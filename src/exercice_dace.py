import dace
import numpy as np
import time

# Forcer les flags de compilation C++ en arrière-plan pour être 100% équitable
dace.config.Config.set('compiler', 'cpu', 'args', value='-std=c++14 -O3 -march=native -fPIC')

# Define variables for Dace (N is our array size)
N = dace.symbol('N')

@dace.program
def process_samples_dace(x: dace.int32[N], y: dace.int32[N], z: dace.int32[N], b: dace.int32[N], energy: dace.int32[N], score: dace.int32[N]):
    for i in dace.map[0:N]:
        # Calcul des normes élément par élément
        energy[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i]
        
        # Calcul du score unitaire
        s = (x[i] + y[i] - z[i]) * 3 + b[i] * 5
        
        # Clamp manuel (évite les allocations de vectorisation globales)
        if s < -1000:
            score[i] = -1000
        elif s > 1000:
            score[i] = 1000
        else:
            score[i] = s

def main():
    n_val = 10000000
    repeats = 1000
    import sys
    view = False
    if '--view' in sys.argv:
        view = True

    print(f"n = {n_val}, repeats = {repeats}")

    # Initialize data identically to the C version
    i = np.arange(n_val, dtype=np.int32)
    base = i * 3 + 7
    
    x = (base % 50) - 25
    y = ((base * 2) % 60) - 30
    z = ((base * 5) % 40) - 20
    b = (i % 8) - 4
    
    energy = np.zeros(n_val, dtype=np.int32)
    score = np.zeros(n_val, dtype=np.int32)

    # 1. First run to compile the C++ code and warm up
    print("Compiling and running warmup...")
    process_samples_dace(x, y, z, b, energy, score, N=n_val)

    # Generate and save SDFG + generated C++ for inspection (useful for slides / SDFV)
    try:
        sdfg = process_samples_dace.to_sdfg()
        sdfg.save("process_samples.sdfg")
        code = sdfg.generate_code()
        with open("process_samples.cpp", "w") as f:
            f.write(code)
        print("Saved process_samples.sdfg and process_samples.cpp")
        if view:
            sdfg.view()
    except Exception as e:
        print("Warning: failed to generate/save SDFG or code:", e)

    # 2. Benchmark loop
    start_time = time.time()
    for _ in range(repeats):
        process_samples_dace(x, y, z, b, energy, score, N=n_val)
    end_time = time.time()

    total_ms = (end_time - start_time) * 1000
    print(f"Processing time DaCe total : {total_ms:.0f} ms")
    print(f"Per run DaCe               : {total_ms / repeats:.6f} ms")

if __name__ == '__main__':
    main()
