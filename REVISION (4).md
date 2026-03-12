# FICHE RÉVISION : GAME OF LIFE

## 📝 Concept
Simuler le jeu de la vie de Conway sur une grille avec une configuration initiale dessinée via des commandes.

## 🎯 Objectifs
- Lire des commandes depuis stdin pour dessiner la configuration initiale
- Simuler N itérations du jeu de la vie
- Afficher le résultat ('0' pour vivant, ' ' pour mort)
- Gestion de grille de dimensions width × height

## 🎮 Commandes d'initialisation

### Concept du "stylo"
Commence en haut à gauche (0, 0) avec le stylo levé.

### Commandes
- `w` : Haut (y--)
- `a` : Gauche (x--)
- `s` : Bas (y++)
- `d` : Droite (x++)
- `x` : Lever/baisser le stylo (toggle)

Quand le stylo est baissé, il dessine sur toutes les cases traversées.

## 🔬 Règles du Jeu de la Vie

Pour chaque cellule, compter les 8 voisins vivants:

### Cellule vivante
- **< 2 voisins** → Meurt (sous-population)
- **2-3 voisins** → Survit
- **> 3 voisins** → Meurt (surpopulation)

### Cellule morte
- **Exactement 3 voisins** → Devient vivante (reproduction)

⚠️ **Important**: Toutes les modifications se font SIMULTANÉMENT (utiliser 2 grilles ou copie)

## 🔑 Points Clés

### Structure de données
```c
typedef struct {
    int width;
    int height;
    char **grid;  // 0 = mort, 1 = vivant
} board_t;
```

### Parsing des commandes
```c
int x = 0, y = 0;
int pen_down = 0;

while ((c = getchar()) != EOF) {
    if (c == 'x') {
        pen_down = !pen_down;
    } else {
        if (pen_down && in_bounds(x, y)) {
            grid[y][x] = 1;
        }
        // Déplacer selon w/a/s/d
    }
}
```

### Comptage des voisins
```c
int count_neighbors(char **grid, int x, int y, int w, int h) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                count += grid[ny][nx];
            }
        }
    }
    return count;
}
```

### Simulation d'une itération
```c
void simulate(board_t *board) {
    char **next = create_empty_grid(board->width, board->height);
    
    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            int neighbors = count_neighbors(board->grid, x, y, 
                                           board->width, board->height);
            if (board->grid[y][x]) {
                // Vivante
                next[y][x] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                // Morte
                next[y][x] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
    
    // Remplacer l'ancienne grille
    free_grid(board->grid);
    board->grid = next;
}
```

### Affichage
```c
void print_board(board_t *board) {
    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            putchar(board->grid[y][x] ? '0' : ' ');
        }
        putchar('\n');
    }
}
```

## ⚠️ Pièges à éviter
- Modifier la grille en place (toutes les modifications doivent être simultanées)
- Ne pas gérer les bords (cellules hors grille sont mortes)
- Oublier le toggle du stylo (x peut être appelé plusieurs fois)
- Ne pas vérifier les limites lors du dessin
- Compter la cellule elle-même comme voisin
- Fuites mémoire (allocation de grilles)
- Mauvaise gestion des arguments (width, height, iterations)

## 💡 Approche

### Étape 1: Parsing des arguments
```c
int main(int ac, char **av) {
    if (ac != 4) return 1;
    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iterations = atoi(av[3]);
    // ...
}
```

### Étape 2: Initialisation
1. Créer grille de width × height initialisée à 0
2. Lire les commandes depuis stdin
3. Dessiner selon les commandes (x, y, pen_down)

### Étape 3: Simulation
```c
for (int i = 0; i < iterations; i++) {
    simulate(board);
}
```

### Étape 4: Affichage
Parcourir la grille et afficher '0' ou ' '

## 📊 Complexité
- **Initialisation**: O(commandes)
- **Simulation par itération**: O(width × height × 9) = O(width × height)
- **Total**: O(iterations × width × height)

## 🧪 Exemples à tester

### Oscillateurs
- Blinker (ligne de 3)
  ```
  .0.    ...
  .0. -> 000
  .0.    ...
  ```

### Patterns stables
- Block (2×2)
  ```
  00
  00  (reste identique)
  ```

### Edge cases
- Grille 1×1
- 0 itérations (juste afficher l'initial)
- Pattern qui touche les bords
- Commandes qui sortent de la grille
