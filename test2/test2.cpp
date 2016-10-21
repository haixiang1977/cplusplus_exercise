/* virtual and non-virtual difference is polymorphism */
/* upcasting: taking the address of any object (either pointer or reference), treating it as the address of base type */
/* binding: connecting a function call with function body called binding */
/* early binding: binding before program run, means compilation */
/* late binding: binding during program run */
/* c++ Primer 15.2.3 */

#include <iostream>
using namespace std;

class PEOPLE {
public:
	virtual ~PEOPLE() {};
	void play() {
		cout << "people playing" << endl;
	}
	virtual void sing() {
		cout << "people sing" << endl;
	}
};

class GIRL: public PEOPLE {
public:
	void play() {
		cout << "girl play" << endl;
	}
	virtual void sing () {
		cout << "girl sing" << endl;
	}
};

class BOY: public PEOPLE {
public:
	void play() {
		cout << "boy play" << endl;
	}
	virtual void sing () {
		cout << "boy sing" << endl;
	}
};

void sunday (PEOPLE &p) { // must use reference for upcasting
	                      // if sunday (PEOPLE p), then will all people play and sing
	                      // also can see from debugger
	p.play();

	p.sing();
}

int main () {
	PEOPLE p;
	GIRL g;
	BOY b;

	sunday(p);
	sunday(b);
	sunday(g);

	return 0;
}
