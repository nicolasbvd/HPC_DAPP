cmake_minimum_required(VERSION 3.10)
project(simd_exercice LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

add_executable(simd_exercice
    src/exercice.c
    src/my_sdfg.cpp
)

target_compile_definitions(simd_exercice PRIVATE LIKWID_PERFMON)
target_compile_options(simd_exercice PRIVATE
    -O3 -g -march=native -mavx2
)
target_include_directories(simd_exercice PRIVATE
    ${CMAKE_SOURCE_DIR}/src/.dacecache/process_samples_dace/include
    /home/skyrag3/.local/lib/python3.10/site-packages/dace/runtime/include
)

target_link_libraries(simd_exercice PRIVATE likwid
    ${CMAKE_SOURCE_DIR}/src/.dacecache/process_samples_dace/build/libprocess_samples_dace.so
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(simd_exercice PRIVATE OpenMP::OpenMP_CXX)
endif()

