#include <iostream>
#include <vector>

typedef int State;

class Memento {
private:
    friend class Originator;

    Memento(const State &state):
            state(state) {}

    State GetState() {
        return state;
    }

    void SetState(const State &state) {
        this->state = state;
    }

private:
    State state;
};

class Originator {
public:
    Originator(const State &state):
            state(state) {}

    void SetMemento(Memento *memento) {
        state = memento->GetState();
    }

    Memento *CreateMemento() {
        return new Memento(state);
    }

    State GetState() {
        return state;
    }

    void SetState(const State &state) {
        this->state = state;
    }

private:
    State state;
};

class Caretaker {
public:
    Caretaker(Originator* originator):
            originator(originator) {}

    ~Caretaker() {
        for (std::vector<Memento *>::iterator iter = history.begin();
             iter != history.end(); ++iter) {
            delete *iter;
        }
        history.clear();
    }

    void Save() {
        history.push_back(originator->CreateMemento());
    }

    void Undo() {
        if (history.empty()) {
            return;
        }
        Memento *memento = history.back();
        originator->SetMemento(memento);
        history.pop_back();
        delete memento;
    }

private:
    Originator *originator;
    std::vector<Memento*> history;
};

int main() {
    Originator originator(1);
    Caretaker caretaker(&originator);
    caretaker.Save();
    originator.SetState(2);
    caretaker.Save();
    originator.SetState(3);
    caretaker.Undo();
    std::cout << "State: " << originator.GetState() << std::endl;
    caretaker.Undo();
    std::cout << "State: " << originator.GetState() << std::endl;
    return 0;
}