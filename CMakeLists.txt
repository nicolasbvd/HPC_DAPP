cmake_minimum_required(VERSION 3.10)
project(simd_exercice LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

# --- Chemins DaCe ---

set(DACE_LIB_DIR  ${CMAKE_SOURCE_DIR}/.dacecache/process_samples_dace/build)
set(DACE_LIB_NAME process_samples_dace)
set(DACE_LIB_PATH ${DACE_LIB_DIR}/lib${DACE_LIB_NAME}.so)

add_executable(simd_exercice
    src/exercice.c
    src/my_sdfg.c
)

target_compile_definitions(simd_exercice PRIVATE LIKWID_PERFMON)

target_compile_options(simd_exercice PRIVATE
    -O3 -g -march=native -mavx2
)

target_include_directories(simd_exercice PRIVATE
    ${CMAKE_SOURCE_DIR}/.dacecache/process_samples_dace/include
    $ENV{HOME}/.local/lib/python3.10/site-packages/dace/runtime/include
)

# RPATH inscrit dans le binaire => pas besoin de LD_LIBRARY_PATH au runtime
set_target_properties(simd_exercice PROPERTIES
    BUILD_RPATH ${DACE_LIB_DIR}
)

# --- Lien conditionnel avec DaCe ---
if(EXISTS ${DACE_LIB_PATH})
    target_link_directories(simd_exercice PRIVATE ${DACE_LIB_DIR})
    target_link_libraries(simd_exercice PRIVATE likwid ${DACE_LIB_NAME})
else()
    message(FATAL_ERROR "DaCe library not found at ${DACE_LIB_PATH}.\nRun 'python3 src/exercice_dace.py' to generate the DaCe cache, then configure and build again.")
endif()

# --- OpenMP ---
if(OpenMP_C_FOUND)
    target_link_libraries(simd_exercice PRIVATE OpenMP::OpenMP_C)
endif()
if(OpenMP_CXX_FOUND)
    target_link_libraries(simd_exercice PRIVATE OpenMP::OpenMP_CXX)
endif()