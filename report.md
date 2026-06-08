# **Présentation**

Ce dépôt compare trois implémentations du même noyau (Labo4) :
- une version séquentielle ("normal"),
- une version optimisée avec intrinsics SIMD ("SIMD"),
- une version générée par DaCe (SDFG, nommée `process_samples_dace`).

Objectifs : vérifier la fonctionnalité, comparer latence et efficacité énergétique sur un cœur isolé, et fournir une procédure de test reproductible.

# **Documentation d'installation**

Prérequis système : `cmake`, `make`, `gcc`/`g++`, `python3`. 
Avec un compilateur compatible C++20 (par exemple GCC 10 ou une version plus récente).
CMake 3.15 ou une version plus récente.

Installer dépendances Python (optionnel, recommandé dans un `venv`) :
```bash
python3 -m pip install --upgrade pip
# paquets nécessaires (exemple) : DaCe et NumPy
python3 -m pip install dace numpy
```

pour tout troubleshooting d'installation ou de gestion de CPU veuillez vous référencez a la [documentation](https://spcldace.readthedocs.io/en/latest/setup/installation.html)

# **Procédure de test**

Pour tester l'outil DaCe on a décidé de reprendre le labo 4 ou l'on compare des implémentation normal et avec SIMD. On a donc rajouter une implémentation de `process_samples()` a l'aide de DaCe. Pour la suite de ce rapport nous allons parler de notre implémentation qui est présente sur notre [répo](https://github.com/nicolasbvd/HPC_DAPP)

Pour cela il faut en premier lieux réaliser le code de `process_samples()` en python car DaCe utilise python pour décrire la logique et le transforme ensuite pour pouvoir faire du code c par la suite.

Pour ca on a crée une fonction avec l'annotation `@dace.program` qui va être la définition de notre SDFG.

il faut ensuite générez le SDFG.
```bash
python3 src/exercice_dace.py
```

ensuite on a créer `dace_api.h` pour fait le lien entre le SDFG crée et notre code et tout ca est gérer par `my_sdfg.c`. Il nous faut plus que l'appeler dans `exercice.c`. On va donc maintenant

Build le projet :
```bash
cd build/
cmake ..
make
# binaire : build/simd_exercice
```
 Validation fonctionnelle
```bash
./build/simd_exercice 10000000 1000
# vérifier les sorties "Arrays ... match." et scores
```
# Rapport

** Mesures mono-thread équitables **
On a fait attention car DaCe a tendance a optimiser au maximum l'implémentation on a donc ici forcer l'exécution sur un seul thread pour pouvoir le comparer aux autres implémentation qui elle tourne aussi que sur un thread.

** Mesures LIKWID**
On a réaliser plusieurs mesure avec différente optimisations du compilateur pour voir la différence. Des mesures on été enregistrer avec Likwid sur un ordinateur avec les specs suivantes :
```bash
CPU name:	Intel(R) Core(TM) i7-1065G7 CPU @ 1.30GHz
CPU type:	Intel Icelake processor
```
On a essayer de faire une baseline ainsi que de prendre des valeur seulement il semblerait que je n'ai pas les ressource pour trouver les opérations faites ou likwid n'est pas fait pour ca mais je n'ai pas réussi a avoir de donnée.

**Données recueillies (résumé)**

Les résultats synthétiques tirés des runs enregistrés dans `valeur.md` :

- Temps (mono-thread, total en ms) :
  - `normal` : ~13 115 ms
  - `SIMD`   : ~12 701 ms
  - `SDFG`   : ~21 616 ms

- Indicateurs LIKWID (exemples) :
  - `SIMD` L3 total BW : ~36.8 GB/s
  - `SDFG` L3 total BW :  ~22.2 GB/s
  - Energy (package) exemple : `SIMD` ~214 J vs `SDFG` ~355 J

Observations courtes : la version SIMD est la meilleure en latence et rendement énergétique dans ce cas ; la version SDFG, telle que générée par défaut, présente un overhead et un débit mémoire réduit.

Par contre, l'outil est très intéressant car on se retrouve avec un fichier `process_samples.sdfg` qui nous permet d'appercevoir notre schéma et de la modifier si nécessaire. On se retrouve aussi avec des résultat monothreader qui sont 75% plus lent en moyenne mais qui permette d'optimiser des programmes sans trop d'effort ou de connaissance, car rappelons le que ici le code SIMD tourne en `03 -march=native` et que nous avons limiter le nombre de thread du sdfg sans quoi on se retrouve dans les même temps que le simd (12ms ~). DaCe apport donc un vrai plus pour des ingénieurs qui ne serait pas forcément connaisseur en c mais qui voudrait implémenter des fonctions le plus optimal possible pour du c mais en python.


