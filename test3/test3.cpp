/* exercise static members in c++ */
/* static variable can be accessed by both object and class */
/* static function can also be accessed by both object and class */
/* static variable must be declared outside of class */
#include <iostream>

using namespace std;

class Logger
{
public:
	static void init(void) {cout << "log init" << endl;}
	void term(void) {cout << "log term" << endl;}

	static void print (void) {cout << "shandle = " << shandle << endl;}
	static int shandle;
	int handle;
};

int Logger::shandle = 10; /* must define outside of the class and only one defination allowed */

int main() {
	Logger log;

	Logger::init();
	//Logger::term(); /* cannot call member function ‘void Logger::term()’ without object */
	Logger::print();

	log.init(); /* both class and object can call static function */
	log.term();

	Logger::shandle = 100; /* error: invalid use of qualified-name ‘Logger::shandle’ */
	Logger::print();
	//Logger::handle = 10; /* invalid use of non-static data member ‘Logger::handle’ */
	log.shandle = 1000;
	Logger::print();
	log.handle = 100;
	log.print();

	return 0;
}
