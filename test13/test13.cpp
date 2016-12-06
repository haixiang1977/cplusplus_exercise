/*
 * test13.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: liu
 */

/* using global variable in c++ */

#include <iostream>

using namespace std;

static string g_var("Initial global string");

class A
{
public:
	void print_A() {
		cout << "print global variable from class " << g_var << endl;
	}
};

int main ()
{
	A a;

	a.print_A();

	cout << "print global variable from main " << g_var << endl;

	cout << "print global variable c_str() from main " << g_var.c_str() << endl;

	return 0;
}

