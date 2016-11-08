/*
 * test11.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: liu
 */

/* constructor from a derived sequence */
/* the sequence of constructor: base class first, derived class next */
/* the sequence of de-constructor: derived class first, base class followed */

/* When constructing a derived class, the derived class constructor is
 * responsible for determining which base class constructor is called. If no
 * base class constructor is specified, the default base class constructor
 * will be used. In that case, if no default base class constructor can be
 * found (or created by default), the compiler will error. The classes are
 * then constructed in order from most base to most derived.
 */

#include <iostream>

using namespace std;

class A {
public:
	A() {cout << "class A constructor called" << endl;}
	~A() {cout << "class A de-constructor called" << endl;}
};

class B : public A {
public:
	B() {cout << "class B constructor called" << endl;}
	~B() {cout << "class B de-constructor called" << endl;}
};

class C {
private:
	int m_id;
public:
	C() {
		cout << "C::C() called" << endl;
		m_id = 0;
	}
	C(int id) {
		cout << "C::C(int) called" << endl;
		m_id = id;
	}
	void get_id () {cout << "C:id = " << m_id << endl;}
};

class D : public C {
public:
	D () {} // class C::C() default constructor called
	D (int id) : C(id) {} // class C::C(int id) constructor called
};


int main ()
{
	B b;

	D d;
	D dd(10);

	d.get_id();
	dd.get_id();

	return 0;
}


