#include <algorithm>
#include <iostream>
#include <set>
#include <string>

int main()
{
    std::set<std::string> set1;
    std::set<std::string> set2;

    for (unsigned int i = 0; i < 6; i++) {
        std::string str = std::string("WPG-00100") + std::to_string(i);
        set1.insert(str);
    }

    for (std::set<std::string>::iterator it = set1.begin(); it != set1.end(); ++it) {
        std::cout << "set1 " << *it << std::endl;
    }

    for (unsigned int j = 10; j > 4; j--) {
        std::string str = std::string("WPG-00100") + std::to_string(j);
        set2.insert(str);
    }

    for (std::set<std::string>::iterator it = set2.begin(); it != set2.end(); ++it) {
        std::cout << "set2 " << *it << std::endl;
    }

    if (set1 == set2) {
        std::cout << "set1 == set2" << std::endl;
    } else {
        std::cout << "set1 != set2" << std::endl;
        std::set<std::string> result;
        std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), 
            std::inserter(result, result.end()));

        for (std::set<std::string>::iterator it = result.begin(); it != result.end(); ++it) {
            std::cout << "s1 - s2 result >> " << *it << std::endl;
        }

        result.clear();
        std::set_difference(set2.begin(), set2.end(), set1.begin(), set1.end(), 
            std::inserter(result, result.end()));

        for (std::set<std::string>::iterator it = result.begin(); it != result.end(); ++it) {
            std::cout << "s2 - s1 result >> " << *it << std::endl;
        }
    }
    return 0;
}
