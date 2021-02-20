#include <iostream>
#include <unordered_map>

class Context {
public:
    void Set(const std::string &var, const bool &value) {
        vars[var] = value;
    }

    bool Get(const std::string &exp) {
        return vars[exp];
    }

private:
    std::unordered_map<std::string, bool> vars;
};

class AbstractExpression {
public:
    virtual ~AbstractExpression() {}

    virtual bool Interpret(Context *) {
        return false;
    }
};

class TerminalExpression :
        public AbstractExpression {
public:
    TerminalExpression(const std::string &val) :
            value(val) {}

    bool Interpret(Context *context) {
        return context->Get(value);
    }

private:
    std::string value;
};

class NonterminalExpression :
        public AbstractExpression {
public:
    NonterminalExpression(AbstractExpression *left, AbstractExpression *right):
            lop(left),
            rop(right) {}

    ~NonterminalExpression() {
        delete lop;
        delete rop;
    }

    bool Interpret(Context *context) {
        return lop->Interpret(context) && rop->Interpret(context);
    }

private:
    AbstractExpression *lop;
    AbstractExpression *rop;
};


int main() {
    NonterminalExpression And(new TerminalExpression("A"),
                              new TerminalExpression("B"));
    AbstractExpression *expression = &And;
    Context context;
    context.Set("A", true);
    context.Set("B", false);
    std::cout << context.Get("A") << " AND "
              << context.Get("B") << " = "
              << expression->Interpret(&context)
              << std::endl;
    return 0;
}