#include <iostream>

using namespace std;

template <class T>
class mycontainer {
 private:
    T element;
 public:
    mycontainer(T arg) {
        element = arg;
    }
    T increase() {
        return ++element;
    }
};

// class template specialization
template<>
class mycontainer <char> {
 private:
    char element;
 public:
    mycontainer(char arg) {
        element = arg;
    }
    char upcase() {
        element += 'A' - 'a';
        return element;
    }
};

int main() {
    mycontainer<int> myint(7);

    cout << myint.increase() << endl;

    mycontainer<char> mychar('j');

    cout << mychar.upcase() << endl;

    return 0;
}

