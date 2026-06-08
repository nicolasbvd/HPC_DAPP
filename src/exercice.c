#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <immintrin.h>
#include <likwid-marker.h>

typedef struct {
    int *x;
    int *y;
    int *z;
    int *bias;
} Sample;

typedef enum {
    MODE_BOTH = 0,
    MODE_SCALAR,
    MODE_SIMD,
    MODE_SDFG
} RunMode;

static long long now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000LL + (long long)ts.tv_nsec / 1000000LL;
}

static inline int clamp_int(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void init_samples(Sample *a, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        int base = (int)(i * 3 + 7);
        a->x[i]    =  (base % 50) - 25;
        a->y[i]    = ((base * 2) % 60) - 30;
        a->z[i]    = ((base * 5) % 40) - 20;
        a->bias[i] =  (int)(i % 8) - 4;
    }
}

void process_samples(const Sample *a, size_t n, int *energy, int *score) {
    for (size_t i = 0; i < n; ++i) {
        int x = a->x[i];
        int y = a->y[i];
        int z = a->z[i];
        int b = a->bias[i];

        // Normes
        int e = x * x + y * y + z * z;

        // Calcul d'un score abitraire
        int s = (x + y - z) * 3 + b * 5;

        // Clamp foncièrement inutile mais intéressant pour l'exercice
        s = clamp_int(s, -1000, 1000);

        energy[i] = e;
        score[i]  = s;
    }
}

void process_samples_simd(const Sample *a, size_t n, int *energy, int *score) {
    size_t i = 0;

    const __m256i v3   = _mm256_set1_epi32(3);
    const __m256i v5   = _mm256_set1_epi32(5);
    const __m256i vmin = _mm256_set1_epi32(-1000);
    const __m256i vmax = _mm256_set1_epi32(1000);

    for (; i + 8 <= n; i += 8) {
        __m256i vx = _mm256_loadu_si256((const __m256i*)&a->x[i]);
        __m256i vy = _mm256_loadu_si256((const __m256i*)&a->y[i]);
        __m256i vz = _mm256_loadu_si256((const __m256i*)&a->z[i]);
        __m256i vb = _mm256_loadu_si256((const __m256i*)&a->bias[i]);

        __m256i vxx = _mm256_mullo_epi32(vx, vx);
        __m256i vyy = _mm256_mullo_epi32(vy, vy);
        __m256i vzz = _mm256_mullo_epi32(vz, vz);
        __m256i ve  = _mm256_add_epi32(_mm256_add_epi32(vxx, vyy), vzz);

        __m256i vxyz = _mm256_sub_epi32(_mm256_add_epi32(vx, vy), vz);
        __m256i vs   = _mm256_add_epi32(
            _mm256_mullo_epi32(vxyz, v3),
            _mm256_mullo_epi32(vb, v5)
        );

        vs = _mm256_max_epi32(vs, vmin);
        vs = _mm256_min_epi32(vs, vmax);

        _mm256_storeu_si256((__m256i*)&energy[i], ve);
        _mm256_storeu_si256((__m256i*)&score[i],  vs);
    }

    for (; i < n; ++i) {
        int x = a->x[i];
        int y = a->y[i];
        int z = a->z[i];
        int b = a->bias[i];

        int e = x * x + y * y + z * z;
        int s = (x + y - z) * 3 + b * 5;
        s = clamp_int(s, -1000, 1000);

        energy[i] = e;
        score[i]  = s;
    }
}

void process_samples_SDFG(const Sample *a, size_t n, int *energy, int *score) {
    if (n == 0) {
        return;
    }

    if (process_samples_sdfg_init((int)n) != 0) {
        fprintf(stderr, "Error: failed to initialize DaCe SDFG for n=%zu\n", n);
        return;
    }

    process_samples_sdfg_run(a->x, a->y, a->z, a->bias, energy, score, (int)n);

    process_samples_sdfg_exit(); 
}

void compare_arrays(const int *a, const int *b, size_t n, const char *name) {
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            printf("Mismatch in %s at index %zu: %d != %d\n", name, i, a[i], b[i]);
            return;
        }
    }
    printf("Arrays %s match.\n", name);
}

static RunMode parse_mode(int argc, char **argv) {
    for (int i = 3; i < argc; ++i) {
        if (strcmp(argv[i], "--scalar") == 0) return MODE_SCALAR;
        if (strcmp(argv[i], "--simd") == 0) return MODE_SIMD;
        if (strcmp(argv[i], "--sdfg") == 0) return MODE_SDFG;
    }
    return MODE_BOTH;
}

int main(int argc, char** argv) {

    LIKWID_MARKER_INIT;
    LIKWID_MARKER_THREADINIT;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <n> <repeats> [--scalar|--simd|--sdfg]\n", argv[0]);
        return 1;
    }

    size_t n = (size_t)strtoull(argv[1], NULL, 10);
    size_t repeats = (size_t)strtoull(argv[2], NULL, 10);

    if (n == 0 || repeats == 0) {
        fprintf(stderr, "Error: n and repeats must be > 0\n");
        return 1;
    }

    Sample samples;
    int *energy       = (int*)malloc(n * sizeof(int));
    int *score        = (int*)malloc(n * sizeof(int));
    int *energy_simd  = (int*)malloc(n * sizeof(int));
    int *score_simd   = (int*)malloc(n * sizeof(int));
    
    int *energy_sdfg  = (int*)malloc(n * sizeof(int));
    int *score_sdfg   = (int*)malloc(n * sizeof(int));

    samples.x         = (int*)malloc(n * sizeof(int));
    samples.y         = (int*)malloc(n * sizeof(int));
    samples.z         = (int*)malloc(n * sizeof(int));
    samples.bias      = (int*)malloc(n * sizeof(int));

    if (!samples.x || !samples.y || !samples.z || !samples.bias || !energy || !score || !energy_simd || !score_simd) {
        perror("malloc");
        free(samples.x);
        free(samples.y);
        free(samples.z);
        free(samples.bias);
        free(energy);
        free(score);
        free(energy_simd);
        free(score_simd);
        free(score_sdfg);
        free(energy_sdfg);
        return 1;
    }

    init_samples(&samples, n);

    RunMode mode = parse_mode(argc, argv);

    long long totalNormalMs = 0;
    long long totalSimdMs = 0;
    long long totalSDFG = 0;
    long long minimumTimeNormal = 10000000;
    long long minimumTimeSimd = 10000000;
    long long minimumTimeSDFG = 10000000;

    LIKWID_MARKER_START("sequentiel");
    if (mode == MODE_SCALAR || mode == MODE_BOTH) {
        for (size_t r = 0; r < repeats; ++r) {
            long long startTime = now_ms();
            process_samples(&samples, n, energy, score);
            long long endTime = now_ms();
            long long currentTimeNormal = endTime - startTime;
            if (currentTimeNormal < minimumTimeNormal) {
                minimumTimeNormal = currentTimeNormal;
            }
            totalNormalMs += endTime - startTime;
        }
    }
    LIKWID_MARKER_STOP("sequentiel");

    LIKWID_MARKER_START("simd");
    if (mode == MODE_SIMD || mode == MODE_BOTH) {
        
        for (size_t r = 0; r < repeats; ++r) {
            long long startTime = now_ms();
            process_samples_simd(&samples, n, energy_simd, score_simd);
            long long endTime = now_ms();
            long long currentTimeSimd = endTime - startTime;
            if (currentTimeSimd < minimumTimeSimd) {
                minimumTimeSimd = currentTimeSimd;
            }
            totalSimdMs += endTime - startTime;
        }
    
    }
    LIKWID_MARKER_STOP("simd");


    LIKWID_MARKER_START("SDFG");
    if (mode == MODE_SDFG || mode == MODE_BOTH) {

        for (size_t r = 0; r < repeats; ++r) {
            long long startTime = now_ms();
            process_samples_SDFG(&samples, n, energy_sdfg, score_sdfg);
            long long endTime = now_ms();
            long long currentTimeSDFG = endTime - startTime;
            if (currentTimeSDFG < minimumTimeSDFG) {
                minimumTimeSDFG = currentTimeSDFG;
            }
            totalSDFG += endTime - startTime;
        }
    }
    LIKWID_MARKER_STOP("SDFG");


    if (mode == MODE_BOTH) {
        compare_arrays(energy, energy_simd, n, "energy");
        compare_arrays(score, score_simd, n, "score");
        compare_arrays(energy, energy_sdfg, n, "energy SDFG");
        compare_arrays(score, score_sdfg, n, "score SDFG"); 
    }

    printf("n = %zu, repeats = %zu\n", n, repeats);
    if (mode != MODE_SIMD) {
        printf("Processing time normal total : %lld ms\n", totalNormalMs);
        printf("Per run normal : %.6f ms\n", (double)totalNormalMs / (double)repeats);
        printf("Minimum time normal : %lld ms\n", minimumTimeNormal);
    }
    if (mode != MODE_SCALAR) {
        printf("Processing time SIMD total   : %lld ms\n", totalSimdMs);
        printf("Per run SIMD   : %.6f ms\n", (double)totalSimdMs / (double)repeats);
        printf("Minimum time SIMD : %lld ms\n", minimumTimeSimd);
    }

    if (mode != MODE_SDFG) {

        printf("Processing time SDFG total   : %lld ms\n", totalSDFG);
        printf("Per run SDFG   : %.6f ms\n", (double)totalSDFG / (double)repeats);
        printf("Minimum time SDFG : %lld ms\n", minimumTimeSDFG);
    }

    LIKWID_MARKER_CLOSE;
    free(samples.x);
    free(samples.y);
    free(samples.z);
    free(samples.bias);
    free(energy);
    free(score);
    free(energy_simd);
    free(score_simd);
    free(energy_sdfg);
    free(score_sdfg);
    return 0;
}