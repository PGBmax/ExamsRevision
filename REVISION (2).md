# FICHE RÉVISION : VECT2

## 📝 Concept
Créer une classe `vect2` représentant un vecteur mathématique 2D contenant des entiers.

## 🎯 Objectifs
- Stocker 2 composantes (x, y) entières
- Addition de vecteurs (`+`)
- Soustraction de vecteurs (`-`)
- Multiplication par un scalaire (`*`)
- Accès aux composantes via `[]` (0 et 1)
- Affichage avec `<<` au format `{x, y}`

## 🔑 Points Clés

### Structure de données
```cpp
class vect2 {
    int _x, _y;
    // OU int _data[2];
public:
    vect2(int x = 0, int y = 0);
};
```

### Opérations mathématiques
- **Addition**: `vect2(x1, y1) + vect2(x2, y2) = vect2(x1+x2, y1+y2)`
- **Soustraction**: `vect2(x1, y1) - vect2(x2, y2) = vect2(x1-x2, y1-y2)`
- **Multiplication par scalaire**: `vect2(x, y) * k = vect2(x*k, y*k)`
  - Attention: gérer `vect2 * int` ET `int * vect2`

### Accès par index
```cpp
int& operator[](int index) {
    // return index == 0 ? _x : _y;
}
const int& operator[](int index) const {
    // version const
}
```

### Affichage
Format: `{x, y}` (avec accolades, espace après la virgule)

## ⚠️ Pièges à éviter
- Oublier la version const de operator[]
- Ne pas gérer les deux sens de multiplication (v*2 et 2*v)
- Mauvais format d'affichage
- Forme canonique orthodoxe manquante
- Ne pas retourner de référence pour operator[]

## 💡 Approche
1. Créer la classe avec 2 attributs (x, y)
2. Constructeur avec valeurs par défaut
3. Implémenter operator+ (retourne nouveau vect2)
4. Implémenter operator- (retourne nouveau vect2)
5. Implémenter operator* (2 versions: vect2*int et int*vect2)
6. Implémenter operator[] (version const et non-const)
7. Implémenter operator<< pour affichage

## 📊 Exemple
```cpp
vect2 v1(2, 3);
vect2 v2(1, 4);
vect2 v3 = v1 + v2;        // {3, 7}
vect2 v4 = v1 * 2;         // {4, 6}
vect2 v5 = 3 * v1;         // {6, 9}
std::cout << v1;           // {2, 3}
int x = v1[0];             // 2
```

## 🔧 Multiplicateurs
Pour `int * vect2`, créer une fonction friend ou globale:
```cpp
friend vect2 operator*(int scalar, const vect2& v);
```
