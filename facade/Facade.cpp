#include <iostream>

class SubSystemA {
public:
    void SubOperation() {
        std::cout << "SubSystemA" << std::endl;
    }
};

class SubSystemB {
public:
    void SubOperation() {
        std::cout << "SubSystemB" << std::endl;
    }
};

class SubSystemC {
public:
    void SubOperation() {
        std::cout << "SubSystemC" << std::endl;
    }
};

class Facade {
public:
    Facade(SubSystemA *subSystemA, SubSystemB *subSystemB, SubSystemC *subSystemC) :
            subSystemA(subSystemA),
            subSystemB(subSystemB),
            subSystemC(subSystemC) {}

    void operation1() {
        subSystemA->SubOperation();
        subSystemB->SubOperation();
    }

    void operation2() {
        subSystemC->SubOperation();
    }

private:
    SubSystemA *subSystemA;
    SubSystemB *subSystemB;
    SubSystemC *subSystemC;
};

int main() {
    SubSystemA subSystemA;
    SubSystemB subSystemB;
    SubSystemC subSystemC;
    Facade facade(&subSystemA, &subSystemB, &subSystemC);
    facade.operation1();
    facade.operation2();
    return 0;
}