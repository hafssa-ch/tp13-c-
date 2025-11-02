#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

// Foncteurs de comparaison
struct Asc {
    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

struct Desc {
    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return b < a;
    }
};

// QuickSort template
template <typename T, typename Comp = Asc>
void quickSort(vector<T>& vec, Comp comp = Comp{}) {
    auto partition = [&](int low, int high) {
        T pivot = vec[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (comp(vec[j], pivot)) {
                ++i;
                swap(vec[i], vec[j]);
            }
        }
        swap(vec[i + 1], vec[high]);
        return i + 1;
    };

    function<void(int,int)> qs = [&](int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            qs(low, pi - 1);
            qs(pi + 1, high);
        }
    };

    if (!vec.empty()) qs(0, vec.size() - 1);
}

// Test structure utilisateur
struct Personne {
    string nom;
    int age;
    bool operator<(const Personne& autre) const {
        return age < autre.age;
    }
};

int main() {
    // Test int
    vector<int> vi{5, 2, 9, 1, 7};
    quickSort(vi, Asc{});
    for (auto i : vi) cout << i << " ";
    cout << endl;

    quickSort(vi, Desc{});
    for (auto i : vi) cout << i << " ";
    cout << endl;

    // Test string
    vector<string> vs{"Charlie", "Alice", "Bob"};
    quickSort(vs, Asc{});
    for (auto& s : vs) cout << s << " ";
    cout << endl;

    // Test structure utilisateur
    vector<Personne> vp{{"Alice",30}, {"Bob",25}, {"Charlie",35}};
    quickSort(vp, Asc{});
    for (auto& p : vp) cout << p.nom << "(" << p.age << ") ";
    cout << endl;

    return 0;
}
