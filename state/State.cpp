#include <iostream>

class State {
public:
    virtual ~State() {}

    virtual void Handle() = 0;
};

class ConcreteStateA :
        public State {
public:
    void Handle() {
        std::cout << "ConcreteStateA" << std::endl;
    }
};

class ConcreteStateB :
        public State {
public:
    void Handle() {
        std::cout << "ConcreteStateB" << std::endl;
    }
};

class Context {
public:
    Context(State *state):
            state(state) {}

    ~Context() {
        delete state;
    }

    void SetState(State *state) {
        if (state == nullptr) {
            return;
        }
        if (this->state == state) {
            return;
        }
        delete this->state;
        this->state = state;
    }

    void Request() {
        state->Handle();
    }

private:
    State *state;
};

int main() {
    Context context(new ConcreteStateA());
    context.Request();
    context.SetState(new ConcreteStateB());
    context.Request();
    return 0;
}