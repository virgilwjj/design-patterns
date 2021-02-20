#include <iostream>

class Product {
public:
    virtual ~Product() {}
};

class ConcreteProduct :
        public Product {
public:
    ConcreteProduct() {
        std::cout << "ConcreteProduct()" << std::endl;
    }
};

class Creator {
public:
    virtual ~Creator() {}

    void AnOperation() {
        // ...
        Product *product = FactoryMethod();
        // ...
        delete product;
    }

protected:
    virtual Product *FactoryMethod() = 0;
};

class ConcreteCreator :
        public Creator {
private:
    Product *FactoryMethod() {
        return new ConcreteProduct();
    }
};

int main() {
    ConcreteCreator concreteCreator;
    Creator *creator = &concreteCreator;
    creator->AnOperation();
    return 0;
}