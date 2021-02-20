#include <iostream>
#include <vector>

class Component {
public:
    virtual ~Component() {}

    virtual void Operation() = 0;

    virtual void Add(Component *) {};

    virtual void Remove(Component *) {}

    virtual Component *GetChild(const int &) {
        return nullptr;
    };
};

class Composite :
        public Component {
public:
    ~Composite() {
        for (std::vector<Component *>::iterator iter = children.begin();
             iter != children.end();
             ++iter) {
            delete *iter;
        }
        children.clear();
    }

    void Operation() {
        for (std::vector<Component *>::iterator iter = children.begin();
             iter != children.end();
             ++iter) {
            (*iter)->Operation();
        }
    }

    void Add(Component *component) {
        children.push_back(component);
    }

    void Remove(Component *component) {
        for (std::vector<Component *>::iterator iter = children.begin();
             iter != children.end();
             ++iter) {
            if ((*iter) == component) {
                children.erase(iter);
                delete component;
            }
        }
    }

    Component *GetChild(const int &index) {
        return children[index];
    }

private:
    std::vector<Component *> children;
};

class Leaf :
        public Component {
public:
    Leaf(const int &id) :
            id(id) {}

    void Operation() {
        std::cout << "Leaf id: "<< id << std::endl;
    }

private:
    int id;
};

int main() {
    Composite composite;
    for (int i = 1; i < 4; ++i) {
        Component *component = new Composite();
        for (int j = 1; j < 4; ++j) {
            component->Add(new Leaf(10 * i + j));
        }
        composite.Add(component);
    }
    composite.Operation();
    return 0;
}