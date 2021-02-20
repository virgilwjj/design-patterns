#include <iostream>

class Product {};

class Builder {
public:
    virtual ~Builder() {}

    Product *GetResult() {
        return product;
    }

    virtual void BuildPart() = 0;

protected:
    Product *product;
};

class ConcreteBuilder :
        public Builder {
public:
    void BuildPart() {}
};

class Director {
public:
    Director(Builder *builder) :
            builder(builder) {}

    ~Director() {
        delete builder;
    }

    Product *Construct() {
        builder->BuildPart();
        return builder->GetResult();
    }

private:
    Builder *builder;
};

int main() {
    Director director(new ConcreteBuilder());
    Product *product = director.Construct();
    return 0;
}