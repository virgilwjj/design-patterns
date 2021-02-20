#include <iostream>

class Receiver {
public:
    void Action() {
        std::cout << "Action()" << std::endl;
    }
};

class Command {
public:
    virtual ~Command() {}

    virtual void Execute() = 0;
};

class ConcreteCommand:
        public Command {
public:
    ConcreteCommand(Receiver *receiver):
            receiver(receiver) {}

    ~ConcreteCommand() {
        if (receiver != nullptr) {
            delete receiver;
        }
    }

    void Execute() {
        receiver->Action();
    }

private:
    Receiver *receiver;
};

class Invoker {
public:
    Invoker():
            command(nullptr) {}


    void Set(Command *command) {
        this->command = command;
    }

    void Confirm() {
        if (command != nullptr) {
            command->Execute();
        }
    }

private:
    Command *command;
};

int main() {
    ConcreteCommand concreteCommand(new Receiver());
    Invoker invoker;
    invoker.Set(&concreteCommand);
    invoker.Confirm();
    return 0;
}