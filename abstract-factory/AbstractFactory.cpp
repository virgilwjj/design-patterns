#include <iostream>

class AbstractProductA {
public:
    virtual ~AbstractProductA() {}
};

class ProductA1 :
        public AbstractProductA {
public:
    ProductA1() {
        std::cout << "ProductA1()" << std::endl;
    }
};

class ProductA2 :
        public AbstractProductA {
public:
    ProductA2() {
        std::cout << "ProductA2()" << std::endl;
    }
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() {}
};

class ProductB1
        : public AbstractProductB {
public:
    ProductB1() {
        std::cout << "ProductB1()" << std::endl;
    }
};

class ProductB2
        : public AbstractProductB {
public:
    ProductB2() {
        std::cout << "ProductB2()" << std::endl;
    }
};

class AbstractFactory {
public:
    virtual ~AbstractFactory() {}

    virtual AbstractProductA *CreateProductA() = 0;

    virtual AbstractProductB *CreateProductB() = 0;
};

class ConcreteFactory1 :
        public AbstractFactory {
public:
    AbstractProductA *CreateProductA() {
        return new ProductA1();
    }

    AbstractProductB *CreateProductB() {
        return new ProductB1();
    }
};

class ConcreteFactory2 :
        public AbstractFactory {
public:
    AbstractProductA *CreateProductA() {
        return new ProductA2();
    }

    AbstractProductB *CreateProductB() {
        return new ProductB2();
    }
};

int main() {
    ConcreteFactory1 concreteFactory1;
    ConcreteFactory2 concreteFactory2;
    AbstractFactory *factory1 = &concreteFactory1;
    AbstractFactory *factory2 = &concreteFactory2;
    AbstractProductA *productA1 = factory1->CreateProductA();
    AbstractProductB *productB1 = factory1->CreateProductB();
    AbstractProductA *productA2 = factory2->CreateProductA();
    AbstractProductB *productB2 = factory2->CreateProductB();
    delete productA1;
    delete productB1;
    delete productA2;
    delete productB2;
    return 0;
}