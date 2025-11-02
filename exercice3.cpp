
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
using namespace std;

// Exceptions personnalisées
class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "Stack overflow: la pile est pleine.";
    }
};

class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "Stack underflow: la pile est vide.";
    }
};

template <typename T>
class Stack {
private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t topIndex;

public:
    // Constructeurs
    Stack(size_t cap = 10) : data(make_unique<T[]>(cap)), capacity(cap), topIndex(0) {}

    template <typename Iter>
    Stack(Iter begin, Iter end) {
        capacity = distance(begin, end);
        data = make_unique<T[]>(capacity);
        topIndex = 0;
        for (Iter it = begin; it != end; ++it) {
            data[topIndex++] = *it;
        }
    }

    // Méthodes
    void push(const T& val) {
        if (topIndex >= capacity)
            throw StackOverflow();
        data[topIndex++] = val;
    }

    void pop() {
        if (topIndex == 0)
            throw StackUnderflow();
        --topIndex;
    }

    T peek() const {
        if (topIndex == 0)
            throw StackUnderflow();
        return data[topIndex - 1];
    }

    bool empty() const {
        return topIndex == 0;
    }

    size_t size() const {
        return topIndex;
    }
};

// Test
int main() {
    Stack<int> s(5);

    // Test push
    for (int i = 1; i <= 5; ++i) s.push(i);

    try {
        s.push(6); // Devrait lever StackOverflow
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Test peek et pop
    while (!s.empty()) {
        cout << "Top: " << s.peek() << endl;
        s.pop();
    }

    try {
        s.pop(); // Devrait lever StackUnderflow
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Test constructeur avec itérateurs
    vector<string> mots = {"Alice", "Bob", "Charlie"};
    Stack<string> s2(mots.begin(), mots.end());
    while (!s2.empty()) {
        cout << s2.peek() << " ";
        s2.pop();
    }
    cout << endl;

    return 0;
}
