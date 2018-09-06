#include <unistd.h>
#include <iostream>
#include <thread>

class Base {
 public:
    Base();
    virtual ~Base();

    virtual void Print(void) = 0;
};

class Derived : public Base {
 public:
    Derived();
    virtual ~Derived();

    virtual void Print(void);
};

Base::Base() {
    std::cout << "Base::Base() in" << std::endl;
    std::cout << "Base::Base() out" << std::endl;
}

Base::~Base() {
    std::cout << "Base::~Base() in" << std::endl;
    sleep(20);
    std::cout << "Base::~Base() out" << std::endl;
}

Derived::Derived() {
    std::cout << "Derived::Derived() in" << std::endl;
    std::cout << "Derived::Derived() out" << std::endl;
}

Derived::~Derived() {
    std::cout << "Derived::~Derived() in" << std::endl;
    std::cout << "Derived::~Derived() out" << std::endl;
}

void Derived::Print(void) {
    std::cout << "Derived::Print()" << std::endl;
}

void *thread_func(Base* b)
{
    while (true) {
        b->Print();
        sleep(1);
    }

    return 0;
}

int main() {
    std::thread t;
    Base* b = new Derived();

    t = std::thread(&thread_func, b);
    b->Print();

    sleep(2);
    delete b;

    return 0;
}
