// https://blog.csdn.net/liukang325/article/details/53668046

#include <iostream>
#include <functional>

using namespace std;

void print_hello() {
	cout << "hello std::function" << endl;

	return;
}

int main() {
	std::function<void()> func;

	func = print_hello;

	func();

	return 0;
}
