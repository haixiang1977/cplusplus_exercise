/*
 * test24.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: liu
 */

#include <iostream>
#include <vector>

using namespace std;

#define CHECK_CONST 1 // to test iterator const

// std::vector<T>::push_back() creates a copy of the argument and stores it in
// the vector. If you want to store pointers to objects in your vector, create
// a std::vector<whatever*> instead of std::vector<whatever>.
// However, you need to make sure that the objects referenced by the pointers
// remain valid while the vector holds a reference to them (smart pointers
// utilizing the RAII idiom solve the problem).

class A {
public:
	A(int v) : m_val(v) {}
#ifdef CHECK_CONST
	int get_val() const {return m_val;} // to avoid compiler think const
	                                    // iterator->xxx() compile error
#else
	int get_val () {return m_val;}
#endif
private:
	int m_val;
};

typedef vector <A> AList;

class B {
public:
	void push (A a);
	AList & get_alist(); // use reference can save space to avoid copy object
private:
	AList m_list;
};

void B::push(A a) {
	m_list.push_back(a);
	return;
}

AList & B::get_alist() {
	return m_list;
}

int main()
{
	A a1(0);
	A a2(1);
	A a3(2);

	B b;

	b.push(a1);
	b.push(a2);
	b.push(a3);

#ifdef CHECK_CONST // const initialization must be done in definition
	const AList alist = b.get_alist();
#else
	AList alist;
#endif

#ifdef CHECK_CONST
	for (AList::const_iterator it = alist.begin(); it != alist.end(); ++it) {
		cout << "val " << it->get_val() << endl;
	}
#else
	alist = b.get_alist();
	for (AList::iterator it = alist.begin(); it != alist.end(); it++) {
		cout << "val " << it->get_val() << endl;
	}
#endif

	return 0;
}
