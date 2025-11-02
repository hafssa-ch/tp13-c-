# TP 12 : Surcharge d'opérateurs et Templates Avancés en C++

Ce TP couvre quatre exercices avancés en C++ : conteneurs génériques, matrices, piles sécurisées et foncteurs de tri avec concepts C++20.  
Il permet de pratiquer la surcharge d'opérateurs, les templates, les pointeurs intelligents et les concepts.

---

## Exercice 1 – Conteneur dynamique générique avec itérateur personnalisé

### Objectifs pédagogiques
- Créer un conteneur similaire à `std::vector` sans utiliser la STL.
- Implémenter un itérateur bidirectionnel compatible avec les boucles `range-based for`.

### Travail demandé
- Créer une classe template `ArrayDyn<T>` gérant capacité, taille courante et pointeur dynamique.
- Méthodes : `push_back(const T&)`, `pop_back()`, `operator[](std::size_t)` avec contrôle de bornes.
- Itérateur interne avec `operator*`, `operator++`, `operator--`, `operator!=`.
- Méthodes `begin()` et `end()` pour l’itérateur.
- Tester avec `int`, `std::string` et des objets personnalisés.
<img width="649" height="265" alt="image" src="https://github.com/user-attachments/assets/8a63c53c-ff2c-40a0-a776-c3c61ee69446" />

---

## Exercice 2 – Matrice générique + opérateurs arithmétiques

### Objectifs pédagogiques
- Manipuler des templates avec paramètres multiples.
- Surcharger les opérateurs `+`, `*` pour des matrices de taille fixe.

### Travail demandé
- Créer un template `Matrice<T, N, M>` avec tableau statique `T data[N][M]`.
- Constructeurs : par défaut (0) et avec liste d’initialisation.
- Surcharger :
  - `operator+` pour addition élément par élément
  - `operator*` pour produit matriciel
  - `operator<<` (ami) pour affichage
- Tester avec `int` et `double`. Optionnel : spécialisation `bool` pour produit logique.
<img width="474" height="461" alt="image" src="https://github.com/user-attachments/assets/d61a7192-fcee-498a-9830-d470ed56d9fa" />

---

## Exercice 3 – Pile générique sécurisée avec `std::unique_ptr`

### Objectifs pédagogiques
- Utiliser templates et pointeurs intelligents pour gestion automatique de la mémoire.
- Implémenter des exceptions personnalisées.

### Travail demandé
- Créer `Stack<T>` utilisant `unique_ptr<T[]>`.
- Attributs : `capacity`, `top`.
- Méthodes : `push(const T&)`, `pop()`, `peek() const`, `empty() const`.
- Exceptions : `StackOverflow`, `StackUnderflow`.
- Constructeurs : par défaut et à partir d’itérateurs (`begin`, `end`).
- Tester avec plusieurs types et vérifier qu’il n’y a pas de fuite mémoire.
<img width="558" height="302" alt="image" src="https://github.com/user-attachments/assets/a6ddec3f-548a-484a-b2df-60faeafca748" />

---

## Exercice 4 – Foncteur générique de tri avec contraintes C++20 (concepts)

### Objectifs pédagogiques
- Employer les concepts pour restreindre les types acceptés par un template.
- Implémenter un algorithme de tri paramétrable par stratégie.

### Travail demandé
- Définir un concept `Sortable` :
```cpp
template<typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};
<img width="538" height="191" alt="image" src="https://github.com/user-attachments/assets/54624d3f-7bf7-4163-9e6b-d4a5ed0775e0" />
