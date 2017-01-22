/*
 * test23.cpp
 *
 *  Created on: Jan 22, 2017
 *      Author: liu
 */

// c++ string operation example

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//string test ("a:b:c");
//string test (":a:b:c");
string test ("a:b:c:");
//string test ("a:b:c::");

int main()
{
	vector <string> token;

	for (size_t p = 0; p != string::npos;) {
		p = test.find(":", p);
		if (p != string::npos) {
			cout << "found pos p " << p << " push " << test.substr(0, p) << endl;
			token.push_back(test.substr(0, p));
			p++;
		} else {
			// write the whole string
			cout << "no more : push test " << test << endl;
			token.push_back(test);
		}
	}

	for (vector <string>::iterator it = token.begin(); it != token.end(); it++) {
		cout << "path to search " << it->c_str() << endl;
		// if not in the cache, we start to search from the 1st path
		// take the name of the last path
		size_t p = 0;
		std::string name;
		p = it->find_last_of(":");
		if (p != std::string::npos) {
			name = it->substr(p + 1);
		} else {
			// the first path name
			name = *it;
		}
		if (name.empty() == false) {
			cout << "name to browse " << name << endl;
		}
	}


	return 0;
}

