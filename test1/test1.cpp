/* 1. virtual has to do with polymorphy and that is why it's only allowed inside a class.  */
/* 2. when class have virtual fun = 0, this class has been virtual class, can not be instance */
/* 3. not pure virtual function, still can run as normal member function */

#include <iostream>

using namespace std;

class CAT {
public:
	virtual void sound(void);
	void climb(void);
	virtual void sleep(void) = 0;
	void wakeup(void);
	void jump(void);
private:
	char name[256];
};

void CAT::sound(void) {
	cout << "cat sound" << endl;
}

void CAT::climb(void) {
	cout << "cat climb" << endl;
}

void CAT::wakeup(void) {
	cout << "cat wakeup" << endl;
}

void CAT::jump(void) {
	cout << "cat jump" << endl;
}

class BIGCAT: public CAT {
public:
	virtual void sound(void);
	void climb(void);
	virtual void sleep(void);
	void jump(void);
};

void BIGCAT::sound(void) {
	cout << "big cat sound" << endl;
}

void BIGCAT::climb(void) {
	cout << "big cat climb" << endl;
}

void BIGCAT::sleep(void) {
	cout << "big cat sleep" << endl;
}

void BIGCAT::jump(void) {
	cout << "big cat jump" << endl;
	CAT::jump();
}

int main () {
	//CAT c; /* cat has become pure virtual class */
	BIGCAT B;

	//c.sound();
	//c.climb();

	B.sound();
	B.climb();
	B.sleep();
	B.wakeup();
	B.jump();
}
