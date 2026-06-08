#ifndef DACE_API_H
#define DACE_API_H

#ifdef __cplusplus
extern "C" {
#endif

/* Minimal C declarations for the DaCe-generated runtime symbols.
 * We avoid including the generated C++ headers here so this file can be
 * compiled with a C compiler. The actual definitions are provided by the
 * shared library produced by DaCe.
 */

typedef void* process_samples_daceHandle_t;

process_samples_daceHandle_t __dace_init_process_samples_dace(int N);
void __program_process_samples_dace(process_samples_daceHandle_t handle,
                                   int *b, int *energy, int *score,
                                   int *x, int *y, int *z, int N);
int __dace_exit_process_samples_dace(process_samples_daceHandle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* DACE_API_H */
