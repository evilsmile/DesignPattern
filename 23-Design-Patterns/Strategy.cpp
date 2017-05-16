#include <iostream>
#include <string>

class IStrategy {
    public:
        virtual void doSomething() = 0;
};

class Strategy1 : public IStrategy {
    public:
        void doSomething() {
            std::cout << "concrete strategy 1." << std::endl;
        }
};

class Strategy2 : public IStrategy {
    public:
        void doSomething() {
            std::cout << "concrete strategy 2." << std::endl;
        }
};

class Context {
    public:
        Context() {}
        Context(IStrategy* strategy) {
            this->_strategy = strategy;
        }

        void execute() {
            _strategy->doSomething();
        }
    private:
        IStrategy* _strategy;
};

int main()
{
    Context* context;
    context = new Context(new Strategy1());
    context->execute();

    context = new Context(new Strategy2());
    context->execute();

    return 0;
}
