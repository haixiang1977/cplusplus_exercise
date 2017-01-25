/*
 * test27.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: liu
 */

// https://en.wikipedia.org/wiki/Smart_pointer
// In computer science, a smart pointer is an abstract data type that simulates
// a pointer while providing added features, such as automatic memory management
// or bounds checking. Such features are intended to reduce bugs caused by the
// misuse of pointers, while retaining efficiency.

// Smart pointers prevent most situations of memory leaks by making the memory
// deallocation automatic.
// More generally, they make object destruction automatic: an object controlled
// by a smart pointer is automatically destroyed (finalized and then deallocated)
// when the last (or only) owner of an object is destroyed.

// c++11 smart pointer:
// std::auto_ptr is deprecated under C++11 and completely removed from C++17.
// http://www.cplusplus.com/reference/memory/auto_ptr/
//
// http://www.cplusplus.com/unique_ptr
// unique_ptr objects delete their managed object without taking into account
// whether other pointers still point to the same object or not, and thus
// leaving any other pointers that point there as pointing to an invalid
// location.
// When that unique_ptr is destroyed, the resource is automatically reclaimed.
//
// http://en.cppreference.com/w/cpp/memory/shared_ptr
// A shared_ptr is a container for a raw pointer. It maintains reference
// counting ownership of its contained pointer in cooperation with all copies
// of the shared_ptr. An object referenced by the contained raw pointer will
// be destroyed when and only when all copies of the shared_ptr have been
// destroyed.
//
// A weak_ptr is a container for a raw pointer. It is created as a copy of a
// shared_ptr. The existence or destruction of weak_ptr copies of a shared_ptr
// have no effect on the shared_ptr or its other copies. After all copies of a
// shared_ptr have been destroyed, all weak_ptr copies become empty.

#include <iostream>
#include <memory>

int main() {
	// 1. example of unique_ptr and raw ptr
	std::cout << "Example 1" << std::endl;

	std::unique_ptr<int> p1(new int(5)); // no memory leak if no reset since it
	                                     // is unique_ptr
	int *p2 = new int (10); // memory leak detected by valgrind, if no delete

	std::cout << "unique_ptr example " << *p1 << std::endl;
	std::cout << "raw_ptr example " << *p2 << std::endl;

	// memory pointed by p1 is freed after p1 destroy
	// memory pointed by p2 is not free after p2 destroy, detected by valgrind

	p1.reset(); // free unique_ptr pointer
	delete p2;  // free raw pointer

	// 2. example of unique ptr for move
	std::cout << "Example 2" << std::endl;
	std::unique_ptr<int> p3(new int(5));
	//std::unique_ptr<int> p4 = p3; // 'use of deleted function', not allowed by compiler
	std::unique_ptr<int> p4 = std::move(p3);

	p3.reset(); // do nothing since the memory has been moved to p4
	p4.reset(); // free the memory allocated by p3

	// 3. example of strong pointer
	std::cout << "Example 3" << std::endl;
	std::shared_ptr<int> p5(new int(20));
	std::shared_ptr<int> p6 = p5; // both point to p5 allocated memory

	p5.reset(); // free p5 but p5 allocated memory still there
	std::cout << "shared_ptr example " << *p6 << std::endl;
	*p6 = 30;
	std::cout << "shared_ptr example " << *p6 << std::endl;
	p6.reset(); // free p6 and p5 allocated memory is freed

	// 4. example of weak pointer
	std::cout << "Example 4" << std::endl;
	std::shared_ptr<int> p7(new int(35));
	std::weak_ptr<int> wp1 = p7; //p7 owns the memory.

	if (wp1.expired()) { // valid here
		std::cout << "weak_ptr wp1 is expired" << std::endl;
	} else {
		std::cout << "weak_ptr wp1 is valid" << std::endl;
	}
	p7.reset();
	if (wp1.expired()) { // expired
		std::cout << "weak_ptr wp1 is expired" << std::endl;
	} else {
		std::cout << "weak_ptr wp1 is valid" << std::endl;
	}

	// std::weak_ptr is used to track the object, and it is converted to
	// std::shared_ptr to assume temporary ownership. If the original
	// std::shared_ptr is destroyed at this time, the object's lifetime is
	// extended until the temporary std::shared_ptr is destroyed as well.

	// 5. example use weak point to access
	std::cout << "Example 5" << std::endl;
	std::shared_ptr<int> p8(new int(40));
	std::weak_ptr<int> wp2 = p8;

	// weak point to lock and create a new shared pointer to access the memory
	std::shared_ptr<int> p9 = wp2.lock();

	// we have memory now and shared by p9
	p8.reset();
	// check wp2 valid or not even p8 has been reset
	if (wp2.expired()) { // valid since p9 take the memory
		std::cout << "weak_ptr wp2 is expired" << std::endl;
	} else {
		std::cout << "weak_ptr wp2 is valid" << std::endl;
	}

	p9.reset();
	if (wp2.expired()) { // expired
		std::cout << "weak_ptr wp2 is expired" << std::endl;
	} else {
		std::cout << "weak_ptr wp2 is valid" << std::endl;
	}

	return 0;
}

