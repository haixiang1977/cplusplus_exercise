/*
 * test15.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: liu
 */

// Template function specialization
// it is useful to implement a templated function slightly different for a
// specific data type.

#include <iostream>

template <class T>
class Storage {
private:
	T m_value;
public:
	Storage (T value) {
		m_value = value;
	}
	~Storage () {}
	void print () {
		std::cout << "Storage value " << m_value << std::endl;
	}
};

// add specification function for double
template <>
void Storage<double>::print() {
	 std::cout << std::scientific << m_value << std::endl;
}

int main () {
	Storage <int> nValue (5);
	Storage <double> mValue (10.5);

	nValue.print();
	mValue.print();

	return 0;
}


