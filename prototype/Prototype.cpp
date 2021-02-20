#include <iostream>

class Prototype {
public:
    virtual ~Prototype() {}

    virtual Prototype* Clone() = 0;
};

class ConcretePrototype1 :
        public Prototype {
public:
    ConcretePrototype1() {}

    ConcretePrototype1(const ConcretePrototype1 &) {
        std::cout << "ConcretePrototype1(const ConcretePrototype1 &)" << std::endl;
    }

    Prototype* Clone() {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 :
        public Prototype {
public:
    ConcretePrototype2() {}

    ConcretePrototype2(const ConcretePrototype2 &) {
        std::cout << "ConcretePrototype2(const ConcretePrototype2 &)" << std::endl;
    }

    Prototype* Clone() {
        return new ConcretePrototype2(*this);
    }
};

class Client {
public:
    Client(Prototype *prototype):
            prototype(prototype) {}

    ~Client() {
        delete prototype;
    }

    void Operation() {
        Prototype *p = prototype->Clone();
        delete p;
    }

private:
    Prototype *prototype;
};

int main() {
    Client client1(new ConcretePrototype1());
    Client client2(new ConcretePrototype2());
    client1.Operation();
    client2.Operation();
    return 0;
}