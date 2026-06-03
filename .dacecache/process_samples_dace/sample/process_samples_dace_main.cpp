#include <cstdlib>
#include "../include/process_samples_dace.h"

int main(int argc, char **argv) {
    process_samples_daceHandle_t handle;
    int err;
    int N = 42;
    int * __restrict__ b = (int*) calloc(N, sizeof(int));
    int * __restrict__ energy = (int*) calloc(N, sizeof(int));
    int * __restrict__ score = (int*) calloc(N, sizeof(int));
    int * __restrict__ x = (int*) calloc(N, sizeof(int));
    int * __restrict__ y = (int*) calloc(N, sizeof(int));
    int * __restrict__ z = (int*) calloc(N, sizeof(int));


    handle = __dace_init_process_samples_dace(N);
    __program_process_samples_dace(handle, b, energy, score, x, y, z, N);
    err = __dace_exit_process_samples_dace(handle);

    free(b);
    free(energy);
    free(score);
    free(x);
    free(y);
    free(z);


    return err;
}
