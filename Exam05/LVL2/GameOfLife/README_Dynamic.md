# DynamicGameOfLife

Version animée et colorée du **Jeu de la Vie** de Conway — extension de [GameOfLife](README.md).

## Différences avec GameOfLife

| Fonctionnalité         | GameOfLife | DynamicGameOfLife |
|------------------------|------------|-------------------|
| Affichage animé        | ✗          | ✓                 |
| Couleurs ANSI          | ✗          | ✓                 |
| Bordure de grille      | ✗          | ✓                 |
| Paramètre de vitesse   | ✗          | ✓                 |
| Gestion SIGINT/SIGQUIT | ✗          | ✓                 |
| Cellules naissantes    | `O`        | `█` jaune         |
| Cellules survivantes   | `O`        | `█` vert          |

## Compilation

```bash
cc -Wall -Wextra -Werror -g3 -o DynamicGameOfLife DynamicGameOfLife.c
```

## Utilisation

```bash
echo '<commandes>' | ./DynamicGameOfLife <width> <height> <iterations> <speed>
```

### Arguments

| Argument     | Description                                        |
|--------------|----------------------------------------------------|
| `width`      | Largeur de la grille (colonnes)                    |
| `height`     | Hauteur de la grille (lignes)                      |
| `iterations` | Nombre d'itérations à simuler                     |
| `speed`      | Délai entre chaque frame en millisecondes          |

### Commandes (stdin)

Le crayon démarre en haut à gauche de la grille.

| Commande | Action                                        |
|----------|-----------------------------------------------|
| `w`      | Déplacer le crayon vers le haut               |
| `s`      | Déplacer le crayon vers le bas                |
| `a`      | Déplacer le crayon vers la gauche             |
| `d`      | Déplacer le crayon vers la droite             |
| `x`      | Lever / poser le crayon (toggle dessin)       |

## Affichage

Chaque frame efface le terminal et affiche :
- Un titre avec le numéro de génération en cours
- La grille encadrée avec des caractères box-drawing (`┌─┐│└┘`)
- Les cellules vivantes en `█` coloré :
  - **Vert** — cellule survivante (vivante depuis la génération précédente)
  - **Jaune** — cellule naissante (vient de devenir vivante)

## Gestion des signaux

`SIGINT` (Ctrl+C) et `SIGQUIT` (Ctrl+\) sont interceptés : la mémoire est libérée proprement avant de quitter.

## Exemples

```bash
# Blinker animé — 10 itérations, 200ms par frame
$ echo 'dxss' | ./DynamicGameOfLife 10 10 10 200

# Générateur de vaisseau (Gosper Glider Gun) — 100 itérations, 100ms par frame
$ echo 'sdddddddddddddddddddddddddxsxaaxxasxssawwxaaaaaaaxaxaaaaaaaaaaaassxsdwxwddddddddddxxddddxxdsxsdasxsaxxwwaxxsssaxaxwaxxwaxwwxddddddddddddsxxddxsxddddddddddwwwxwdsx' | ./DynamicGameOfLife 40 40 100 100
```
