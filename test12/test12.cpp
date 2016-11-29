/*
 * test12.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: liu
 */

/* Friend function: */
/* A friend function is a function that can access the private members of a
 * class as though it were a member of that class.
 */
/* A friend function may be either a normal function, or a member function of
 * another class. To declare a friend function, simply use the friend keyword
 * in front of the prototype of the function you wish to be a friend of the
 * class.
 */
/* A function can be a friend of more than one class at the same time. */


/* Friend class */
/* It is also possible to make an entire class a friend of another class. This
 * gives all of the members of the friend class access to the private members
 * of the other class.
 */

#include <iostream>

using namespace std;

class Accumulator {
private:
	int m_value;
public:
	Accumulator() {
		m_value = 0;
	}
	void add(int value) {
		m_value += value;
	}

	/* make external normal function reset() as friend */
	friend void reset(Accumulator &accumulator);

	/* make another class as friend */
	friend class DisplayResult;
};

void reset (Accumulator& accumulator) {
	/* friend function able to access the private member */
	accumulator.m_value = 0;
	cout << "friend reset() access Accumulator::m_value " << accumulator.m_value << endl;

	return;
}

class DisplayResult {
private:
	bool IsDisplay;
public:
	DisplayResult (bool display) : IsDisplay(display) {}
	void Display (Accumulator& accumulator) {
		if (IsDisplay) {
			cout << "friend class DisplayResult access Accumulator::m_value " << accumulator.m_value << endl;
		}
		return;
	}
};

int main ()
{
	Accumulator acc;
	DisplayResult disp (true);

	acc.add(5);
	reset(acc);

	acc.add(10);
	disp.Display(acc);
}
