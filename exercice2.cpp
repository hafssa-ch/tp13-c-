
#include <iostream>
#include <initializer_list>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrice {
private:
    T data[N][M]{};

public:
    // Constructeur par défaut (initialise tout à 0)
    Matrice() {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] = T(0);
    }

    // Constructeur avec liste d'initialisation
    Matrice(initializer_list<initializer_list<T>> init) {
        size_t i = 0;
        for (auto& row : init) {
            size_t j = 0;
            for (auto& val : row) {
                if (i < N && j < M)
                    data[i][j] = val;
                ++j;
            }
            ++i;
        }
    }

    // Accès à un élément
    T& operator()(size_t i, size_t j) {
        return data[i][j];
    }

    const T& operator()(size_t i, size_t j) const {
        return data[i][j];
    }

    // Addition élément par élément
    Matrice<T, N, M> operator+(const Matrice<T, N, M>& autre) const {
        Matrice<T, N, M> resultat;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                resultat.data[i][j] = data[i][j] + autre.data[i][j];
        return resultat;
    }

    // Multiplication matricielle
    template <size_t P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {
        Matrice<T, N, P> resultat;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < P; ++j) {
                T somme = 0;
                for (size_t k = 0; k < M; ++k)
                    somme += data[i][k] * autre(k, j);
                resultat(i, j) = somme;
            }
        }
        return resultat;
    }

    // Affichage
    friend ostream& operator<<(ostream& out, const Matrice<T, N, M>& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j)
                out << m.data[i][j] << "\t";
            out << endl;
        }
        return out;
    }
};

// Test
int main() {
    Matrice<int, 2, 3> m1{{ {1, 2, 3}, {4, 5, 6} }};
    Matrice<int, 2, 3> m2{{ {6, 5, 4}, {3, 2, 1} }};

    cout << "M1 + M2 =" << endl;
    cout << m1 + m2 << endl;

    Matrice<int, 3, 2> m3{{ {1, 2}, {3, 4}, {5, 6} }};
    cout << "M1 * M3 =" << endl;
    auto m4 = m1 * m3;
    cout << m4 << endl;

    Matrice<double, 2, 2> md{{ {1.5, 2.5}, {3.5, 4.5} }};
    cout << "Matrice double:" << endl << md << endl;

    return 0;
}
