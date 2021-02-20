#include <iostream>

class Implementor {
public:
    virtual ~Implementor() {}

    virtual void OperationImp() = 0;
};

class ConcreteImplementorA :
        public Implementor {
public:
    void OperationImp() {
        std::cout << "ConcreteImplementorA" << std::endl;
    }
};

class ConcreteImplementorB :
        public Implementor {
public:
    void OperationImp() {
        std::cout << "ConcreteImplementorB" << std::endl;
    }
};

class Abstraction {
public:
    virtual ~Abstraction() {
        delete imp;
    }

    Abstraction(Implementor *implementor):
            imp(implementor) {}

    void Operation() {
        imp->OperationImp();
    }

private:
    Implementor *imp;
};

class RefinedAbstraction :
        public Abstraction {
public:
    RefinedAbstraction(Implementor *implementor):
            Abstraction(implementor) {}
};

int main() {
    RefinedAbstraction refinedAbstraction1(new ConcreteImplementorA());
    RefinedAbstraction refinedAbstraction2(new ConcreteImplementorB());
    Abstraction *abstraction1 = &refinedAbstraction1;
    Abstraction *abstraction2 = &refinedAbstraction2;
    abstraction1->Operation();
    abstraction2->Operation();
    return 0;
}