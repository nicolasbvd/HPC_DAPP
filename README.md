# DAPP — DaCe Example and Tests

Contenu du dossier :

- `Documentation_DAPP.md` : guide d'installation et procédure de test (comparaison C vs DaCe).
- `exercice_dace.py` : script DaCe reproduisant `Labos/Lab04` kernel, génère `process_samples.sdfg` et `process_samples.cpp`.
- `process_samples.sdfg`, `process_samples.cpp` : SDFG et code généré (créés après première exécution du script).

Exemples d'utilisation :

1. Installer les dépendances Python (préconisé dans un `venv` ou conda) :
```bash
python3 -m pip install --upgrade pip
pip install dace numpy
```

2. Lancer le benchmark DaCe et générer les artefacts :
```bash
python3 exercice_dace.py
# ou pour ouvrir la vue SDFV (si extension installée) :
python3 exercice_dace.py --view
```

3. Compiler et exécuter la version C de comparaison :
```bash
cd ../Labos/Lab04/code/src
gcc -O3 -march=native exercice.c -o exercice
./exercice 10000000 1000
```

4. Fichiers générés par DaCe :
- `process_samples.sdfg` : ouvrez-le avec l'extension SDFV dans VS Code.
- `process_samples.cpp` : code C++ généré — utile pour captures d'écran et comparaison.

Licence: aucun — travail de cours.
