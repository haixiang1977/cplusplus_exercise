#include <iostream>

using namespace std;

class A {
public:
    static const string TEST_STRING;
};

const string A::TEST_STRING = "hello world";

int main() {
    cout << A::TEST_STRING << endl;
    return 0;
}

