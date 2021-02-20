#include <iostream>
#include <unordered_map>

typedef int State;

class Flyweight {
public:
    virtual ~Flyweight() {}

    virtual void Operation(const State &extrinsicState) = 0;
};

class UnsharedConcreteFlyweight :
        public Flyweight {
public:
    void Operation(const State &extrinsicState) {
        allState = extrinsicState;
        std::cout << "UnsharedConcreteFlyweight state:" << allState << std::endl;
    }

private:
    State allState;
};

class ConcreteFlyweight :
        public Flyweight {
public:
    void Operation(const State &extrinsicState) {
        intrinsicState = extrinsicState;
        std::cout << "ConcreteFlyweight state:" << intrinsicState << std::endl;
    }

private:
    State intrinsicState;
};

class FlyweightFactory {
public:
    ~FlyweightFactory() {
        for (std::unordered_map<std::string, Flyweight *>::iterator iter = flyweights.begin();
             iter != flyweights.end(); ++iter) {
            delete iter->second;
        }
        flyweights.clear();
    }

    Flyweight *GetFlyweight(const std::string &key) {
        if (flyweights.find(key) != flyweights.end()) {
            return flyweights[key];
        } else {
            Flyweight *flyweight = new ConcreteFlyweight();
            flyweights[key] = flyweight;
            return flyweight;
        }
    }

private:
    std::unordered_map<std::string, Flyweight *> flyweights;
};

int main() {
    FlyweightFactory flyweightFactory;
    Flyweight *flyweight1 = flyweightFactory.GetFlyweight("key");
    Flyweight *flyweight2 = flyweightFactory.GetFlyweight("key");
    UnsharedConcreteFlyweight unsharedConcreteFlyweight;
    Flyweight *flyweight3 = &unsharedConcreteFlyweight;
    flyweight1->Operation(1);
    flyweight2->Operation(2);
    flyweight3->Operation(3);
    return 0;
}