/*
 * test19.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: liu
 */

// find() to find matched value
// insert() to add new value

#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int main() {
	list<int> li;

	for (int i = 0; i < 6; i++) {
		li.push_back(i);
	}

	list<int>::iterator it;
	it = find(li.begin(), li.end(), 3);

	li.insert(it, 8); // insert before it

	// since insert maybe change the memory of list, it needs to re-get again
	for (it = li.begin(); it != li.end(); it++) {
		cout << *it << " " << endl;
	}

	return 0;
}
