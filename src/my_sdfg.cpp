#include "my_sdfg.h"
#include ".dacecache/process_samples_dace/include/process_samples_dace.h"
#include <omp.h>

static process_samples_daceHandle_t dace_handle = nullptr;
static int dace_handle_N = 0;

int process_samples_sdfg_init(int N) {
    if (N <= 0) {
        return -1;
    }
    if (dace_handle && dace_handle_N == N) {
        return 0;
    }
    if (dace_handle) {
        __dace_exit_process_samples_dace(dace_handle);
        dace_handle = nullptr;
        dace_handle_N = 0;
    }
    dace_handle = __dace_init_process_samples_dace(N);
    if (!dace_handle) {
        return -1;
    }
    dace_handle_N = N;
    /* Force single-threaded execution for OpenMP-enabled runtimes */
    omp_set_dynamic(0);
    omp_set_num_threads(1);
    return 0;
}

void process_samples_sdfg_run(const int *x, const int *y, const int *z, const int *b,
                             int *energy, int *score, int N) {
    if (!dace_handle || dace_handle_N != N) {
        if (process_samples_sdfg_init(N) != 0) {
            return;
        }
    }
    __program_process_samples_dace(dace_handle,
                                  (int *)b,
                                  energy,
                                  score,
                                  (int *)x,
                                  (int *)y,
                                  (int *)z,
                                  N);
}

int process_samples_sdfg_exit(void) {
    if (!dace_handle) {
        return 0;
    }
    int err = __dace_exit_process_samples_dace(dace_handle);
    dace_handle = nullptr;
    dace_handle_N = 0;
    return err;
}