/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct process_samples_dace_state_t {

};

inline void process_samples_dace_13_4_0_0_2(process_samples_dace_state_t *__state, const int&  __tmp_15_20_r, const int&  __tmp_15_34_r, const int&  __tmp_15_48_r, const int&  __tmp_18_39_r, int&  __tmp_15_8_w, int&  __tmp_22_12_w) {
    int64_t x_slice_y_slice_z_slice_times_3;
    int64_t b_slice_times_5;
    int x_slice_times_x_slice;
    int y_slice_times_y_slice;
    int z_slice_times_z_slice;
    int x_slice_plus_y_slice;
    int x_slice_y_slice_minus_z_slice;
    int64_t s;


    x_slice_times_x_slice = (__tmp_15_20_r * __tmp_15_20_r);
    y_slice_times_y_slice = (__tmp_15_34_r * __tmp_15_34_r);
    z_slice_times_z_slice = (__tmp_15_48_r * __tmp_15_48_r);
    x_slice_plus_y_slice = (__tmp_15_20_r + __tmp_15_34_r);
    {

        {
            int __out;

            ///////////////////
            // Tasklet code (assign_15_8)
            __out = ((x_slice_times_x_slice + y_slice_times_y_slice) + z_slice_times_z_slice);
            ///////////////////

            __tmp_15_8_w = __out;
        }

    }
    x_slice_y_slice_minus_z_slice = (x_slice_plus_y_slice - __tmp_15_48_r);
    {

        {
            int64_t __out;

            ///////////////////
            // Tasklet code (_Mult_)
            __out = (int64_t(x_slice_y_slice_minus_z_slice) * 3);
            ///////////////////

            x_slice_y_slice_z_slice_times_3 = __out;
        }
        {
            int __in1 = __tmp_18_39_r;
            int64_t __out;

            ///////////////////
            // Tasklet code (_Mult_)
            __out = (int64_t(__in1) * 5);
            ///////////////////

            b_slice_times_5 = __out;
        }

    }
    s = (x_slice_y_slice_z_slice_times_3 + b_slice_times_5);
    if ((s < -1000)) {
        {

            {
                int __out;

                ///////////////////
                // Tasklet code (assign_22_12)
                __out = -1000;
                ///////////////////

                __tmp_22_12_w = __out;
            }

        }
    } else {
        if ((s > 1000)) {
            {

                {
                    int __out;

                    ///////////////////
                    // Tasklet code (assign_24_12)
                    __out = 1000;
                    ///////////////////

                    __tmp_22_12_w = __out;
                }

            }
        } else {
            {

                {
                    int __out;

                    ///////////////////
                    // Tasklet code (assign_26_12)
                    __out = s;
                    ///////////////////

                    __tmp_22_12_w = __out;
                }

            }
        }
    }
}

void __program_process_samples_dace_internal(process_samples_dace_state_t*__state, int * __restrict__ b, int * __restrict__ energy, int * __restrict__ score, int * __restrict__ x, int * __restrict__ y, int * __restrict__ z, int N)
{

    {

        {
            #pragma omp parallel for
            for (auto i = 0; i < N; i += 1) {
                process_samples_dace_13_4_0_0_2(__state, x[i], y[i], z[i], b[i], energy[i], score[i]);
            }
        }

    }
}

DACE_EXPORTED void __program_process_samples_dace(process_samples_dace_state_t *__state, int * __restrict__ b, int * __restrict__ energy, int * __restrict__ score, int * __restrict__ x, int * __restrict__ y, int * __restrict__ z, int N)
{
    __program_process_samples_dace_internal(__state, b, energy, score, x, y, z, N);
}

DACE_EXPORTED process_samples_dace_state_t *__dace_init_process_samples_dace(int N)
{

    int __result = 0;
    process_samples_dace_state_t *__state = new process_samples_dace_state_t;

    if (__result) {
        delete __state;
        return nullptr;
    }

    return __state;
}

DACE_EXPORTED int __dace_exit_process_samples_dace(process_samples_dace_state_t *__state)
{

    int __err = 0;
    delete __state;
    return __err;
}
