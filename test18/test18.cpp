/*
 * test18.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: liu
 */

#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main() {
	list<int> li;

	for (int i = 0; i < 6; i++) {
		li.push_back(i);
	}

	list<int>::iterator it;
	it = min_element(li.begin(), li.end());
	cout << "min_element " << *it << endl;

	it = max_element(li.begin(), li.end());
	cout << "max_element " << *it << endl;

	return 0;
}
