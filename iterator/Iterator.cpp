#include <iostream>
#include <vector>

class Iterator;

class Aggregate {
public:
    virtual ~Aggregate() {}

    virtual Iterator *CreateIterator() = 0;

    virtual int At(const size_t &) = 0;

    virtual size_t Size() = 0;
};

class ConcreteAggregate:
        public Aggregate {
public:
    ConcreteAggregate(const std::vector<int> &array):
            array(array) {}

    Iterator *CreateIterator();

    int At(const size_t &index) {
        return array[index];
    }

    size_t Size() {
        return array.size();
    };

private:
    std::vector<int> array;
};

class Iterator {
public:
    virtual ~Iterator() {}

    virtual void First() = 0;

    virtual void Next() = 0;

    virtual bool IsDone() = 0;

    virtual int CurrentItem() = 0;
};

class ConcreteIterator:
        public Iterator {
public:
    ConcreteIterator(Aggregate *aggregate):
            aggregate(aggregate),
            index(0) {}

    void First() {
        index = 0;
    }

    void Next() {
        ++index;
    }

    bool IsDone() {
        return index >= aggregate->Size();
    }

    int CurrentItem() {
        if (IsDone()) {
            return -1;
        }
        return aggregate->At(index);
    }

private:
    Aggregate *aggregate;
    size_t index;
};

Iterator *ConcreteAggregate::CreateIterator() {
    return new ConcreteIterator(this);
}

int main() {
    std::vector<int> array(5);
    ConcreteAggregate concreteAggregate(array);
    for (Iterator *iterator = concreteAggregate.CreateIterator();
         !iterator->IsDone(); iterator->Next()) {
        std::cout << iterator->CurrentItem() << std::endl;
    }
    return 0;
}