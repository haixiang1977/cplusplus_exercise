/*
 * test14.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: liu
 */

// understanding template function in c++

// In C++, function templates are functions that serve as a pattern for
// creating other similar functions.

// The basic idea behind function templates is to create a function without
// having to specify the exact type(s) of some or all of the variables.
// Instead, we define the function using placeholder types, called template
// type parameters.

// When you call a template function, the compiler “stencils” out a copy of
// the template, replacing the placeholder types with the actual variable types
// from the parameters in your function call

// Because the function argument passed in for type T could be a class type,
// and it’s generally not a good idea to pass classes by value, it would be
// better to make the parameters and return types const references

#include <iostream>

//using namespace std;
// std::max() will conflicts the max I defined here

template <typename T>

const T& max(const T& x, const T& y) {
	return (x > y) ? x : y;
}

class Cents {
private:
	int m_cents;
public:
	Cents (int cent) : m_cents(cent) {}
	int get_cents() {
		return m_cents;
	}
	// Override the operate '>'
	// non-member friend function
	// an overloaded operator declared as member function is asymmetric
	// because it can have only one parameter and the other parameter passed
	// automatically is the 'this' pointer. So no standard exists to compare
	// them.
    // overloaded operator declared as a friend is symmetric because we pass
	// two arguments of the same type and hence, they can be compared
	// http://stackoverflow.com/questions/4622330/operator-overloading-member-function-vs-non-member-function
	friend bool operator > (const Cents &c1, const Cents &c2) {
		return (c1.m_cents > c2.m_cents);
	}
};

int main () {
	int i = max (3, 7);
	std::cout << "int max (3, 7) = " << i << std::endl;

	double j = max (6.34, 18.23);
	std::cout << "double max (6.34, 18.23) = " << j << std::endl;

	Cents a(3);
	Cents b(10);
	Cents c = max (a, b);

	std::cout << "max (a, b) = " << c.get_cents() << std::endl;
}

