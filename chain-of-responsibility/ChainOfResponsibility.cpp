#include <iostream>

class Handler {
public:
    Handler():
            successor(nullptr) {}

    virtual ~Handler() {}

    virtual void SetHandler(Handler *successor) {
        this->successor = successor;
    }

    virtual void HandleRequest() {
        if (successor != nullptr) {
            successor->HandleRequest();
        }
    }

private:
    Handler *successor;
};

class ConcreteHandler1:
        public Handler {
public:
    void HandleRequest() {
        std::cout << "ConcreteHandler1" << std::endl;
        Handler::HandleRequest();
    }
};

class ConcreteHandler2:
        public Handler {
public:
    void HandleRequest() {
        std::cout << "ConcreteHandler2" << std::endl;
        Handler::HandleRequest();
    }
};

int main() {
    ConcreteHandler1 handler1;
    ConcreteHandler2 handler2;
    ConcreteHandler1 handler3;
    ConcreteHandler2 handler4;
    handler1.SetHandler(&handler2);
    handler2.SetHandler(&handler3);
    handler3.SetHandler(&handler4);
    Handler *handler = &handler1;
    handler->HandleRequest();
    return 0;
}