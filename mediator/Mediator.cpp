#include <iostream>
#include <unordered_map>

class Mediator;

typedef std::string Id_t;

class Colleague {
public:
    Colleague(Mediator *mediator, const Id_t &id);

    virtual ~Colleague() {}

    Id_t GetId() {
        return id;
    }

    virtual void Send(const Id_t &receiverId, const std::string &msg) = 0;

    virtual void Receive(const Id_t &senderId, const std::string &msg) = 0;

protected:
    Mediator *mediator;
    Id_t id;
};

class ConcreteColleague1 :
        public Colleague {
public:
    ConcreteColleague1(Mediator *mediator, const Id_t &id):
            Colleague(mediator, id) {}

    void Send(const Id_t &receiverId, const std::string &msg);

    void Receive(const Id_t &senderId, const std::string &msg) {
        std::cout << "ConcreteColleague1, id: " << id << " received: '" << msg << "' from senderId: " << senderId << std::endl;
    }
};

class ConcreteColleague2 :
        public Colleague {
public:
    ConcreteColleague2(Mediator *mediator, const Id_t &id):
            Colleague(mediator, id) {}

    void Send(const Id_t &receiverId, const std::string &msg);

    void Receive(const Id_t &senderId, const std::string &msg) {
        std::cout << "ConcreteColleague2, id: " << id << " received: '" << msg << "' from senderId: " << senderId << std::endl;
    }
};

class Mediator {
public:
    virtual ~Mediator() {}

    virtual void Register(Colleague* colleague) = 0;

    virtual void Distribute(Colleague *sender, const Id_t &receiverId, const std::string &msg) = 0;
};

class ConcreteMediator :
        public Mediator {
public:
    void Register(Colleague *colleague) {
        colleagues[colleague->GetId()] = colleague;
    }

    void Distribute(Colleague *sender, const Id_t &receiverId, const std::string &msg) {
        colleagues[receiverId]->Receive(sender->GetId(), msg);
    }

private:
    std::unordered_map<Id_t, Colleague *> colleagues;
};

Colleague::Colleague(Mediator *mediator, const Id_t &id):
        mediator(mediator),
        id(id) {
    mediator->Register(this);
}

void ConcreteColleague1::Send(const Id_t &receiverId, const std::string &msg) {
    std::cout << "ConcreteColleague1, id: " << id << " send: '" << msg << "' to receiverId: " << receiverId << std::endl;
    mediator->Distribute(this, receiverId, msg);
}

void ConcreteColleague2::Send(const Id_t &receiverId, const std::string &msg) {
    std::cout << "ConcreteColleague2, id: " << id << " send: '" << msg << "' to receiverId: " << receiverId << std::endl;
    mediator->Distribute(this, receiverId, msg);
}

int main() {
    ConcreteMediator concreteMediator;
    ConcreteColleague1 concreteColleague1(&concreteMediator, "1");
    ConcreteColleague2 concreteColleague2(&concreteMediator, "2");
    ConcreteColleague1 concreteColleague3(&concreteMediator, "3");
    Colleague *colleague1 = &concreteColleague1;
    Colleague *colleague2 = &concreteColleague2;
    Colleague *colleague3 = &concreteColleague3;
    colleague1->Send("2", "Hello");
    colleague2->Send("3", "World");
    colleague3->Send("1", "Design Patterns");
    return 0;
}