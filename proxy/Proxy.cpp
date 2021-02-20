#include <iostream>

class Subject {
public:
    virtual ~Subject() {}

    virtual void Request() = 0;
};

class RealSubject :
        public Subject {
public:
    void Request() {
        std::cout << "RealSubject" << std::endl;
    }
};

class Proxy :
        public Subject {
public:
    Proxy(Subject *subject):
            realSubject(subject) {}

    void Request() {
        // ...
        realSubject->Request();
        // ...
    }

private:
    Subject *realSubject;
};

int main() {
    RealSubject realSubject;
    Proxy proxy(&realSubject);
    Subject *subject = &proxy;
    subject->Request();
    return 0;
}