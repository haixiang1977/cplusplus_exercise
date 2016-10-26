/* http://www.cplusplus.com/reference/stl/ */
/* understanding the usage of sequence container like vector, list and iterator */
/* vector is class template, not type. So vector must have type followed */
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main ()
{
	vector <string> text; /* vector <T> v */
	unsigned int i;

	vector <string>::iterator it; /* vector <T>::iterator */
	                              /* <T>::iterator */

	list <string> food;
	list <string>::iterator itt;

	cout << "vector is empty " << (text.empty() ? "true" : "false") << endl;/* check vector is empty */
	cout << "size of vector " << text.size() << endl; /* check the size of vector */

	/* push 3 string into the vector */
	text.push_back("liu");
	text.push_back("hai");
	text.push_back("xiang");

	/* browse the vector */
	for (i =  0; i < text.size(); i ++) {
		cout << "text[" << i << "]" << text[i] << endl;
	}

	/* pop */
	text.pop_back();
	/* browse the vector */
	for (i =  0; i < text.size(); i ++) {
		cout << "text[" << i << "]" << text[i] << endl;
	}

	/* change the element with index */
	text[1] = "jie";
	text.push_back("juan");
	/* browse the vector */
	for (i =  0; i < text.size(); i ++) {
		cout << "text[" << i << "]" << text[i] << endl;
	}

	/* insert element before position */
	text.insert(text.begin(), "Mrs");
	/* browse the vector */
	for (i =  0; i < text.size(); i ++) {
		cout << "text[" << i << "]" << text[i] << endl;
	}

	/* iterator */
	for (it = text.begin(); it != text.end(); it++) {
		cout << *it << endl;
	}

	/* insert list */
	food.push_back("Strawberry");
	food.push_back("Chocolate");
	food.push_back("Vanilla");

	for (itt = food.begin(); itt != food.end(); ++itt) {
		cout << *itt << endl;
	}

	food.sort();
	cout << "after sort ..." << endl;
	for (itt = food.begin(); itt != food.end(); ++itt) {
		cout << *itt << endl;
	}


	return 0;
}
