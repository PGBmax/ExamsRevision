# FICHE RÉVISION : POLYSET

## 📝 Concept
Implémenter des bags cherchables et une classe set en utilisant l'héritage multiple et le polymorphisme.

## 🎯 Objectifs
**Partie 1**: Créer `searchable_array_bag` et `searchable_tree_bag`
**Partie 2**: Créer la classe `set` qui wrap un searchable_bag

## 🔑 Hiérarchie de classes

```
        bag (abstract)              searchable_bag (abstract)
           |                                |
    ----------------                        |
    |              |                        |
array_bag      tree_bag                    |
    |              |                        |
    ----------------                        |
           |                                |
    searchable_array_bag --------------------
    searchable_tree_bag  --------------------
           |
         set (composition)
```

## 📦 Partie 1: Searchable Bags

### searchable_array_bag
- Hérite de `array_bag` et implémente `searchable_bag`
- Cherche dans le tableau séquentiellement
- Implémente `contains(const T& item)` et autres méthodes de recherche

### searchable_tree_bag
- Hérite de `tree_bag` et implémente `searchable_bag`
- Cherche dans l'arbre binaire de recherche
- Implémente `contains(const T& item)` avec recherche BST

## 🎒 Partie 2: Set

### Concept Set vs Bag
- **Bag**: Peut contenir des doublons
- **Set**: Pas de doublons

### Implémentation
```cpp
class set {
    searchable_bag* _bag;  // Composition
public:
    void insert(const T& item) {
        if (!_bag->contains(item)) {
            _bag->add(item);
        }
    }
};
```

## 🔑 Points Clés

### Héritage multiple
- `searchable_array_bag : public array_bag, public searchable_bag`
- Attention au diamond problem potentiel
- Utiliser l'héritage virtuel si nécessaire

### Forme canonique orthodoxe
- Constructeur par défaut
- Constructeur de copie
- Opérateur d'assignation
- Destructeur (virtuel pour classes de base!)

### Méthodes abstraites
- Les classes abstraites ont des méthodes virtuelles pures
- Implémenter TOUTES les méthodes virtuelles pures dans les classes concrètes

### Méthodes const
- Ne pas oublier le `const` sur les méthodes qui ne modifient pas l'objet
- `contains()`, `size()`, etc. doivent être const

## ⚠️ Pièges à éviter
- Oublier les destructeurs virtuels
- Ne pas implémenter toutes les méthodes abstraites
- Oublier le const sur les méthodes appropriées
- Fuites mémoire dans set (bien gérer le pointeur)
- Ne pas gérer la copie profonde

## 💡 Approche

### Étape 1: searchable_array_bag
1. Hériter de array_bag et searchable_bag
2. Implémenter contains() avec boucle sur le tableau
3. Implémenter autres méthodes de recherche

### Étape 2: searchable_tree_bag
1. Hériter de tree_bag et searchable_bag
2. Implémenter contains() avec recherche dans BST
3. Implémenter autres méthodes de recherche

### Étape 3: set
1. Composer avec un searchable_bag (pointer ou objet)
2. Dans insert(), vérifier contains() avant d'ajouter
3. Wrapper toutes les méthodes nécessaires
4. Gérer la mémoire (constructeur/destructeur/copie)

## 📊 Complexité
- **array_bag recherche**: O(n)
- **tree_bag recherche**: O(log n) moyen, O(n) pire cas
- **set insert**: coût de recherche + coût d'ajout
