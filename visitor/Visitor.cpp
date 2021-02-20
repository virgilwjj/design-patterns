#include <iostream>

class Element;
class ConcreteElementA;
class ConcreteElementB;

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void VisitConcreteElementA(ConcreteElementA *) = 0;

    virtual void VisitConcreteElementB(ConcreteElementB *) = 0;
};

class ConcreteVisitor1:
        public Visitor {
public:
    void VisitConcreteElementA(ConcreteElementA *) {
        std::cout << "ConcreteVisitor1 VisitConcreteElementA()" << std::endl;
    }

    void VisitConcreteElementB(ConcreteElementB *) {
        std::cout << "ConcreteVisitor1 VisitConcreteElementB()" << std::endl;
    }
};

class ConcreteVisitor2:
        public Visitor {
public:
    void VisitConcreteElementA(ConcreteElementA *) {
        std::cout << "ConcreteVisitor2 VisitConcreteElementA()" << std::endl;
    }

    void VisitConcreteElementB(ConcreteElementB *) {
        std::cout << "ConcreteVisitor2 VisitConcreteElementB()" << std::endl;
    }
};

class Element {
public:
    virtual ~Element() {}

    virtual void Accept(Visitor *visitor) = 0;
};

class ConcreteElementA :
        public Element {
public:
    void Accept(Visitor *visitor) {
        visitor->VisitConcreteElementA(this);
    }
};

class ConcreteElementB:
        public Element {
public:
    void Accept(Visitor *visitor) {
        visitor->VisitConcreteElementB(this);
    }
};

int main() {
    ConcreteElementA elementA;
    ConcreteElementB elementB;
    ConcreteVisitor1 visitor1;
    ConcreteVisitor2 visitor2;
    elementA.Accept(&visitor1);
    elementA.Accept(&visitor2);
    elementB.Accept(&visitor1);
    elementB.Accept(&visitor2);
    return 0;
}
