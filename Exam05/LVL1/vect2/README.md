# vect2

Implémentation d'un vecteur mathématique de dimension 2 (entiers) en C++ — sujet d'examen de l'école 42.

## Description

La classe `vect2` représente un vecteur 2D à composantes entières. Elle supporte les opérations arithmétiques usuelles (addition, soustraction, multiplication scalaire) ainsi que la comparaison et l'affichage via `std::ostream`.

## Fichiers

| Fichier      | Description                                     |
|--------------|-------------------------------------------------|
| `v.hpp`      | Déclaration de la classe `vect2`                |
| `v.cpp`      | Implémentation de tous les opérateurs           |
| `main.cpp`   | Programme de test fourni avec le sujet          |
| `subject.txt`| Énoncé officiel de l'examen                     |

## Compilation

```bash
c++ -Wall -Wextra -Werror -std=c++98 v.cpp main.cpp -o vect2
```

## Utilisation

```cpp
#include "v.hpp"

vect2 a(1, 2);
vect2 b(3, 4);

vect2 c = a + b;          // {4, 6}
vect2 d = a * 3;          // {3, 6}
vect2 e = 3 * a;          // {3, 6}

std::cout << c << std::endl;  // {4, 6}

bool eq = (vect2(2, 2) * 2 == vect2(4, 4));  // true
int y = a[1];             // 2
```

## Opérateurs supportés

| Opérateur         | Description                              |
|-------------------|------------------------------------------|
| `+`, `-`          | Addition / soustraction de deux vect2    |
| `-` (unaire)      | Négation                                 |
| `*` (scalaire)    | Multiplication par un entier (des deux côtés) |
| `+=`, `-=`, `*=`  | Versions en place                        |
| `++`, `--`        | Pré/post-incrémentation                  |
| `==`, `!=`        | Comparaison                              |
| `[]`              | Accès aux composantes (0 = x, 1 = y)    |
| `<<`              | Affichage `{x, y}`                       |
