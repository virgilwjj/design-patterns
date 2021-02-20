#include <iostream>

class Strategy {
public:
    virtual ~Strategy() {};

    virtual void AlgorithmInterface() = 0;
};

class ConcreteStrategyA :
        public Strategy {
public:
    void AlgorithmInterface() {
        std::cout << "ConcreteStrategyA" << std::endl;
    }
};

class ConcreteStrategyB :
        public Strategy {
public:
    void AlgorithmInterface() {
        std::cout << "ConcreteStrategyB" << std::endl;
    }
};

class ConcreteStrategyC :
        public Strategy {
public:
    void AlgorithmInterface() {
        std::cout << "ConcreteStrategyC" << std::endl;
    }
};

class Context {
public:
    Context(Strategy *strategy) :
            strategy(strategy) {}

    ~Context() {
        delete strategy;
    }

    void ContextInterface() {
        strategy->AlgorithmInterface();
    }

private:
    Strategy *strategy;
};

int main() {
    Context context1(new ConcreteStrategyA());
    Context context2(new ConcreteStrategyB());
    Context context3(new ConcreteStrategyC());
    context1.ContextInterface();
    context2.ContextInterface();
    context3.ContextInterface();
    return 0;
}