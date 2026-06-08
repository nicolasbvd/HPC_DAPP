# DAPP — DaCe example and tests 

Ce dépôt contient un exemple comparant trois implémentations. Cela reprend un travail réaliser lors du labo4 de HPC :
- implémentation séquentielle (``normal``)
- implémentation optimisée avec intrinsics SIMD (``SIMD``)
- implémentation générée par DaCe (SDFG / ``process_samples_dace``)

Fichiers importants
- `src/` : code source du bench, wrappers et SDFG wrapper (`exercice.c`, `my_sdfg.cpp`, `my_sdfg.h`, `exercice_dace.py`).
- `.dacecache/process_samples_dace` : cache DaCe (SDFG, includes, build) généré après exécution de `exercice_dace.py`.
- `valeur.md` : résultats et sorties LIKWID collectés.
- `requirements.txt` : dépendances Python utiles pour DaCe.

Prérequis
- Python 3 (préférer un virtualenv / conda)
- CMake, make, gcc/clang, g++
- LIKWID (pour instrumentation performance/énergie) — facultatif mais recommandé
- DaCe Python package (optionnel si vous n'avez pas besoin de regénérer la lib C++)

Installation Python (optionnelle)
```bash
python3 -m pip install --upgrade pip
python3 -m pip install -r requirements.txt
```

Générer les artefacts DaCe (optionnel)
- Le script `src/exercice_dace.py` génère la SDFG a l'aide d'une fonction annotée de `@dace.program` et les sources C++ dans `.dacecache/process_samples_dace`.
- Exemple :
```bash
python3 src/exercice_dace.py
# si vous voulez visualiser avec SDFG vous pouvez installer une extension VsCode du même nom (SDFG ou DaCe IOE)
```

Build du binaire principal une fois le SDFG crée
```bash
# à la racine du dépôt
cmake -S . -B build
cmake --build build -j4
# exécutable : build/simd_exercice
```

Exécution et benchmarks
- Exécution simple :
```bash
./build/simd_exercice 10000000 1000
```


Validation
- Le programme imprime des messages confirmant que les tableaux résultats se correspondent entre implémentations.

Résultats
- Consultez `valeur.md` pour les sorties LIKWID et les runs précédents sur un ordinateur avec les specs suivantes :
```bash
CPU name:	Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz
CPU type:	Intel Icelake processor
```

dépannage rapide
- Si la compilation ou le link échoue sur les symboles `process_samples_sdfg_*` : assurez-vous que `.dacecache/process_samples_dace/build/libprocess_samples_dace.so` existe et que `CMakeLists.txt` inclut le chemin vers `.dacecache/.../include` et link la lib.
- Si le script DaCe génère des chemins absolus erronés, supprimez le dossier `.dacecache/process_samples_dace/build` et regénérez avec `python3 src/exercice_dace.py`.

# Présentation
La présentation est présente dans le dossier reveal.js, il suffit juste de télécherger les dépendances a l'aide de `npm install` et ensuite de le lancer a l'aide de `npm start`.
