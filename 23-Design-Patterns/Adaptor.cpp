#include <iostream>
#include <string>

class Target {
    public:
        virtual void Request() {}
        virtual void f1() {}
        virtual void f2() {}
        virtual void f3() {}
};

class Adaptee {
    public:
        void SpecifiedRequest() {
            std::cout << "called SpecifiedRequest()" << std::endl;
        }
};

// 类适配器
class CAdapter : public Adaptee, public Target {
    public:
        void Request() {
            this->SpecifiedRequest();
        }
};


// 对象适配器
class OAdapter : public Target {
    public:
        OAdapter() {
            _adaptee = new Adaptee();
        }

        void Request() {
            _adaptee->SpecifiedRequest();
        }

    private:
        Adaptee *_adaptee;
};

// 默认适配器
class DAdapter : public Target {
    public:
        void f1() {}
        void f2() {}
        void f3() {}
};

class MyInterest : public DAdapter {
    public:
        void f3() {
            std::cout << "My interest is " << __FUNCTION__ << std::endl;
        }
};

int main()
{
    Target *t = new CAdapter();
    t->Request();

    t = new OAdapter();
    t->Request();

    t = new MyInterest;
    t->f3();

    return 0;
}
