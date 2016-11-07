/*
 * test10.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: liu
 */

/* associative container */

/* A set is a container that stores unique elements, with duplicate elements disallowed. The elements are sorted according to their values. */

/* A map (also called an associative array) is a set where each element is a pair, called a key/value pair. The key is used for sorting and indexing the data, and must be unique. The value is the actual data.*/

#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

int main()
{
    set <int> myset;
    set <int>::const_iterator set_it; /* read only set iterator */

    map <int, string> mymap;
    map <int, string>::const_iterator map_it; /* read only map iterator */

    myset.insert(7);
    myset.insert(7);
    myset.insert(2);
    myset.insert(-6);
    myset.insert(8);
    myset.insert(1);
    myset.insert(-4);

    set_it = myset.begin();
    while (set_it != myset.end()) {
    	cout << "myset it = " << *set_it << endl; // print the number in order since set is ordered container
    	set_it ++;
    }

    mymap.insert(make_pair(4, "apple")); /* key = 4, value = apple. the map will order with key */
    mymap.insert(make_pair(2, "orange"));
    mymap.insert(make_pair(1, "banana"));
    mymap.insert(make_pair(3, "grapes"));
    mymap.insert(make_pair(6, "mango"));
    mymap.insert(make_pair(5, "peach"));

    map_it = mymap.begin();
    while (map_it != mymap.end()) {
    	cout << map_it->first << "=" << map_it->second << " " << endl;
    	map_it ++;
    }

	return 0;
}
