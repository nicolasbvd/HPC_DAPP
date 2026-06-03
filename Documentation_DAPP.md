# DAPP
**Autheurs**: Nicolas Duprat & Nicolas Bovard

## Installation

### 1. Prérequis Système
Avant d'installer l'outil, assurez-vous de disposer des éléments suivants :
- **Python** : versions 3.10 à 3.13 (*Attention : Python 3.14 présente des problèmes de dépendances*).
- **Compilateur C++** : supportant le standard C++20.
- **CMake** : version 3.15 ou ultérieure.

Pour installer ces prérequis sur des distributions basées sur RPM (comme Fedora) :
```bash
sudo dnf install gcc-c++ cmake python3-devel
```

Pour les distributions basées sur Debian (comme Ubuntu) :
```bash
sudo apt update
sudo apt install g++ cmake python3-dev
```

### 2. Installation Principale (DAPP / DaCe)
L'outil et ses différentes dépendances s'installent facilement via `pip`. Vous avez deux options :

**Option A : Depuis le dépôt officiel (PyPI)**
```bash
pip install dace
```

**Option B : Depuis les sources GitHub (version de développement)**
```bash
pip install git+https://github.com/spcl/dace.git
```

### 3. Dépendances Optionnelles
Selon vos besoins, des modules supplémentaires peuvent être ajoutés :

- **Accélération matérielle (GPU)** :
  - *NVIDIA* : Le toolkit CUDA est requis.
  - *AMD* : ROCm / HIP est nécessaire.
  - L'intégration des tableaux GPU sous Python se fait avec `cupy` : `pip install cupy`
- **Calcul Distribué** : La librairie **MPI** (ex: OpenMPI) doit être installée pour un usage sur plusieurs nœuds.
- **Performances CPU Intel** : L'implémentation **MKL** (ou une alternative BLAS rapide) est fortement recommandée.
  ```bash
  conda install mkl mkl-devel mkl-include
  ```
- **Améliorations Python / Scientifiques** :
  - Optimisation d'expressions tensorielles (*einsum*) : `pip install opt_einsum`
  - Tableaux sparse (creux) / opérations mathématiques : `pip install scipy`
  - Support MLIR : `pip install pymlir readthedocs`

### 4. Extension VS Code
L'écosystème DaCe inclut une extension visuelle pour VS Code qui permet d'éditer et de transformer les graphes (SDFGs).
- **Comment installer** : Recherchez l'extension **SDFV** depuis le marketplace VS Code et installez-la.


## Tests

Afin de vérifier que l'outil DAPP (DaCe) fonctionne correctement, nous allons comparer un code écrit manuellement en C (avec et sans instuctions SIMD) avec un script équivalent écrit en Python et optimisé par DaCe.

### 1. Code C natif (Naïf et SIMD)
Nous utilisons un laboratoire traitant un très grand nombre d'échantillons (`n = 10'000'000`) de vecteurs (x,y,z,b) sur 10 itérations.

*Compilation et exécution du code de test :*
```bash
cd Labos/Lab04/code/src
gcc -O3 -march=native exercice.c -o exercice
./exercice 10000000 1000
```

```text
Arrays energy match.
Arrays score match.
n = 10000000, repeats = 1000
Processing time normal total : 8911 ms
Processing time SIMD total   : 8923 ms
```

### 2. Le script d'optimisation via DaCe
Créez le script Python `exercice_dace.py` dans le répertoire courant. Notez l'utilisation explicite de `dace.map` formuler la boucle de manière très proche du C pour éviter les écritures temporaires non optimisées :

```python
import dace
import numpy as np
import time

dace.config.Config.set('compiler', 'cpu', 'args', value='-std=c++14 -O3 -march=native -fPIC')

N = dace.symbol('N')

@dace.program
def process_samples_dace(x: dace.int32[N], y: dace.int32[N], z: dace.int32[N], b: dace.int32[N], 
                         energy: dace.int32[N], score: dace.int32[N]):
    for i in dace.map[0:N]:
        energy[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i]
        s = (x[i] + y[i] - z[i]) * 3 + b[i] * 5
        if s < -1000:
            score[i] = -1000
        elif s > 1000:
            score[i] = 1000
        else:
            score[i] = s
```

### 3. Exécution et constatation
Lancer le script via la commande :
```bash
python3 exercice_dace.py
```

*Résultats via DAPP :*
```text
n = 10000000, repeats = 1000
Compiling and running warmup...
Processing time DaCe total : 8885 ms
Per run DaCe               : 8.885436 ms
```

### 4. Interprétation du Test
1. **Compilation sous-jacente :** DaCe met quelques secondes au premier appel ("warmup") pour traduire le code Python en un graphe (SDFG) puis le compiler en C++ avec les flags demandés tels que `-O3` et `-march=native`.
2. **Performance exceptionnelle :** L'exécution du script (8885 ms) est équivalente en tout point au code C/SIMD (8923 ms). Le surcoût Python est complètement éliminé !
3. **Ergonomie :** Vous obtenez des performances de niveau SIMD sans devoir utiliser de registres AVX (comme `_mm256_loadu_si256`) ni d'avoir à gérer manuellement les alignements mémoires pour les cas où *n* n'est pas multiple de 8. DaCe prend en charge toute cette complexité.

Si le script réussit à s'exécuter et produit ces métriques sans erreur, l'installation de DaCe est dûment validée.