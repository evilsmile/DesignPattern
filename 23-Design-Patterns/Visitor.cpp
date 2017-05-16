#include <iostream>
#include <string>
#include <list>

class IElement;

class IVisitor {
    public:
        virtual void visit(IElement *el) = 0;
};

class IElement {
    public:
        void accept(IVisitor* visitor) {
            visitor->visit(this);
        }
        virtual void doSomething() = 0;
};

class ConcreteElement1 : public IElement {
    public:
        void doSomething() {
            std::cout << "Concrete element 1" << std::endl;
        }
};

class ConcreteElement2 : public IElement {
    public:
        void doSomething() {
            std::cout << "Concrete element 2" << std::endl;
        }
};

class Visitor : public IVisitor {
    public:
        void visit(IElement *el) {
            el->doSomething();
        }
};

class ObjectStructure {
    public:
        static std::list<IElement*> getList() {
            std::list<IElement*> _list;
            for (int i = 0; i < 100; ++i) {
                if (i < 50) {
                    _list.push_back(new ConcreteElement1);
                } else {
                    _list.push_back(new ConcreteElement2);
                }
            }

            return _list;
        }
};

int main()
{
    std::list<IElement*> l = ObjectStructure::getList();
    for (std::list<IElement*>::iterator iter = l.begin();
            iter != l.end();
            ++iter) {
        (*iter)->accept(new Visitor);
    }

    return 0;
}
