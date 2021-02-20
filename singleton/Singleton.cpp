#include <iostream>
#include <atomic>

class SingletonA {
public:
    static SingletonA *Instance() {
        return uniqueInstance;
    }

    void SingletonOperation() {
        std::cout << "SingletonA" << std::endl;
    }

    int GetSingletonData() {
        return singletonData;
    }

private:
    SingletonA() {}

    SingletonA(const SingletonA &);

    SingletonA& operator=(const SingletonA &);

    static SingletonA *uniqueInstance;

    int singletonData;
};

SingletonA *SingletonA::uniqueInstance = new SingletonA();

class SingletonB {
public:
    static SingletonB *Instance() {
        if (uniqueInstance == nullptr) {
            uniqueInstance = new SingletonB();
        }
        return uniqueInstance;
    }

    void SingletonOperation() {
        std::cout << "SingletonB" << std::endl;
    }

    int GetSingletonData() {
        return singletonData;
    }

private:
    SingletonB() {}

    SingletonB(const SingletonB &);

    SingletonB& operator=(const SingletonB &);

    static SingletonB *uniqueInstance;

    int singletonData;
};

SingletonB *SingletonB::uniqueInstance = nullptr;

class SingletonC {
public:
    static SingletonC *Instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (uniqueInstance == nullptr) {
            uniqueInstance = new SingletonC();
        }
        return uniqueInstance;
    }

    void SingletonOperation() {
        std::cout << "SingletonC" << std::endl;
    }

    int GetSingletonData() {
        return singletonData;
    }

private:
    SingletonC() {}

    SingletonC(const SingletonC &);

    SingletonC& operator=(const SingletonC &);

    static SingletonC *uniqueInstance;

    static std::mutex mutex;

    int singletonData;
};

SingletonC* SingletonC::uniqueInstance = nullptr;

std::mutex SingletonC::mutex;

class SingletonD {
public:
    static SingletonD *Instance() {
        SingletonD *tmp = uniqueInstance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            tmp = uniqueInstance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new SingletonD();
                std::atomic_thread_fence(std::memory_order_release);
                uniqueInstance.store(tmp, std::memory_order_relaxed);
            }
        }
        return tmp;
    }

    void SingletonOperation() {
        std::cout << "SingletonD" << std::endl;
    }

    int GetSingletonData() {
        return singletonData;
    }

private:
    SingletonD() {}

    SingletonD(const SingletonC &);

    SingletonD& operator=(const SingletonD &);

    static std::atomic<SingletonD *> uniqueInstance;

    static std::mutex mutex;

    int singletonData;
};

std::atomic<SingletonD *> SingletonD::uniqueInstance;

std::mutex SingletonD::mutex;

int main() {
    SingletonA::Instance()->SingletonOperation();
    SingletonB::Instance()->SingletonOperation();
    SingletonC::Instance()->SingletonOperation();
    SingletonD::Instance()->SingletonOperation();
    return 0;
}