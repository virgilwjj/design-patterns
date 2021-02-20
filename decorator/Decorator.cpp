#include <iostream>

class Component {
public:
    virtual ~Component() {}

    virtual void Operation() = 0;
};

class ConcreteComponent :
        public Component {
public:
    void Operation() {
        std::cout << "Operation()" << std::endl;
    }
};

class Decorator :
        public Component {
public:
    Decorator(Component *component) :
            component(component) {}

    void Operation() {
        component->Operation();
    }

private:
    Component *component;
};

typedef int State;

class ConcreteDecoratorA :
        public Decorator {
public:
    ConcreteDecoratorA(Component *component) :
            Decorator(component),
            addedState(0) {}

    void Operation() {
        Decorator::Operation();
        std::cout << "addedState: " << addedState << std::endl;
    }

private:
    State addedState;
};

class ConcreteDecoratorB :
        public Decorator {
public:
    ConcreteDecoratorB(Component *component) :
            Decorator(component) {}

    void Operation() {
        Decorator::Operation();
        AddedBehavior();
    }

    void AddedBehavior() {
        std::cout << "AddedBehavior()" << std::endl;
    }
};

int main() {
    ConcreteComponent concreteComponent = ConcreteComponent();
    ConcreteDecoratorA concreteDecoratorA = ConcreteDecoratorA(&concreteComponent);
    ConcreteDecoratorB concreteDecoratorB = ConcreteDecoratorB(&concreteDecoratorA);
    Component *component = &concreteDecoratorB;
    component->Operation();
    return 0;
}