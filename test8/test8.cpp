/*
 * test8.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: liu
 */
#include <iostream>

using namespace std;

class A
{
private:
	int b;
public:
	A() : b(1) {;}
	void setval(int val) {b = val;}
	void getval () {cout << "A::b = " << b << endl;}
};

/* Passing arguments by reference */
void foo_1 (A &c) //using reference here
{
	c.setval(5);
}

/* Passing arguments by point */
void foo_2 (A *p)
{
	p->setval(10);
}

int main ()
{
	A a;

	a.getval();
	foo_1(a);
	a.getval();
	foo_2(&a);
	a.getval();

	return 0;
}

