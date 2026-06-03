#include <dace/dace.h>
typedef void * process_samples_daceHandle_t;
extern "C" process_samples_daceHandle_t __dace_init_process_samples_dace(int N);
extern "C" int __dace_exit_process_samples_dace(process_samples_daceHandle_t handle);
extern "C" void __program_process_samples_dace(process_samples_daceHandle_t handle, int * __restrict__ b, int * __restrict__ energy, int * __restrict__ score, int * __restrict__ x, int * __restrict__ y, int * __restrict__ z, int N);
