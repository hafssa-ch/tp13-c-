
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class ArrayDyn {
private:
    T* data;
    size_t taille;
    size_t capacite;

    void agrandir() {
        size_t nouvelleCap = capacite == 0 ? 1 : capacite * 2;
        T* nouveauData = new T[nouvelleCap];
        for (size_t i = 0; i < taille; ++i) {
            nouveauData[i] = data[i];
        }
        delete[] data;
        data = nouveauData;
        capacite = nouvelleCap;
    }

public:
    // Constructeurs
    ArrayDyn() : data(nullptr), taille(0), capacite(0) {}
    ArrayDyn(size_t cap) : data(new T[cap]), taille(0), capacite(cap) {}
    
    // Constructeur de copie
    ArrayDyn(const ArrayDyn& autre) : data(new T[autre.capacite]), taille(autre.taille), capacite(autre.capacite) {
        for (size_t i = 0; i < taille; ++i)
            data[i] = autre.data[i];
    }

    // Opérateur d’affectation
    ArrayDyn& operator=(const ArrayDyn& autre) {
        if (this != &autre) {
            delete[] data;
            taille = autre.taille;
            capacite = autre.capacite;
            data = new T[capacite];
            for (size_t i = 0; i < taille; ++i)
                data[i] = autre.data[i];
        }
        return *this;
    }

    // Destructeur
    ~ArrayDyn() { delete[] data; }

    // Méthodes
    void push_back(const T& val) {
        if (taille == capacite)
            agrandir();
        data[taille++] = val;
    }

    void pop_back() {
        if (taille > 0) --taille;
    }

    T& operator[](size_t index) {
        if (index >= taille)
            throw out_of_range("Index invalide");
        return data[index];
    }

    size_t size() const { return taille; }

    // Itérateur interne
    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        Iterator& operator--() { --ptr; return *this; }
        bool operator!=(const Iterator& autre) const { return ptr != autre.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + taille); }
};

// Test
class Personne {
public:
    string nom;
    Personne(string n = "") : nom(n) {}
};

int main() {
    ArrayDyn<int> arrInt;
    arrInt.push_back(10);
    arrInt.push_back(20);

    ArrayDyn<string> arrStr;
    arrStr.push_back("Bonjour");
    arrStr.push_back("Monde");

    ArrayDyn<Personne> arrPers;
    arrPers.push_back(Personne("Alice"));
    arrPers.push_back(Personne("Bob"));

    cout << "Array d'entiers:" << endl;
    for (auto &e : arrInt) cout << e << " ";
    cout << endl;

    cout << "Array de string:" << endl;
    for (auto &e : arrStr) cout << e << " ";
    cout << endl;

    cout << "Array de personnes:" << endl;
    for (auto &p : arrPers) cout << p.nom << " ";
    cout << endl;

    return 0;
}
