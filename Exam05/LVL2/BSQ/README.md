# BSQ — Biggest Square

Trouve le plus grand carré vide sur une carte en évitant les obstacles — sujet d'examen de l'école 42.

## Description

`bsq` lit une ou plusieurs cartes (fichiers ou stdin), localise le plus grand carré composé uniquement de cases vides, le remplace par le caractère « plein », et affiche la carte résultante.

## Fichiers

| Fichier      | Description                                    |
|--------------|------------------------------------------------|
| `bsq.c`      | Implémentation complète                        |
| `bsq.h`      | Structures et prototypes                       |
| `Makefile`   | Règles de compilation                          |
| `Subject.txt`| Énoncé officiel de l'examen                    |

## Compilation

```bash
make
```

## Utilisation

```bash
# Depuis un fichier
./bsq <map_file> [map_file2 ...]

# Depuis stdin
./bsq < map_file
echo '...' | ./bsq
```

## Format de la carte

La **première ligne** contient les métadonnées (séparées par des espaces) :
```
<nb_lignes> <vide> <obstacle> <plein>
```

Les lignes suivantes forment la grille, composée uniquement des caractères `vide` et `obstacle`.

### Exemple
```
9 . o x
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................
```

Sortie :
```
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxxo..............
.....xxxxxxx...............
....oxxxxxxx...............
.....xxxxxxx...o...........
.....xxxxxxx...............
......o..............o.....
..o.......o................
```

## Carte invalide

Une carte est invalide si :
- les lignes n'ont pas toutes la même longueur
- il n'y a aucune ligne ou aucune colonne
- la première ligne est mal formée (champs manquants, caractères identiques, non-imprimables…)
- les lignes contiennent un caractère autre que `vide` ou `obstacle`
- une ligne ne se termine pas par `\n`

Dans ce cas, `map error` est affiché sur `stderr` et le programme passe à la carte suivante.

## Algorithme

Programmation dynamique O(H × W) :

$$dp[r][c] = \min(dp[r-1][c],\ dp[r][c-1],\ dp[r-1][c-1]) + 1$$

avec $dp[r][c] = 0$ si la case est un obstacle.

En cas d'égalité de taille, le carré le plus haut puis le plus à gauche est retenu.
