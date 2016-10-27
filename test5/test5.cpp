/* understand the observer design pattern */
/* https://en.wikipedia.org/wiki/Observer_pattern */
#include <iostream>
#include <vector>

using namespace std;

class Subject {
private:
	vector <class Observer *> views; // the vector for observer
	int value;
public:
	void attach(Observer *obs); // attach observer
	void set_value(int v);
	int get_value();
	void notify(); // notify the observer
};

class Observer {
public:
	Observer(Subject *sub); // constructor to register subscriber
	                        // no return type for constructor
	void update (int v); // callback when get notified by the subject
};

void Subject::attach (Observer *obs) {
	views.push_back(obs); // push the observer into vector list for register
	return;
}

void Subject::set_value(int v) {
	value = v;
	notify (); // notify observer
	return;
}

int Subject::get_value() {
	return value;
}

Observer::Observer(Subject *sub) {
	sub->attach (this);
	return;
}

void Observer::update(int v) {
	cout << "Observer: " << this << " observed subscriber value has been changed to " << v << endl;
	return;
}

void Subject::notify() {
	vector <class Observer *> :: iterator it;
	for (it = views.begin(); it != views.end(); ++it) {
		Observer* obs = *it;
		obs->update(get_value());
		//(*it)->update();
	}
}

int main ()
{
	Subject sub;
	Observer obs (&sub); // register observer to subject
                         // subscriber doesn't need to know who is observer
	Observer obs_1 (&sub);
	Observer obs_2 (&sub);

	sub.set_value(5);
	sub.set_value(10);

	return 0;
}
