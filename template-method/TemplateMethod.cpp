#include <iostream>

class AbstractClass {
public:
    virtual ~AbstractClass() {};

    void TemplateMethod() {
        // ...
        PrimitiveOperation1();
        // ...
        PrimitiveOperation2();
        // ...
    }

protected:
    virtual void PrimitiveOperation1() = 0;

    virtual void PrimitiveOperation2() = 0;
};

class ConcreteClass :
        public AbstractClass {
protected:
    void PrimitiveOperation1() {
        std::cout << "PrimitiveOperation1()" << std::endl;
    }

    void PrimitiveOperation2() {
        std::cout << "PrimitiveOperation2()" << std::endl;
    }
};

int main() {
    ConcreteClass concreteClass;
    AbstractClass *abstractClass = &concreteClass;
    abstractClass->TemplateMethod();
    return 0;
}