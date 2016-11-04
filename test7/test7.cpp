/*
 * test7.cpp
 *
 *  Created on: Nov 4, 2016
 *      Author: liu
 */

/* The this pointer is a hidden const pointer that holds the address of the object the member function was called on. */
/* *this always points to the object being operated on and each member function has a *this pointer parameter that is set to the address of the object being operated on. */

#include <iostream>

using namespace std;

/* case 1 to use this */
/* First, if you have a constructor (or member function) that has a parameter with the same name as a member variable, you can disambiguate them by using “this”: */
class CALC {
private:
	int data;
public:
	void set_data (int data) {this->data = data;}
	void get_data () {cout << "data = " << data << endl;}

	/* case 2 to use this */
	/* Second, it can sometimes be useful to have a class member function return the object it was working with as a return value. */
	CALC& calc_add (int value) {data += value; return *this;} // return reference
	CALC* calc_sub (int value) {data -= value; return this;} // return pointer
	void calc_multi (int value) {data *= value; return;} // return void
};

int main()
{
	CALC c;

	c.set_data(10);
	c.get_data();
	c.calc_add(5).calc_sub(3)->calc_multi(2); // (10 + 5 - 3) * 2 = 8
	c.get_data();

	return 0;
}
