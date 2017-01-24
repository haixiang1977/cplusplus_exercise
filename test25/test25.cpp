/*
 * test25.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: liu
 */

// time conversion

#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>

int main()
{
    std::tm t = {};
    std::istringstream ss("2017-01-24T02:27:20.469Z");
    ss >> std::get_time (&t, "%Y-%m-%dT%H:%M:%S.%fZ");
    std::cout << std::put_time(&t, "%c") << std::endl;
    if (ss.fail()) {
	std::cout << "Parse failed" << std::endl;
    } else {
        std::cout << std::put_time(&t, "%c") << std::endl;
    }
}

