pour o0 :
```bash
 ./simd_exercice 10000000 1000
Arrays energy match.
Arrays score match.
n = 10000000, repeats = 1000
Processing time normal total : 63764 ms
Per run normal : 63.764000 ms
Processing time SIMD total   : 26135 ms
Per run SIMD   : 26.135000 ms
Processing time SDFG total   : 14319 ms
Per run SDFG   : 14.319000 ms

```

pour o3 + flops likwid :
```bash
likwid-perfctr -C 2 -g HPC -m ./simd_exercice 10000000 1000
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz
CPU type:	Intel Icelake processor
CPU clock:	1.50 GHz
--------------------------------------------------------------------------------
Arrays energy match.
Arrays score match.
n = 10000000, repeats = 1000
Processing time normal total : 11916 ms
Per run normal : 11.916000 ms
Minimum time normal : 11 ms
Processing time SIMD total   : 11691 ms
Per run SIMD   : 11.691000 ms
Minimum time SIMD : 11 ms
Processing time SDFG total   : 20918 ms
Per run SDFG   : 20.918000 ms
Minimum time SDFG : 20 ms
--------------------------------------------------------------------------------
Region simd, Group 1: HPC
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  11.671990 |
|     call count    |          1 |
+-------------------+------------+

+------------------------------------------+---------+-------------+
|                   Event                  | Counter |  HWThread 2 |
+------------------------------------------+---------+-------------+
|             INSTR_RETIRED_ANY            |  FIXC0  | 33750240000 |
|           CPU_CLK_UNHALTED_CORE          |  FIXC1  | 44553870000 |
|           CPU_CLK_UNHALTED_REF           |  FIXC2  | 17212530000 |
|    FP_ARITH_INST_RETIRED_SCALAR_DOUBLE   |   PMC0  |          11 |
| FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE |   PMC1  |           0 |
|              L2_LINES_IN_ALL             |   PMC2  |  3761583000 |
|              L2_TRANS_L2_WB              |   PMC3  |  3720480000 |
+------------------------------------------+---------+-------------+

+------------------------+--------------+
|         Metric         |  HWThread 2  |
+------------------------+--------------+
|   Runtime (RDTSC) [s]  |      11.6720 |
|  Runtime unhalted [s]  |      29.7026 |
|       Clock [MHz]      |    3882.6834 |
|           CPI          |       1.3201 |
|   DP total [MFLOP/s]   | 9.424271e-07 |
|  L3 load BW [MBytes/s] |   20625.5585 |
| L3 evict BW [MBytes/s] |   20400.1820 |
| L3 total BW [MBytes/s] |   41025.7404 |
|  L3 total vol [GBytes] |     478.8520 |
|  Operational intensity | 2.297161e-11 |
+------------------------+--------------+

Region SDFG, Group 1: HPC
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  20.883980 |
|     call count    |          1 |
+-------------------+------------+

+------------------------------------------+---------+--------------+
|                   Event                  | Counter |  HWThread 2  |
+------------------------------------------+---------+--------------+
|             INSTR_RETIRED_ANY            |  FIXC0  | 280001600000 |
|           CPU_CLK_UNHALTED_CORE          |  FIXC1  |  79573370000 |
|           CPU_CLK_UNHALTED_REF           |  FIXC2  |  30764360000 |
|    FP_ARITH_INST_RETIRED_SCALAR_DOUBLE   |   PMC0  |           11 |
| FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE |   PMC1  |            0 |
|              L2_LINES_IN_ALL             |   PMC2  |   3764163000 |
|              L2_TRANS_L2_WB              |   PMC3  |   3722177000 |
+------------------------------------------+---------+--------------+

+------------------------+--------------+
|         Metric         |  HWThread 2  |
+------------------------+--------------+
|   Runtime (RDTSC) [s]  |      20.8840 |
|  Runtime unhalted [s]  |      53.0489 |
|       Clock [MHz]      |    3879.8160 |
|           CPI          |       0.2842 |
|   DP total [MFLOP/s]   | 5.267195e-07 |
|  L3 load BW [MBytes/s] |   11535.4656 |
| L3 evict BW [MBytes/s] |   11406.7974 |
| L3 total BW [MBytes/s] |   22942.2629 |
|  L3 total vol [GBytes] |     479.1258 |
|  Operational intensity | 2.295848e-11 |
+------------------------+--------------+

Region sequentiel, Group 1: HPC
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  11.896340 |
|     call count    |          1 |
+-------------------+------------+

+------------------------------------------+---------+-------------+
|                   Event                  | Counter |  HWThread 2 |
+------------------------------------------+---------+-------------+
|             INSTR_RETIRED_ANY            |  FIXC0  | 28750240000 |
|           CPU_CLK_UNHALTED_CORE          |  FIXC1  | 45329880000 |
|           CPU_CLK_UNHALTED_REF           |  FIXC2  | 17515980000 |
|    FP_ARITH_INST_RETIRED_SCALAR_DOUBLE   |   PMC0  |          11 |
| FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE |   PMC1  |           0 |
|              L2_LINES_IN_ALL             |   PMC2  |  3761393000 |
|              L2_TRANS_L2_WB              |   PMC3  |  3721198000 |
+------------------------------------------+---------+-------------+

+------------------------+--------------+
|         Metric         |  HWThread 2  |
+------------------------+--------------+
|   Runtime (RDTSC) [s]  |      11.8963 |
|  Runtime unhalted [s]  |      30.2199 |
|       Clock [MHz]      |    3881.8736 |
|           CPI          |       1.5767 |
|   DP total [MFLOP/s]   | 9.246541e-07 |
|  L3 load BW [MBytes/s] |   20235.5642 |
| L3 evict BW [MBytes/s] |   20019.3229 |
| L3 total BW [MBytes/s] |   40254.8871 |
|  L3 total vol [GBytes] |     478.8858 |
|  Operational intensity | 2.296998e-11 |
+------------------------+--------------+


```

exec 03  + energy :
```bash
likwid-perfctr -C 2 -g ENERGY -m ./simd_exercice 10000000 1000
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz
CPU type:	Intel Icelake processor
CPU clock:	1.50 GHz
--------------------------------------------------------------------------------
Arrays energy match.
Arrays score match.
n = 10000000, repeats = 1000
Processing time normal total : 12123 ms
Per run normal : 12.123000 ms
Minimum time normal : 11 ms
Processing time SIMD total   : 11837 ms
Per run SIMD   : 11.837000 ms
Minimum time SIMD : 11 ms
Processing time SDFG total   : 20735 ms
Per run SDFG   : 20.735000 ms
Minimum time SDFG : 20 ms
--------------------------------------------------------------------------------
Region sequentiel, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  12.103840 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+--------------+
|         Event         | Counter |  HWThread 2  |
+-----------------------+---------+--------------+
|   INSTR_RETIRED_ANY   |  FIXC0  |  28750240000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  46141550000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |  17831240000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 229398100000 |
|       TEMP_CORE       |   TMP0  |           59 |
|     PWR_PKG_ENERGY    |   PWR0  |     189.5917 |
|     PWR_PP0_ENERGY    |   PWR1  |     150.0852 |
|    PWR_DRAM_ENERGY    |   PWR3  |            0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |            0 |
+-----------------------+---------+--------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    12.1038 |
| Runtime unhalted [s] |    30.7610 |
|      Clock [MHz]     |  3881.5206 |
|          CPI         |     1.6049 |
|    Temperature [C]   |         59 |
|      Energy [J]      |   189.5917 |
|       Power [W]      |    15.6638 |
|    Energy PP0 [J]    |   150.0852 |
|     Power PP0 [W]    |    12.3998 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+

Region simd, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  11.817940 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+--------------+
|         Event         | Counter |  HWThread 2  |
+-----------------------+---------+--------------+
|   INSTR_RETIRED_ANY   |  FIXC0  |  33750240000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  44969730000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |  17394760000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 223733300000 |
|       TEMP_CORE       |   TMP0  |           65 |
|     PWR_PKG_ENERGY    |   PWR0  |     190.9365 |
|     PWR_PP0_ENERGY    |   PWR1  |     151.1205 |
|    PWR_DRAM_ENERGY    |   PWR3  |            0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |            0 |
+-----------------------+---------+--------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    11.8179 |
| Runtime unhalted [s] |    29.9798 |
|      Clock [MHz]     |  3877.8687 |
|          CPI         |     1.3324 |
|    Temperature [C]   |         65 |
|      Energy [J]      |   190.9365 |
|       Power [W]      |    16.1565 |
|    Energy PP0 [J]    |   151.1205 |
|     Power PP0 [W]    |    12.7874 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+

Region SDFG, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  20.701650 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+--------------+
|         Event         | Counter |  HWThread 2  |
+-----------------------+---------+--------------+
|   INSTR_RETIRED_ANY   |  FIXC0  | 280001600000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  79072590000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |  30555230000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 394088000000 |
|       TEMP_CORE       |   TMP0  |           72 |
|     PWR_PKG_ENERGY    |   PWR0  |     322.4305 |
|     PWR_PP0_ENERGY    |   PWR1  |     262.6166 |
|    PWR_DRAM_ENERGY    |   PWR3  |            0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |            0 |
+-----------------------+---------+--------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    20.7017 |
| Runtime unhalted [s] |    52.7151 |
|      Clock [MHz]     |  3881.7867 |
|          CPI         |     0.2824 |
|    Temperature [C]   |         72 |
|      Energy [J]      |   322.4305 |
|       Power [W]      |    15.5751 |
|    Energy PP0 [J]    |   262.6166 |
|     Power PP0 [W]    |    12.6858 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+


```

exec o0 et flops:
```bash
likwid-perfctr -C 2 -g HPC -m ./simd_exercice 10000000 1000
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz
CPU type:	Intel Icelake processor
CPU clock:	1.50 GHz
--------------------------------------------------------------------------------
Arrays energy match.
Arrays score match.
n = 10000000, repeats = 1000
Processing time normal total : 63989 ms
Per run normal : 63.989000 ms
Minimum time normal : 62 ms
Processing time SIMD total   : 25285 ms
Per run SIMD   : 25.285000 ms
Minimum time SIMD : 24 ms
Processing time SDFG total   : 20667 ms
Per run SDFG   : 20.667000 ms
Minimum time SDFG : 20 ms
--------------------------------------------------------------------------------
Region simd, Group 1: HPC
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  25.244780 |
|     call count    |          1 |
+-------------------+------------+

+------------------------------------------+---------+--------------+
|                   Event                  | Counter |  HWThread 2  |
+------------------------------------------+---------+--------------+
|             INSTR_RETIRED_ANY            |  FIXC0  | 190000300000 |
|           CPU_CLK_UNHALTED_CORE          |  FIXC1  |  96789830000 |
|           CPU_CLK_UNHALTED_REF           |  FIXC2  |  37377150000 |
|    FP_ARITH_INST_RETIRED_SCALAR_DOUBLE   |   PMC0  |           11 |
| FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE |   PMC1  |            0 |
|              L2_LINES_IN_ALL             |   PMC2  |   3767989000 |
|              L2_TRANS_L2_WB              |   PMC3  |   3712200000 |
+------------------------------------------+---------+--------------+

+------------------------+--------------+
|         Metric         |  HWThread 2  |
+------------------------+--------------+
|   Runtime (RDTSC) [s]  |      25.2448 |
|  Runtime unhalted [s]  |      64.5266 |
|       Clock [MHz]      |    3884.3182 |
|           CPI          |       0.5094 |
|   DP total [MFLOP/s]   | 4.357336e-07 |
|  L3 load BW [MBytes/s] |    9552.5212 |
| L3 evict BW [MBytes/s] |    9411.0862 |
| L3 total BW [MBytes/s] |   18963.6074 |
|  L3 total vol [GBytes] |     478.7321 |
|  Operational intensity | 2.297736e-11 |
+------------------------+--------------+

Region SDFG, Group 1: HPC
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  20.633510 |
|     call count    |          1 |
+-------------------+------------+

+------------------------------------------+---------+--------------+
|                   Event                  | Counter |  HWThread 2  |
+------------------------------------------+---------+--------------+
|             INSTR_RETIRED_ANY            |  FIXC0  | 280001700000 |
|           CPU_CLK_UNHALTED_CORE          |  FIXC1  |  78966180000 |
|           CPU_CLK_UNHALTED_REF           |  FIXC2  |  30491230000 |
|    FP_ARITH_INST_RETIRED_SCALAR_DOUBLE   |   PMC0  |           11 |
| FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE |   PMC1  |            0 |
|              L2_LINES_IN_ALL             |   PMC2  |   3766998000 |
|              L2_TRANS_L2_WB              |   PMC3  |   3711287000 |
+------------------------------------------+---------+--------------+

+------------------------+--------------+
|         Metric         |  HWThread 2  |
+------------------------+--------------+
|   Runtime (RDTSC) [s]  |      20.6335 |
|  Runtime unhalted [s]  |      52.6441 |
|       Clock [MHz]      |    3884.6996 |
|           CPI          |       0.2820 |
|   DP total [MFLOP/s]   | 5.331134e-07 |
|  L3 load BW [MBytes/s] |   11684.2879 |
| L3 evict BW [MBytes/s] |   11511.4863 |
| L3 total BW [MBytes/s] |   23195.7743 |
|  L3 total vol [GBytes] |     478.6102 |
|  Operational intensity | 2.298321e-11 |
+------------------------+--------------+

Region sequentiel, Group 1: HPC
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  63.886120 |
|     call count    |          1 |
+-------------------+------------+

+------------------------------------------+---------+--------------+
|                   Event                  | Counter |  HWThread 2  |
+------------------------------------------+---------+--------------+
|             INSTR_RETIRED_ANY            |  FIXC0  | 880000300000 |
|           CPU_CLK_UNHALTED_CORE          |  FIXC1  | 244655800000 |
|           CPU_CLK_UNHALTED_REF           |  FIXC2  |  94485830000 |
|    FP_ARITH_INST_RETIRED_SCALAR_DOUBLE   |   PMC0  |           11 |
| FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE |   PMC1  |            0 |
|              L2_LINES_IN_ALL             |   PMC2  |   3768335000 |
|              L2_TRANS_L2_WB              |   PMC3  |   3696303000 |
+------------------------------------------+---------+--------------+

+------------------------+--------------+
|         Metric         |  HWThread 2  |
+------------------------+--------------+
|   Runtime (RDTSC) [s]  |      63.8861 |
|  Runtime unhalted [s]  |     163.1039 |
|       Clock [MHz]      |    3884.0078 |
|           CPI          |       0.2780 |
|   DP total [MFLOP/s]   | 1.721814e-07 |
|  L3 load BW [MBytes/s] |    3775.0522 |
| L3 evict BW [MBytes/s] |    3702.8918 |
| L3 total BW [MBytes/s] |    7477.9441 |
|  L3 total vol [GBytes] |     477.7368 |
|  Operational intensity | 2.302523e-11 |
+------------------------+--------------+


```

exec o0 et energy :
```bash
likwid-perfctr -C 2 -g ENERGY -m ./simd_exercice 10000000 1000
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz
CPU type:	Intel Icelake processor
CPU clock:	1.50 GHz
--------------------------------------------------------------------------------
Arrays energy match.
Arrays score match.
n = 10000000, repeats = 1000
Processing time normal total : 63831 ms
Per run normal : 63.831000 ms
Minimum time normal : 62 ms
Processing time SIMD total   : 25248 ms
Per run SIMD   : 25.248000 ms
Minimum time SIMD : 24 ms
Processing time SDFG total   : 20307 ms
Per run SDFG   : 20.307000 ms
Minimum time SDFG : 19 ms
--------------------------------------------------------------------------------
Region simd, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  25.207160 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+--------------+
|         Event         | Counter |  HWThread 2  |
+-----------------------+---------+--------------+
|   INSTR_RETIRED_ANY   |  FIXC0  | 190000300000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  96701120000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |  37336670000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 482160500000 |
|       TEMP_CORE       |   TMP0  |           83 |
|     PWR_PKG_ENERGY    |   PWR0  |     462.0643 |
|     PWR_PP0_ENERGY    |   PWR1  |     389.3035 |
|    PWR_DRAM_ENERGY    |   PWR3  |            0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |            0 |
+-----------------------+---------+--------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    25.2072 |
| Runtime unhalted [s] |    64.4674 |
|      Clock [MHz]     |  3884.9656 |
|          CPI         |     0.5090 |
|    Temperature [C]   |         83 |
|      Energy [J]      |   462.0643 |
|       Power [W]      |    18.3307 |
|    Energy PP0 [J]    |   389.3035 |
|     Power PP0 [W]    |    15.4442 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+

Region sequentiel, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  63.728370 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+---------------+
|         Event         | Counter |   HWThread 2  |
+-----------------------+---------+---------------+
|   INSTR_RETIRED_ANY   |  FIXC0  |  880000300000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  244111600000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |   94284150000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 1217328000000 |
|       TEMP_CORE       |   TMP0  |            81 |
|     PWR_PKG_ENERGY    |   PWR0  |     1014.6720 |
|     PWR_PP0_ENERGY    |   PWR1  |      858.2743 |
|    PWR_DRAM_ENERGY    |   PWR3  |             0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |             0 |
+-----------------------+---------+---------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    63.7284 |
| Runtime unhalted [s] |   162.7411 |
|      Clock [MHz]     |  3883.6581 |
|          CPI         |     0.2774 |
|    Temperature [C]   |         81 |
|      Energy [J]      |  1014.6720 |
|       Power [W]      |    15.9218 |
|    Energy PP0 [J]    |   858.2743 |
|     Power PP0 [W]    |    13.4677 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+

Region SDFG, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  20.273870 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+--------------+
|         Event         | Counter |  HWThread 2  |
+-----------------------+---------+--------------+
|   INSTR_RETIRED_ANY   |  FIXC0  | 280001700000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  77672640000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |  29984430000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 387520600000 |
|       TEMP_CORE       |   TMP0  |           79 |
|     PWR_PKG_ENERGY    |   PWR0  |     323.7738 |
|     PWR_PP0_ENERGY    |   PWR1  |     261.7894 |
|    PWR_DRAM_ENERGY    |   PWR3  |            0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |            0 |
+-----------------------+---------+--------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    20.2739 |
| Runtime unhalted [s] |    51.7818 |
|      Clock [MHz]     |  3885.6487 |
|          CPI         |     0.2774 |
|    Temperature [C]   |         79 |
|      Energy [J]      |   323.7738 |
|       Power [W]      |    15.9700 |
|    Energy PP0 [J]    |   261.7894 |
|     Power PP0 [W]    |    12.9127 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+

```

Mono-threaded LIKWID summary (pinned to hwthread 2, `OMP_NUM_THREADS=1`):

HPC group (`likwid-perfctr -g HPC`):
- Normal total: ~13219 ms
- SIMD total:  ~13054 ms
- SDFG total:  ~21629 ms
- SIMD L3 total BW: ~36.8 GB/s
- SDFG L3 total BW:  ~22.2 GB/s

ENERGY group (`likwid-perfctr -g ENERGY`):
- Normal total: ~12974 ms
- SIMD total:  ~13073 ms
- SDFG total:  ~21890 ms
- Energy (package): SIMD ~214 J, SDFG ~355 J


mono-threaded (OMP_NUM_THREADS=1, pinned to hwthread 2):
```bash
Running without Marker API. Activate Marker API with -m on commandline.
Arrays energy match.
Arrays score match.
n = 10000000, repeats = 1000
Processing time normal total : 13115 ms
Per run normal : 13.115000 ms
Minimum time normal : 12 ms
Processing time SIMD total   : 12701 ms
Per run SIMD   : 12.701000 ms
Minimum time SIMD : 11 ms
Processing time SDFG total   : 21616 ms
Per run SDFG   : 21.616000 ms
Minimum time SDFG : 20 ms
```

topology : 
```bash
likwid-topology 
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz
CPU type:	Intel Icelake processor
CPU stepping:	5
********************************************************************************
Hardware Thread Topology
********************************************************************************
Sockets:		1
CPU dies:		1
Cores per socket:	4
Threads per core:	2
--------------------------------------------------------------------------------
HWThread        Thread        Core        Die        Socket        Available
0               0             0           0          0             *                
1               0             1           0          0             *                
2               0             2           0          0             *                
3               0             3           0          0             *                
4               1             0           0          0             *                
5               1             1           0          0             *                
6               1             2           0          0             *                
7               1             3           0          0             *                
--------------------------------------------------------------------------------
Socket 0:		( 0 4 1 5 2 6 3 7 )
--------------------------------------------------------------------------------
********************************************************************************
Cache Topology
********************************************************************************
Level:			1
Size:			48 kB
Cache groups:		( 0 4 ) ( 1 5 ) ( 2 6 ) ( 3 7 )
--------------------------------------------------------------------------------
Level:			2
Size:			512 kB
Cache groups:		( 0 4 ) ( 1 5 ) ( 2 6 ) ( 3 7 )
--------------------------------------------------------------------------------
Level:			3
Size:			8 MB
Cache groups:		( 0 4 1 5 2 6 3 7 )
--------------------------------------------------------------------------------
********************************************************************************
NUMA Topology
********************************************************************************
NUMA domains:		1
--------------------------------------------------------------------------------
Domain:			0
Processors:		( 0 4 1 5 2 6 3 7 )
Distances:		10
Free memory:		764.465 MB
Total memory:		7737.37 MB
--------------------------------------------------------------------------------
```

baseline peakflops :
```bash
 likwid-bench -t peakflops -W N:30kB:1 -i 100
Allocate: Process running on hwthread 0 (Domain N) - Vector length 3750/30000 Offset 0 Alignment 512
--------------------------------------------------------------------------------
LIKWID MICRO BENCHMARK
Test: peakflops
--------------------------------------------------------------------------------
Using 1 work groups
Using 1 threads
--------------------------------------------------------------------------------
Running without Marker API. Activate Marker API with -m on commandline.
--------------------------------------------------------------------------------
Group: 0 Thread 0 Global Thread 0 running on hwthread 0 - Vector length 3750 Offset 0
--------------------------------------------------------------------------------
Cycles:			2142692
CPU Clock:		1500000000
Cycle Clock:		1500000000
Time:			1.428461e-03 sec
Iterations:		100
Iterations per thread:	100
Inner loop executions:	3750
Size (Byte):		30000
Size per thread:	30000
Number of Flops:	6000000
MFlops/s:		4200.32
Data volume (Byte):	3000000
MByte/s:		2100.16
Cycles per update:	5.713845
Cycles per cacheline:	45.710763
Loads per update:	1
Stores per update:	0
Load bytes per element:	8
Store bytes per elem.:	0
Instructions:		7500032
UOPs:			7125000
--------------------------------------------------------------------------------

```

benchmark pour la bande passante : (taille par rapport a nos entrée qui sont énorme donc on check les appel a la mémoire)
```bash
likwid-bench -t triad -W N:500MB:1 -i 100
Allocate: Process running on hwthread 0 (Domain N) - Vector length 15625000/125000000 Offset 0 Alignment 512
Allocate: Process running on hwthread 0 (Domain N) - Vector length 15625000/125000000 Offset 0 Alignment 512
Allocate: Process running on hwthread 0 (Domain N) - Vector length 15625000/125000000 Offset 0 Alignment 512
Allocate: Process running on hwthread 0 (Domain N) - Vector length 15625000/125000000 Offset 0 Alignment 512
--------------------------------------------------------------------------------
LIKWID MICRO BENCHMARK
Test: triad
--------------------------------------------------------------------------------
Using 1 work groups
Using 1 threads
--------------------------------------------------------------------------------
Running without Marker API. Activate Marker API with -m on commandline.
--------------------------------------------------------------------------------
Group: 0 Thread 0 Global Thread 0 running on hwthread 0 - Vector length 15625000 Offset 0
--------------------------------------------------------------------------------
Cycles:			4215837140
CPU Clock:		1500000000
Cycle Clock:		1500000000
Time:			2.810558e+00 sec
Iterations:		100
Iterations per thread:	100
Inner loop executions:	3906250
Size (Byte):		500000000
Size per thread:	500000000
Number of Flops:	3125000000
MFlops/s:		1111.88
Data volume (Byte):	50000000000
MByte/s:		17790.06
Cycles per update:	2.698136
Cycles per cacheline:	21.585086
Loads per update:	3
Stores per update:	1
Load bytes per element:	24
Store bytes per elem.:	8
Load/store ratio:	3.00
Instructions:		7421875016
UOPs:			11718750000
--------------------------------------------------------------------------------
```

perf stat :
```
 Performance counter stats for './simd_exercice 10000000 1000':

        114’629.36 msec task-clock                       #    1.000 CPUs utilized             
               845      context-switches                 #    7.372 /sec                      
                41      cpu-migrations                   #    0.358 /sec                      
           102’439      page-faults                      #  893.654 /sec                      
   427’742’957’488      cycles                           #    3.732 GHz                       
 1’352’488’600’733      instructions                     #    3.16  insn per cycle            
    71’541’856’144      branches                         #  624.115 M/sec                     
           888’520      branch-misses                    #    0.00% of all branches           
                        TopdownL1                 #     19.2 %  tma_backend_bound      
                                                  #     36.6 %  tma_bad_speculation    
                                                  #      2.2 %  tma_frontend_bound     
                                                  #     42.0 %  tma_retiring           

     114.660048931 seconds time elapsed

     114.507449000 seconds user
       0.120980000 seconds sys



```

perfstat scalar : 
```
perf stat ./simd_exercice 10000000 1000 --scalar
Running without Marker API. Activate Marker API with -m on commandline.
n = 10000000, repeats = 1000
Processing time normal total : 64410 ms
Per run normal : 64.410000 ms
Minimum time normal : 63 ms
Processing time SDFG total   : 0 ms
Per run SDFG   : 0.000000 ms
Minimum time SDFG : 10000000 ms

 Performance counter stats for './simd_exercice 10000000 1000 --scalar':

         64’527.36 msec task-clock                       #    1.000 CPUs utilized             
               345      context-switches                 #    5.347 /sec                      
                 3      cpu-migrations                   #    0.046 /sec                      
            63’376      page-faults                      #  982.157 /sec                      
   247’096’515’128      cycles                           #    3.829 GHz                       
   881’619’547’233      instructions                     #    3.57  insn per cycle            
    50’152’354’752      branches                         #  777.226 M/sec                     
           382’492      branch-misses                    #    0.00% of all branches           
                        TopdownL1                 #     21.9 %  tma_backend_bound      
                                                  #      4.7 %  tma_bad_speculation    
                                                  #      4.2 %  tma_frontend_bound     
                                                  #     69.3 %  tma_retiring           

      64.541689609 seconds time elapsed

      64.447402000 seconds user
       0.079984000 seconds sys


```

perfstat sdfg :
```bash
 perf stat ./simd_exercice 10000000 1000 --sdfg
Running without Marker API. Activate Marker API with -m on commandline.
n = 10000000, repeats = 1000
Processing time normal total : 0 ms
Per run normal : 0.000000 ms
Minimum time normal : 10000000 ms
Processing time SIMD total   : 0 ms
Per run SIMD   : 0.000000 ms
Minimum time SIMD : 10000000 ms

 Performance counter stats for './simd_exercice 10000000 1000 --sdfg':

         22’150.82 msec task-clock                       #    0.999 CPUs utilized             
               405      context-switches                 #   18.284 /sec                      
                 7      cpu-migrations                   #    0.316 /sec                      
            63’378      page-faults                      #    2.861 K/sec                     
    80’756’322’669      cycles                           #    3.646 GHz                       
   281’446’368’371      instructions                     #    3.49  insn per cycle            
    20’123’355’372      branches                         #  908.470 M/sec                     
           451’859      branch-misses                    #    0.00% of all branches           
                        TopdownL1                 #     22.1 %  tma_backend_bound      
                                                  #     15.4 %  tma_bad_speculation    
                                                  #      4.5 %  tma_frontend_bound     
                                                  #     58.0 %  tma_retiring           

      22.165750690 seconds time elapsed

      22.056607000 seconds user
       0.094989000 seconds sys



```

perfstat simd:
```bash
perf stat ./simd_exercice 10000000 1000 --simd
Running without Marker API. Activate Marker API with -m on commandline.
n = 10000000, repeats = 1000
Processing time SIMD total   : 26026 ms
Per run SIMD   : 26.026000 ms
Minimum time SIMD : 24 ms
Processing time SDFG total   : 0 ms
Per run SDFG   : 0.000000 ms
Minimum time SDFG : 10000000 ms

 Performance counter stats for './simd_exercice 10000000 1000 --simd':

         26’138.73 msec task-clock                       #    1.000 CPUs utilized             
               356      context-switches                 #   13.620 /sec                      
                 1      cpu-migrations                   #    0.038 /sec                      
            63’372      page-faults                      #    2.424 K/sec                     
    98’209’881’749      cycles                           #    3.757 GHz                       
   191’392’698’354      instructions                     #    1.95  insn per cycle            
     1’361’897’892      branches                         #   52.103 M/sec                     
           268’164      branch-misses                    #    0.02% of all branches           
                        TopdownL1                 #     49.8 %  tma_backend_bound      
                                                  #     13.2 %  tma_bad_speculation    
                                                  #      0.8 %  tma_frontend_bound     
                                                  #     36.2 %  tma_retiring           

      26.148751986 seconds time elapsed

      26.054468000 seconds user
       0.084978000 seconds sys


```

march native 03 sdfg :
```bash
 perf stat ./simd_exercice 10000000 1000 --sdfg
Running without Marker API. Activate Marker API with -m on commandline.
n = 10000000, repeats = 1000
Processing time normal total : 0 ms
Per run normal : 0.000000 ms
Minimum time normal : 10000000 ms
Processing time SIMD total   : 0 ms
Per run SIMD   : 0.000000 ms
Minimum time SIMD : 10000000 ms

 Performance counter stats for './simd_exercice 10000000 1000 --sdfg':

         20’958.12 msec task-clock                       #    1.000 CPUs utilized             
               149      context-switches                 #    7.109 /sec                      
                 1      cpu-migrations                   #    0.048 /sec                      
            63’377      page-faults                      #    3.024 K/sec                     
    80’288’333’939      cycles                           #    3.831 GHz                       
   280’599’621’754      instructions                     #    3.49  insn per cycle            
    20’098’789’882      branches                         #  958.998 M/sec                     
           193’640      branch-misses                    #    0.00% of all branches           
                        TopdownL1                 #     23.8 %  tma_backend_bound      
                                                  #      5.1 %  tma_bad_speculation    
                                                  #      8.9 %  tma_frontend_bound     
                                                  #     62.2 %  tma_retiring           

      20.964556624 seconds time elapsed

      20.871769000 seconds user
       0.087990000 seconds sys



```

marchnative 03 simd :
```bash
 perf stat ./simd_exercice 10000000 1000 --simd
Running without Marker API. Activate Marker API with -m on commandline.
n = 10000000, repeats = 1000
Processing time SIMD total   : 13558 ms
Per run SIMD   : 13.558000 ms
Minimum time SIMD : 12 ms
Processing time SDFG total   : 0 ms
Per run SDFG   : 0.000000 ms
Minimum time SDFG : 10000000 ms

 Performance counter stats for './simd_exercice 10000000 1000 --simd':

         13’626.53 msec task-clock                       #    1.000 CPUs utilized             
                59      context-switches                 #    4.330 /sec                      
                 2      cpu-migrations                   #    0.147 /sec                      
            63’371      page-faults                      #    4.651 K/sec                     
    48’696’840’163      cycles                           #    3.574 GHz                       
    34’304’442’720      instructions                     #    0.70  insn per cycle            
     1’340’888’034      branches                         #   98.403 M/sec                     
           172’483      branch-misses                    #    0.01% of all branches           
                        TopdownL1                 #     80.0 %  tma_backend_bound      
                                                  #      4.7 %  tma_bad_speculation    
                                                  #      0.9 %  tma_frontend_bound     
                                                  #     14.4 %  tma_retiring           

      13.630350987 seconds time elapsed

      13.556022000 seconds user
       0.071984000 seconds sys


```

march native 03 energy : 
```bash
likwid-perfctr -C 2 -g ENERGY -m ./simd_exercice 10000000 1000
--------------------------------------------------------------------------------
CPU name:	Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz
CPU type:	Intel Icelake processor
CPU clock:	1.50 GHz
--------------------------------------------------------------------------------
Arrays energy match.
Arrays score match.
n = 10000000, repeats = 1000
Processing time normal total : 12286 ms
Per run normal : 12.286000 ms
Minimum time normal : 11 ms
Processing time SIMD total   : 12304 ms
Per run SIMD   : 12.304000 ms
Minimum time SIMD : 11 ms
Processing time SDFG total   : 20279 ms
Per run SDFG   : 20.279000 ms
Minimum time SDFG : 19 ms
--------------------------------------------------------------------------------
Region simd, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  12.284290 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+--------------+
|         Event         | Counter |  HWThread 2  |
+-----------------------+---------+--------------+
|   INSTR_RETIRED_ANY   |  FIXC0  |  33750240000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  46837960000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |  18100980000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 232722200000 |
|       TEMP_CORE       |   TMP0  |           67 |
|     PWR_PKG_ENERGY    |   PWR0  |     197.5184 |
|     PWR_PP0_ENERGY    |   PWR1  |     155.7713 |
|    PWR_DRAM_ENERGY    |   PWR3  |            0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |            0 |
+-----------------------+---------+--------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    12.2843 |
| Runtime unhalted [s] |    31.2253 |
|      Clock [MHz]     |  3881.3887 |
|          CPI         |     1.3878 |
|    Temperature [C]   |         67 |
|      Energy [J]      |   197.5184 |
|       Power [W]      |    16.0789 |
|    Energy PP0 [J]    |   155.7713 |
|     Power PP0 [W]    |    12.6805 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+

Region SDFG, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  20.246620 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+--------------+
|         Event         | Counter |  HWThread 2  |
+-----------------------+---------+--------------+
|   INSTR_RETIRED_ANY   |  FIXC0  | 280001600000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  77331780000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |  29865190000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 385483200000 |
|       TEMP_CORE       |   TMP0  |           76 |
|     PWR_PKG_ENERGY    |   PWR0  |     319.4761 |
|     PWR_PP0_ENERGY    |   PWR1  |     259.0395 |
|    PWR_DRAM_ENERGY    |   PWR3  |            0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |            0 |
+-----------------------+---------+--------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    20.2466 |
| Runtime unhalted [s] |    51.5545 |
|      Clock [MHz]     |  3884.0426 |
|          CPI         |     0.2762 |
|    Temperature [C]   |         76 |
|      Energy [J]      |   319.4761 |
|       Power [W]      |    15.7792 |
|    Energy PP0 [J]    |   259.0395 |
|     Power PP0 [W]    |    12.7942 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+

Region sequentiel, Group 1: ENERGY
+-------------------+------------+
|    Region Info    | HWThread 2 |
+-------------------+------------+
| RDTSC Runtime [s] |  12.266610 |
|     call count    |          1 |
+-------------------+------------+

+-----------------------+---------+--------------+
|         Event         | Counter |  HWThread 2  |
+-----------------------+---------+--------------+
|   INSTR_RETIRED_ANY   |  FIXC0  |  28750320000 |
| CPU_CLK_UNHALTED_CORE |  FIXC1  |  46754510000 |
|  CPU_CLK_UNHALTED_REF |  FIXC2  |  18064840000 |
|     TOPDOWN_SLOTS     |  FIXC3  | 232272000000 |
|       TEMP_CORE       |   TMP0  |           65 |
|     PWR_PKG_ENERGY    |   PWR0  |     193.0806 |
|     PWR_PP0_ENERGY    |   PWR1  |     151.8518 |
|    PWR_DRAM_ENERGY    |   PWR3  |            0 |
|  PWR_PLATFORM_ENERGY  |   PWR4  |            0 |
+-----------------------+---------+--------------+

+----------------------+------------+
|        Metric        | HWThread 2 |
+----------------------+------------+
|  Runtime (RDTSC) [s] |    12.2666 |
| Runtime unhalted [s] |    31.1697 |
|      Clock [MHz]     |  3882.2245 |
|          CPI         |     1.6262 |
|    Temperature [C]   |         65 |
|      Energy [J]      |   193.0806 |
|       Power [W]      |    15.7403 |
|    Energy PP0 [J]    |   151.8518 |
|     Power PP0 [W]    |    12.3793 |
|    Energy DRAM [J]   |          0 |
|    Power DRAM [W]    |          0 |
|  Energy PLATFORM [J] |          0 |
|  Power PLATFORM [W]  |          0 |
+----------------------+------------+

```