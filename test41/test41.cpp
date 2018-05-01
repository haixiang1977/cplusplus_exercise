/*
 * test41.cpp
 *
 *  Created on: May 1, 2018
 *      Author: liu
 */

#include <iostream>
#include <functional>

using namespace std;

void func(int a, int b, int c) {
	cout << "func: " << a << " " << b << " " << c << endl;
}

int main() {
	std::function<void()> func_bind = std::bind(func, 1, 2, 3);
	func_bind(); // all default, no parameters needed defined ()

	std::function<void(int x, int y)> func_bind_1 = std::bind(func, placeholders::_1, placeholders::_2, 3);
	func_bind_1(4, 5); // needs 2 parameters so defined (int x, int y)

	return 0;
}

