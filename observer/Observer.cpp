#include <iostream>
#include <vector>

typedef int State;

class Subject;

class Observer {
public:
    virtual ~Observer() {};

    virtual void Update(Subject *) = 0;

    virtual State GetState() = 0;
};

class ConcreteObserver :
        public Observer {
public:
    ConcreteObserver(const State &state) :
            observerState(state) {}

    void Update(Subject *subject);

    State GetState() {
        return observerState;
    }

private:
    State observerState;
};

class Subject {
public:
    virtual ~Subject() {};

    void Attach(Observer *observer) {
        observers.push_back(observer);
    }

    void Detach(const size_t &index) {
        if (index >= observers.size()) {
            return;
        }
        observers.erase(observers.begin() + index);
    }

    void Notify() {
        for (std::vector<Observer *>::iterator iterator = observers.begin();
             iterator != observers.end();
             ++iterator) {
            (*iterator)->Update(this);
        }
    }

    virtual State GetState() = 0;

    virtual void SetState(const State &) = 0;

private:
    std::vector<Observer *> observers;
};

class ConcreteSubject :
        public Subject {
public:
    State GetState() {
        return subjectState;
    }

    void SetState(const State &state) {
        subjectState = state;
    }

private:
    State subjectState;
};

void ConcreteObserver::Update(Subject *subject) {
    observerState = subject->GetState();
}

int main() {
    ConcreteObserver observer1(1);
    ConcreteObserver observer2(2);
    std::cout << "observer1 state: " << observer1.GetState() << std::endl;
    std::cout << "observer2 state: " << observer2.GetState() << std::endl;
    ConcreteSubject concreteSubject;
    Subject *subject = &concreteSubject;
    subject->Attach(&observer1);
    subject->Attach(&observer2);
    subject->SetState(3);
    subject->Notify();
    std::cout << "observer1 state: " << observer1.GetState() << std::endl;
    std::cout << "observer2 state: " << observer2.GetState() << std::endl;
    subject->Detach(0);
    subject->SetState(4);
    subject->Notify();
    std::cout << "observer1 state: " << observer1.GetState() << std::endl;
    std::cout << "observer2 state: " << observer2.GetState() << std::endl;
    return 0;
}