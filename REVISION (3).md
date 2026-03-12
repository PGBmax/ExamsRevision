# FICHE RÉVISION : BSQ (Biggest Square)

## 📝 Concept
Trouver le plus grand carré possible sur une carte en évitant les obstacles.

## 🎯 Objectifs
- Lire une carte depuis un fichier ou stdin
- Parser la première ligne (nb_lignes, char_vide, char_obstacle, char_plein)
- Trouver le plus grand carré sans obstacles
- Remplir le carré trouvé avec le caractère "plein"
- Gérer plusieurs cartes en arguments
- Afficher "map error" sur stderr si carte invalide

## 🔑 Format de la carte

### Première ligne
`N empty_char obstacle_char full_char` (séparés par espaces)
- N = nombre de lignes
- 3 caractères différents (imprimables, peuvent être des chiffres)

### Lignes suivantes
- N lignes de même longueur
- Composées de char_vide et char_obstacle

## 🧮 Algorithme (Dynamic Programming)

### Approche naïve: O(n³)
Pour chaque position, tester toutes les tailles de carrés possibles

### Approche optimale: O(n²) - DP
```
Créer une matrice DP de même taille que la carte

Pour chaque case (i, j):
    Si c'est un obstacle:
        dp[i][j] = 0
    Sinon si c'est sur le bord (i=0 ou j=0):
        dp[i][j] = 1
    Sinon:
        dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1

max_size = max(dp[i][j])
position = position où max_size est trouvé
```

### Logique DP
`dp[i][j]` = taille du plus grand carré dont le coin inférieur-droit est en (i,j)

## 🔑 Points Clés

### Parsing
1. Lire la première ligne (getline)
2. Parser: nb_lignes, 3 caractères
3. Valider: 3 caractères différents, nb correct

### Validation de carte
- Toutes les lignes de même longueur
- Au moins 1 ligne d'au moins 1 case
- Seuls les caractères définis sont présents
- 3 caractères tous différents

### Choix en cas d'égalité
Si plusieurs carrés de même taille maximale:
1. Celui le plus en haut
2. En cas d'égalité, celui le plus à gauche

### Affichage
- Remplacer les cases du carré trouvé par char_plein
- Si plusieurs cartes: séparer par line break
- Erreurs sur stderr, résultats sur stdout

## ⚠️ Pièges à éviter
- Ne pas valider la carte correctement
- Oublier le cas stdin (pas d'arguments)
- Ne pas gérer plusieurs fichiers en arguments
- Bug dans le choix du carré (priorité haut puis gauche)
- Fuites mémoire (malloc/free)
- Ne pas gérer les caractères spéciaux (espaces, nombres, etc.)
- Buffer overflow lors de la lecture

## 💡 Approche

### Étape 1: Structure
```c
typedef struct {
    int rows;
    int cols;
    char empty;
    char obstacle;
    char full;
    char **grid;
} map_t;
```

### Étape 2: Parsing
1. Fonction pour lire la première ligne
2. Fonction pour parser les paramètres
3. Fonction pour lire les lignes de la carte
4. Fonction de validation

### Étape 3: Résolution
1. Allouer matrice DP
2. Remplir matrice selon l'algo
3. Trouver le max et sa position prioritaire
4. Remplir le carré dans la grille originale

### Étape 4: Gestion multi-cartes
```c
int main(int ac, char **av) {
    if (ac == 1) {
        // Lire depuis stdin
        solve_map(stdin);
    } else {
        for (int i = 1; i < ac; i++) {
            FILE *f = fopen(av[i], "r");
            if (!f) {
                fprintf(stderr, "map error\n");
                continue;
            }
            solve_map(f);
            fclose(f);
        }
    }
}
```

## 📊 Complexité
- **Temps**: O(rows × cols) pour l'algorithme DP
- **Espace**: O(rows × cols) pour la matrice DP

## 🧪 Tests edge cases
- Carte 1×1
- Aucun obstacle (tout est le carré)
- Que des obstacles (carré de taille 0 ou 1)
- Caractères numériques ou spéciaux
- Première ligne invalide
- Lignes de longueurs différentes
