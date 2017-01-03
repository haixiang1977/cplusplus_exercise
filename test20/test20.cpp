/*
 * test20.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: liu
 */

// sort and reverse operation

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	vector<int> v;

	v.push_back(7);
	v.push_back(-3);
	v.push_back(6);
	v.push_back(2);
	v.push_back(-5);
	v.push_back(0);
	v.push_back(4);

	sort(v.begin(), v.end());

	vector<int>::iterator it;
	for (it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	reverse(v.begin(), v.end());
	for (it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}
