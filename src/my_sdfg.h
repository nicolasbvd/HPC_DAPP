#ifndef MY_SDFG_H
#define MY_SDFG_H

#ifdef __cplusplus
extern "C" {
#endif

int process_samples_sdfg_init(int N);
void process_samples_sdfg_run(const int *x, const int *y, const int *z, const int *b,
                             int *energy, int *score, int N);
int process_samples_sdfg_exit(void);

#ifdef __cplusplus
}
#endif

#endif // MY_SDFG_H