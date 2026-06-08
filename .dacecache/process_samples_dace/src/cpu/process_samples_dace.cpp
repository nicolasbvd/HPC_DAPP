/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct process_samples_dace_state_t {

};

inline void process_samples_dace_13_4_0_0_2(process_samples_dace_state_t *__state, const int&  __tmp_15_20_r, const int&  __tmp_15_34_r, const int&  __tmp_15_48_r, const int&  __tmp_18_39_r, int&  __tmp_15_8_w, int&  __tmp_22_12_w) {
    int64_t __tmp8;
    int64_t __tmp9;
    int __tmp1;
    int __tmp2;
    int __tmp4;
    int __tmp6;
    int __tmp7;
    int64_t s;


    __tmp1 = (__tmp_15_20_r * __tmp_15_20_r);
    __tmp2 = (__tmp_15_34_r * __tmp_15_34_r);
    __tmp4 = (__tmp_15_48_r * __tmp_15_48_r);
    __tmp6 = (__tmp_15_20_r + __tmp_15_34_r);
    {

        {
            int __out;

            ///////////////////
            // Tasklet code (assign_15_8)
            __out = ((__tmp1 + __tmp2) + __tmp4);
            ///////////////////

            __tmp_15_8_w = __out;
        }

    }
    __tmp7 = (__tmp6 - __tmp_15_48_r);
    {

        {
            int64_t __out;

            ///////////////////
            // Tasklet code (_Mult_)
            __out = (int64_t(__tmp7) * 3);
            ///////////////////

            __tmp8 = __out;
        }
        {
            int __in1 = __tmp_18_39_r;
            int64_t __out;

            ///////////////////
            // Tasklet code (_Mult_)
            __out = (int64_t(__in1) * 5);
            ///////////////////

            __tmp9 = __out;
        }

    }
    s = (__tmp8 + __tmp9);

    if ((! (s < -1000))) {

        if ((! (s > 1000))) {
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

        } else {
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

        }


    } else {
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
