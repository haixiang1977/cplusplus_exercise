// The following are the cases when copy constructor is called.
// 1)When instantiating one object and initializing it with values from another object. 
// -> it called
// 2)When passing an object by value. (from function parameter)
// -> it called
// 3)When an object is returned from a function by value. 
// -> not called and optimized by compiler


#include <stdio.h>
#include <string.h>

//#define ENABLE_DEFAULT_CONSTRUCTOR 1

class A {
public:
	A();
#ifdef ENABLE_DEFAULT_CONSTRUCTOR
#else
	A(const A&);
#endif
	virtual ~A();
	void print();
	void set();

    static A convert();
private:
	char* str;
};

A A::convert() {
    return A();
}

A::A() {
	printf("A Constructor\n");
	str = new char[255];
	memset(str, '\0', 255);
}

#ifdef ENABLE_DEFAULT_CONSTRUCTOR // use default copy constructor - bit copy
    // double free will happen because bit copy
    // b.str and a.str point to the same address with bit copy
    // when a destrctor called, a.str free the memory and b.str will free again
#else
A::A(const A& a) {
	printf("A copy Constructor called\n");
    str = new char[255];
    memset(str, '\0', 255);
    printf("copy a to b \n");
    memcpy(str, a.str, 255);
}
#endif

A::~A() {
	printf("A De-Constructor\n");
	delete[] str;
}

void A::print() {
	printf("A::print %s\n", str);
}

void A::set() {
	strcpy(str, "hello world");
}

A test() {
	A aa = A();
	aa.set();
	return aa;
}

void test1(A c) {
    // constructor and deconstructor will get called both
    c.print();
}

void test2(A& c) {
    // constructor and deconstructor will not called when passing reference
    c.print();
}

int main() {
    printf("Function return object\n"); 
	A a = test(); // copy constructor is avoided by the compiler

    printf("= operator\n");
	A b = a; // copy constructor is called
             // default copy constructor can not be used in this case because has pointer
             // copy constructor must be overrided

    printf("Function parameter pass\n");
    test1(b); // copy constructor is called for function parameter pass

    printf ("Function Reference pass\n");
    test2(b); // copy constructor is *NOT* called for function reference parameter pass

	a.print();
	b.print();

    printf("Function return object\n"); 
    A d = A::convert();
    d.print();
    
	return 0;
}
