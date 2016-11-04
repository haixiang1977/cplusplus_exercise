/*
 * test6.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: liu
 */

#include <iostream>

using namespace std;

class A {
public:
	virtual ~A() {};
	virtual void a() {cout << "A::a() called" << endl;}
	virtual void b() {cout << "A::b() called" << endl;}
};

class B: public A {
public:
	virtual void a() {cout << "B:a() called" << endl;}
};

int main ()
{
	A* a;
	B b;

	a = &b;
	a->a();
	a->b();

	return 0;
}

