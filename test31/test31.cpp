/*
 * test31.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: liu
 */

#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class A {
public:
	~A() {}
	void print () {cout << "A" << endl;}
};

class B : public A {
public:
	B(std::string n) : name(n) {
		bb = 100;
		bbb = 200;
		bbbb = 300;
		bbbbb = 400;
	}
	~B() {}
	void print () {cout << "B" << endl;}
	void print_b() {
		cout << bb << endl;
		cout << bbb << endl;
		cout << bbbb << endl;
		cout << bbbbb << endl;
		return;
	}
	std::string get_name() {return name;}
private:
	std::string name;
	int bb;
	int bbb;
	int bbbb;
	int bbbbb;
};

typedef map<class A*, std::string> AMap;
typedef vector<class B*> BList;

int main() {
	AMap a_map;
	BList b_list;

	A *a1, *a2, *a3;
	B *b1, *b2, *b3;

	b1 = new B ("b1");
	b2 = new B ("b2");
	b3 = new B ("b3");

	a1 = b1;
	a2 = b2;
	a3 = b3;

	cout << "sizeof A " << sizeof(A) << endl;
	cout << "sizeof B " << sizeof(B) << endl;

	cout << "sizeof a1 " << sizeof(a1) << endl;
	cout << "sizeof b1 " << sizeof(b1) << endl;

	cout << "a1 value " << a1 << endl;
	cout << "b1 value " << b1 << endl;

	// push a1 into map
	a_map[a1] = "b1";
	a_map[a2] = "b2";
	a_map[a3] = "b3";

	// push b1 into vector
	b_list.push_back(b1);
	b_list.push_back(b2);
	b_list.push_back(b3);

	// search vector in the map
	for (AMap::iterator it = a_map.begin(); it != a_map.end(); ++it) {
		BList::iterator itt = find (b_list.begin(), b_list.end(), it->first);
		if (itt != b_list.end()) {
			cout << "HIT" << endl;
			cout << "[Map it->second] " << it->second << " [vector name] " << (*itt)->get_name() << endl;
		} else {
			cout << "MISS" << endl;
		}
	}

	return 0;
}
