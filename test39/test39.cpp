#include <iostream>

using namespace std;

class Device {
public:
    Device() {}
    virtual ~Device() {}

    void print_device() {
        cout << "this is device" << endl;
    }
private:
};

class IOSystem {
public:
    IOSystem() {}
    virtual ~IOSystem() {}

    void print_iosystem() {
        cout << "this is io system" << endl;
    }
private:
};

class Gateway : public Device, public IOSystem {
public:
    Gateway() {}
    virtual ~Gateway() {}

    void print_gateway() {
        cout << "this is gateway" << endl;
    }
private:
};

class Adapter : public Device {
public:
    Adapter() {}
    virtual ~Adapter() {}

    void print_adapter() {
        cout << "this is adapter" << endl;
    }
private:
};

int main() {
    Device* b = new Gateway();
    Device* d = new Adapter();

    if (Gateway* g = dynamic_cast<Gateway*>(b)) {
        g->print_gateway();
    } else {
        cout << "this is not gateway" << endl;
    }

    if (Adapter* a = dynamic_cast<Adapter*>(b)) {
        a->print_adapter();
    } else {
        cout << "this is not adapter" << endl;
    }

    if (Gateway* g = dynamic_cast<Gateway*>(d)) {
        g->print_gateway();
    } else {
        cout << "this is not gateway" << endl;
    }

    if (Adapter* a = dynamic_cast<Adapter*>(d)) {
        a->print_adapter();
    } else {
        cout << "this is not adapter" << endl;
    }

    if (IOSystem* i = dynamic_cast<IOSystem*>(b)) {
        i->print_iosystem();
    } else {
        cout << "this is not io system" << endl;
    }

    if (IOSystem* ii = dynamic_cast<IOSystem*>(d)) {
        ii->print_iosystem();
    } else {
        cout << "this is not io system" << endl;
    }

    return 0;
}

