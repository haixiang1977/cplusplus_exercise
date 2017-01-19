/*
 * test21.cpp
 *
 *  Created on: Jan 19, 2017
 *      Author: liu
 */

// check memory leakage of map

#include <iostream>
#include <map>

using namespace std;

class Test {
public:
	~Test() {
		// without clear, the map also freed after delete the object
		options.clear();
	};
	void parse();
private:
	map <string, string> options;
};

void Test::parse()
{
	options["PRIMARY SCHOOL"] = "SENG KANG PRIMARY";
	options["SECONDARY SCHOOL"] = "HUANG ZHONG SECONDARY SCHOOL";
	options["UNIVERSITY"] = "CAMBRIDGE";

	return;
}

int main()
{
	Test *t = new Test();

	t->parse();

	delete t;

	return 0;
}
