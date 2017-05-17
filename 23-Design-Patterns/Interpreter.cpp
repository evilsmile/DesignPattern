#include <iostream>
#include <string>
#include <map>

class Context {
    public:
        void addValue(const std::string& key, int value) {
            _valueMap.insert(std::pair<std::string, int>(key, value));
        }

        int getValue(const std::string& key) {
            return _valueMap[key];
        }

    private:

        std::map<std::string, int> _valueMap;
};

class AbstractExpression {
    public:
        virtual int interpreter(Context *ctx) = 0;
};

class AddNonterminalExpression : public AbstractExpression {
    public:
        AddNonterminalExpression(AbstractExpression* left, AbstractExpression* right) {
            _left = left;
            _right = right;
        }

        int interpreter(Context *ctx) {
            return this->_left->interpreter(ctx) + this->_right->interpreter(ctx); 
        }

    private:
        AbstractExpression *_left;
        AbstractExpression *_right;
};

class SubtractNonterminalExpression : public AbstractExpression {
    public:
        SubtractNonterminalExpression(AbstractExpression* left, AbstractExpression* right) {
            _left = left;
            _right = right;
        }

        int interpreter(Context *ctx) {
            return this->_left->interpreter(ctx) - this->_right->interpreter(ctx); 
        }

    private:
        AbstractExpression *_left;
        AbstractExpression *_right;
};

class TerminalExpression : public AbstractExpression {
    public:
        TerminalExpression(int i) {
            this->_i = i;
        }

        int interpreter(Context* ctx) {
            return this->_i;
        }

    private:
        int _i;
};

int main()
{
    Context ctx;
    ctx.addValue("a", 20);
    ctx.addValue("b", 8);
    ctx.addValue("c", 2);

    SubtractNonterminalExpression *subtractValue = new SubtractNonterminalExpression(new TerminalExpression(ctx.getValue("a")), new TerminalExpression(ctx.getValue("b")));

    AddNonterminalExpression *addValue = new AddNonterminalExpression(subtractValue, new TerminalExpression(ctx.getValue("c")));

    std::cout << addValue->interpreter(&ctx) << std::endl;
    return 0;
}
