# DAPP
**Autheurs**: Nicolas Duprat & Nicolas Bovard

## Présentation
Ce laboratoire présente l'outil DAPP, developpé à l'ETHZ. Il y a la documentation d'installation et une procédure de test.  
La procédure compare trois implémentations du même noyau :
- une version séquentielle ("normal"),
- une version optimisée avec intrinsics SIMD ("SIMD"),
- une version générée par DaCe (SDFG, nommée `process_samples_dace`).

**Objectifs** : vérifier la fonctionnalité, comparer latence et efficacité énergétique sur un cœur isolé, et fournir une procédure de test reproductible.

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

pour tout troubleshooting d'installation ou de gestion de CPU veuillez vous référencez a la [documentation](https://spcldace.readthedocs.io/en/latest/setup/installation.html)

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

## Procédure de test

Pour tester l’outil DaCe, nous avons repris le labo 4, dans lequel on compare une implémentation séquentielle et une implémentation SIMD. Nous y avons ajouté une version équivalente générée avec DaCe, appelée `process_samples_dace`. Le code source utilisé pour cette étude est disponible sur notre répo : [HPC_DAPP](https://github.com/nicolasbvd/HPC_DAPP).

L’objectif de cette procédure est double : vérifier que l’outil fonctionne correctement, puis comparer les performances et l’efficacité énergétique des trois versions sur un même noyau de calcul.

La première étape consiste à décrire le traitement en Python, car DaCe utilise ce langage pour représenter la logique du programme avant transformation. La fonction est annotée avec `@dace.program`, ce qui permet de définir le SDFG.

Ensuite, on génère le SDFG en lançant le script Python du programme que l'on a écrit :
```bash
python3 exercice_dace.py
```

Cette étape sert aussi de premier test fonctionnel, car DaCe doit réussir à construire le graphe et à préparer la compilation.

La deuxième étape consiste à relier ce SDFG au code C du projet. Pour cela, nous avons ajouté un fichier `dace_api.h` pour faire le lien avec le graphe généré, et `my_sdfg.c` pour encapsuler l’appel à DaCe. L’intégration finale se fait ensuite dans `exercice.c`.

Le projet est ensuite compilé avec CMake :

```bash
cd build/
cmake ..
make
```

Le binaire généré est simd_exercice.

La validation fonctionnelle se fait en lançant :

```bash
./build/simd_exercice 10000000 1000
```

### Partie visuelle DaCe
L’un des intérêts de DaCe est qu’il permet aussi de visualiser le programme sous forme de graphe SDFG. Pour cela, il faut installer l’extension visuelle SDFV dans VS Code, puis ouvrir le fichier SDFG généré par DaCe. Cette visualisation permet d’inspecter la structure du calcul et de vérifier que la transformation produite correspond bien à ce que l’on attend.

Dans notre cas, le graphe doit rester simple :

- les tableaux x, y, z et b apparaissent comme entrées,
- une map représente la boucle sur i,
- un tasklet effectue le calcul de energy et score,
- les tableaux de sortie sont écrits directement,
- le nombre de temporaires intermédiaires doit rester faible.

L’interprétation du graphe est importante, car elle permet de comprendre les performances obtenues. Un SDFG simple, avec peu de copies mémoire et peu de buffers temporaires, est généralement plus favorable à l’optimisation. À l’inverse, un graphe plus fragmenté peut révéler une transformation moins efficace et donc expliquer une baisse de performance.

[Voir le graphe DaCe en PDF](Annexe/process_samples_dace.pdf)

### Mesure et analyse

Une fois la correction fonctionnelle validée, on passe aux mesures de performance et d’énergie. L’objectif n’est pas seulement de comparer des temps, mais aussi de comprendre dans quelles conditions DaCe est compétitif et ce que révèlent les compteurs matériels sur le comportement du programme.

Les mesures mono-threadées constituent la référence la plus juste pour comparer les trois implémentations. On évite ainsi que DaCe profite d’un parallélisme différent de celui des autres versions. Dans ce cadre, la version SIMD reste la plus rapide, la version séquentielle est légèrement derrière, et la version SDFG est plus lente. Les résultats observés dans `valeur.md` montrent typiquement un ordre de grandeur d’environ 12 à 13 ms pour les versions séquentielle et SIMD, contre environ 21 à 22 ms pour la version SDFG.

Dans le fichier `valeurs.md`, les tests sont divisés en 2 groupes: Le groupe `HPC` permet d’analyser les performances du programme, notamment le temps d’exécution, le nombre d’instructions et la bande passante mémoire. Le groupe `ENERGY` mesure la consommation et la puissance du processeur pendant l’exécution.

Les mesures LIKWID confirment cette tendance. Avec le groupe `HPC`, la version SIMD atteint une bande passante mémoire plus élevée que la version SDFG, alors que le SDFG retire davantage d’instructions pour un temps d’exécution plus long. Avec le groupe `ENERGY`, on observe également que la consommation package de la version SDFG est plus importante que celle de SIMD, ce qui est cohérent avec son runtime supérieur. Autrement dit, dans cette configuration, le SDFG n’apporte pas le meilleur compromis performance/énergie.

Les essais avec `-march=native` montrent enfin un point important d’interprétation : le compilateur C peut déjà optimiser fortement le noyau de départ, ce qui réduit l’écart entre la version séquentielle et la version SIMD. Dans certaines configurations, la version SDFG se rapproche davantage du SIMD lorsque le parallélisme n’est pas bridé, mais en mono-thread elle reste globalement plus coûteuse. Cela signifie que DaCe fournit bien un modèle de calcul correct et exploitable, mais que ses performances dépendent fortement du niveau d’optimisation choisi, du nombre de threads et de la façon dont le graphe est généré.

En résumé, les résultats valident le bon fonctionnement de l’outil, montrent que la version SIMD manuelle reste la plus efficace dans notre configuration de référence, et mettent en évidence l’intérêt principal de DaCe : la lisibilité du graphe SDFG, la possibilité d’inspecter la transformation produite et la capacité à générer automatiquement un code correct à partir d’une description Python.

