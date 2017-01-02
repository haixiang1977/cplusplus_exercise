/*
 * test16.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: liu
 */

#include <assert.h>
#include <iostream>

template <class T>
class Array {
private:
	int m_length;
	T *m_data;
public:
	Array() {
		m_length = 0;
		m_data = 0;
	}

	Array(int length) {
		m_data = new T[length];
		m_length = length;
	}

	~Array() {
		delete[] m_data;
	}

	void Erase() {
		delete[] m_data;
		m_data = 0;
		m_length = 0;
	}

	T& operator [] (int index) {
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	int getLength();
};

// Each templated member function declared outside the class declaration needs
// its own template declaration.
template <typename T>
// the name of the templated array class is Array<T>, not Array -- Array would
// refer to a non-templated version of a class named Array.
int Array<T>::getLength() {
	return m_length;
}

// Template classes are ideal for implementing container classes, because it
// is highly desirable to have containers work across a wide variety of data
// types, and templates allow you to do so without duplicating code. Although
// the syntax is ugly, and the error messages can be cryptic, template classes
// are truly one of C++’s best and most useful features.
int main() {
	Array<int> intArray(12);
	Array<double> doubleArray(12);

	for (int count = 0; count < intArray.getLength(); ++count) {
		intArray[count] = count;
		doubleArray[count] = count + 0.5;
	}

	for (int count = intArray.getLength()-1; count >= 0; --count) {
		std::cout << intArray[count] << "\t" << doubleArray[count] << std::endl;
	}
}



