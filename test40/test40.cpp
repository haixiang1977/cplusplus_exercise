// https://blog.csdn.net/liukang325/article/details/53668046

#include <iostream>
#include <functional>

using namespace std;

void print_hello() {
	cout << "hello std::function" << endl;

	return;
}

int main() {
	/* save function pointer */
	std::function<void()> func_ptr;

	func_ptr = print_hello;

	func_ptr();

	/* lambda function */
	std::function<void()> func_lambda = []() {
		cout << "hello lambda std::function" << endl;
		return;
	};

	func_lambda();
	return 0;
}
