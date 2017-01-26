/*
 * test28.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: liu
 */

// null pointer definition
// In C++, NULL is defined as #define NULL 0, so it is basically int. And looks
// ambiguous
// C++11 introduces nullptr, it is known as the Null pointer constant and It
// improves type safety and resolves ambiguous situations unlike the existing
// implementation dependent null pointer constant NULL.
// Pre C++11 NULL was used to represent a pointer that has no value or pointer
// that does not point to anything valid. Contrary to the popular notion NULL
// is not a keyword in C++. It is an identifier defined in standard library
// headers. In short you cannot use NULL without including some standard
// library headers.
// http://stackoverflow.com/questions/13816385/what-are-the-advantages-of-using-nullptr

#include <iostream>

using namespace std;

void f (char *ptr) {
	cout << "f(char *) called" << endl;
	return;
}

void f (int *ptr) {
	cout << "f(int *) called" << endl;
	return;
}

void f (std::nullptr_t) {
	cout << "f(std::nullptr_t) called" << endl;
	return;
}

void f(int) {
	cout << "f(int) called" << endl;
	return;
}

int main() {
	f(nullptr);
	f(NULL); // NULL is defined as int (0)
	f(0);

	return 0;
}

