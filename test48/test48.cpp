#include <iostream>
using namespace std;

// Function templates
// Function templates are special functions that can operate with generic types.
//This allows us to create a function template whose functionality can be adapted to more than one type or class without repeating the entire code for each type.

template <class T>
T GetMax(T a, T b) {
    return (a > b ? a : b);
}

template <class T1, class T2>
T1 GetMin(T1 a, T2 b) {
    return (a < b ? a : b);
}

int main() {
    std::cout << GetMax(4, 5) << std::endl;

    std::cout << GetMin(int(4), float(5)) << std::endl;
    return 0;
}
