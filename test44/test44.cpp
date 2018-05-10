#include <iostream>

class A {
 public:
	A() {}
	~A() {}
	void print(int x = 10);
};

void A::print(int x) {
	std::cout << "x: " << x << std::endl;
	return;
}

int main() {
	A a;

	std::cout << "print default function parameter" << std::endl;
	a.print();

	std::cout << "print explict function parameter" << std::endl;
	a.print(20);

	return 0;
}
