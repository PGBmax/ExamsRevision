# GameOfLife

Implémentation du **Jeu de la Vie** de Conway en C.

## Description

Le programme simule le Jeu de la Vie sur une grille de dimensions données. L'état initial est dessiné via des commandes reçues sur l'entrée standard, puis le programme simule le nombre d'itérations demandé et affiche le résultat.

## Compilation

```bash
cc -Wall -Wextra -Werror -g3 -o GameOfLife GameOfLife.c
```

## Utilisation

```bash
echo '<commandes>' | ./GameOfLife <width> <height> <iterations>
```

### Arguments

| Argument     | Description                             |
|--------------|-----------------------------------------|
| `width`      | Largeur de la grille (colonnes)         |
| `height`     | Hauteur de la grille (lignes)           |
| `iterations` | Nombre d'itérations à simuler          |

### Commandes (stdin)

Le crayon démarre en haut à gauche de la grille.

| Commande | Action                                        |
|----------|-----------------------------------------------|
| `w`      | Déplacer le crayon vers le haut               |
| `s`      | Déplacer le crayon vers le bas                |
| `a`      | Déplacer le crayon vers la gauche             |
| `d`      | Déplacer le crayon vers la droite             |
| `x`      | Lever / poser le crayon (toggle dessin)       |

Les cellules vivantes sont représentées par `O`, les cellules mortes par un espace.

## Règles du Jeu de la Vie

- Une cellule vivante avec **2 ou 3 voisins vivants** survit.
- Une cellule morte avec **exactement 3 voisins vivants** devient vivante.
- Toute autre cellule meurt ou reste morte.
- Les cellules hors de la grille sont considérées comme mortes.

## Exemples

```bash
# Blinker (oscillateur de période 2) — itération 0
$ echo 'dxss' | ./GameOfLife 3 3 0
 O
 O
 O

# Blinker — itération 1 (rotation 90°)
$ echo 'dxss' | ./GameOfLife 3 3 1

OOO

# Blinker — itération 2 (retour à l'état initial)
$ echo 'dxss' | ./GameOfLife 3 3 2
 O
 O
 O

# Générateur de vaisseau (Gosper Glider Gun) — itération 0
$ echo 'sdddddddddddddddddddddddddxsxaaxxasxssawwxaaaaaaaxaxaaaaaaaaaaaassxsdwxwddddddddddxxddddxxdsxsdasxsaxxwwaxxsssaxaxwaxxwaxwwxddddddddddddsxxddxsxddddddddddwwwxwdsx' | ./GameOfLife 40 40 0
                         O
                       O O
             OO      OO            OO
            O   O    OO            OO
 OO        O     O   OO
 OO        O   O OO    O O
           O     O       O
            O   O
             OO
```