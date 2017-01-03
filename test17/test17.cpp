/*
 * test17.cpp
 *
 *  Created on: Jan 3, 2017
 *      Author: liu
 */

// In C++, a throw statement is used to signal that an exception or error case
// has occurred. Signaling that an exception has occurred is also commonly
// called raising an exception.
// In C++, we use the try keyword to define a block of statements (called a try
// block). The try block acts as an observer, looking for any exceptions that
// are thrown by any of the statements within the try block.
// 'try' merely tells the program, “Hey, if any of the statements inside this
// try block throws an exception, grab it!”.
// Actually handling exceptions is the job of the catch block(s). The catch
// keyword is used to define a block of code (called a catch block) that
// handles exceptions for a single data type.
// When an exception is raised (using throw), execution of the program
// immediately jumps to the nearest enclosing try block (propagating up the
// stack if necessary to find an enclosing try block. If any of the catch
// handlers attached to the try block handle that type of exception, that
// handler is executed and the exception is considered handled.
// If an exception is routed to a catch block, it is considered “handled” even
// if the catch block is empty. However, typically you’ll want your catch
// blocks to do something useful.
// There are three common things that catch blocks do when they catch an
// exception:
// . catch blocks may print an error (either to the console, or a log file).
// . catch blocks may return a value or error code back to the caller.
// . a catch block may throw another exception.

#include <iostream>
#include <math.h>

int main () {
	std::cout << "Enter a number: ";
	double x;
	std::cin >> x;

	try {
		if (x < 0.0)
			throw "can not take a negative value";
		// otherwise print a sqrt value
		std::cout << "the sqrt of " << x << " = " << sqrt(x) << std::endl;
	}
	catch (const char* exception) {
		std::cerr << "Error: " << exception << std::endl;
	}
}

