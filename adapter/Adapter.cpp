#include <iostream>

class Target {
public:
    virtual ~Target() {}

    virtual void Request() = 0;
};

class Adaptee {
public:
    void SpecificRequest() {
        std::cout << "SpecificRequest()" << std::endl;
    }
};

class AdapterA :
        public Target,
        private Adaptee {
public:
    void Request() {
        SpecificRequest();
    }
};

class AdapterB :
        public Target {
public:
    void Request() {
        adaptee.SpecificRequest();
    }

private:
    Adaptee adaptee;
};

int main() {
    AdapterA adapterA;
    AdapterB adapterB;
    Target *target1 = &adapterA;
    Target *target2 = &adapterB;
    target1->Request();
    target2->Request();
    return 0;
}