# FICHE RÉVISION : BIGINT

## 📝 Concept
Créer une classe `bigint` pour gérer des entiers de précision arbitraire (plus grands que SIZE_MAX).

## 🎯 Objectifs
- Stocker un nombre arbitrairement grand (utiliser un vecteur/string/tableau)
- Implémenter addition (`+`)
- Implémenter comparaisons (`<`, `>`, `==`, `!=`, `<=`, `>=`)
- Implémenter "digitshift" (`<<`, `>>`) - décalage de chiffres en base 10
- Affichage avec `<<` (ostream) sans zéros de tête

## 🔑 Points Clés

### Structure de données
```cpp
class bigint {
    std::string digits;  // Stockage des chiffres (LSB ou MSB first)
    // OU std::vector<int> digits;
};
```

### Addition
- Additionner chiffre par chiffre avec retenue
- Parcourir du chiffre de poids faible au plus fort
- Ne pas oublier la dernière retenue

### Comparaison
- Comparer d'abord la longueur
- Si même longueur, comparer chiffre par chiffre (du plus significatif)

### Digitshift
- `<<` : Ajouter N zéros à droite (ex: 42 << 3 = 42000)
- `>>` : Supprimer N chiffres à droite (ex: 1337 >> 2 = 13)

### Affichage
- Supprimer les zéros de tête
- Cas particulier: "0" si tous les chiffres sont 0

## ⚠️ Pièges à éviter
- Zéros de tête dans l'affichage
- Gestion des retenues en addition
- Comparaison des longueurs différentes
- Shift plus grand que le nombre de chiffres
- Forme canonique orthodoxe (constructeur, destructeur, copie, assignation)

## 💡 Approche
1. Décider si stocker MSB-first ou LSB-first
2. Implémenter constructeurs (de string, d'int, de copie)
3. Implémenter addition (boucle avec retenue)
4. Implémenter comparaisons (longueur puis chiffres)
5. Implémenter shifts (ajout/suppression de zéros)
6. Implémenter operator<< pour affichage

## 📊 Complexité
- Addition: O(n) où n = nombre de chiffres
- Comparaison: O(n)
- Shift: O(n)
