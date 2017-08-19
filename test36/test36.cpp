#include <iostream>

using namespace std;

class B;

class A {
public:
    A();
    ~A();
    void print();
    void start();
    void stop();
private:
    B* m_b;
};

class B {
public:
    B(A*);
    ~B();
private:
    A* m_a;
};

A::A() {
    cout << "A constructer" << endl;
}

A::~A() {
    cout << "A De-constructer" << endl;
}

void A::print() {
    cout << "Hello From A" << endl;
}

void A::start() {
    cout << "Start B from A" << endl;
    m_b = new B(this);
}

void A::stop() {
    cout << "Stop B from A" << endl;
    delete m_b;
}

B::B(A* a) {
    cout << "B constructer" << endl;
    m_a = a;
    m_a->print();
}

B::~B() {
    cout << "B De-constructer" << endl;
}

int main() {
    A* a = new A();
    
    a->start();
    
    a->stop();
    
    a->print();
    // check whether delete B will also delete A?
    delete a;
    
    return 0;
}


