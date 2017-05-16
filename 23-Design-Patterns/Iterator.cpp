#include <iostream>
#include <string>
#include <vector>

template<class Item>
class IIterator {
    public:
        virtual void first() = 0;
        virtual void next() = 0;
        virtual Item* currentItem() = 0;
        virtual bool isDone() = 0;
        virtual ~IIterator() {}
};

template<class Item>
class ConcreteAggregate;

template<class Item>
class ConcreteIterator : public IIterator<Item> {
    public:
        ConcreteIterator(ConcreteAggregate<Item> *a) : _a(a), _cur(0) {}

        virtual void first() { _cur = 0; }
        virtual void next() {
            if (_cur < _a->getLen()) {
                ++_cur;
            }
        }
        virtual Item* currentItem() {
            if (_cur < _a->getLen()) {
                return &(*_a)[_cur];
            } 

            return NULL;
        }
        virtual bool isDone() {
            return (_cur >= _a->getLen());
        }
    private:
        ConcreteAggregate<Item> *_a;
        int _cur;
};

template<class Item>
class Aggregate {
    public:
        virtual IIterator<Item>* createIterator() = 0;
        virtual ~Aggregate() {}
};

template<class Item>
class ConcreteAggregate : public Aggregate<Item> {
    public:
        ConcreteAggregate() {
            data.push_back(1);
            data.push_back(2);
            data.push_back(3);
        }

        virtual IIterator<Item>* createIterator() {
            return new ConcreteIterator<Item>(this);
        }

        Item& operator[](int index) {
            return data[index];
        }
        int getLen() {
            return data.size();
        }
    private:
        // 内部使用vector来存储
        std::vector<Item> data;
};

int main()
{
    Aggregate<int> *aggr = new ConcreteAggregate<int>();
    IIterator<int> *iter = aggr->createIterator();

    for (; !iter->isDone(); iter->next()) {
        std::cout << *(iter->currentItem()) << std::endl;
    }
    delete iter;
    delete aggr;

    return 0;
}
