#include <iostream>
#include <string>

///////////////////////////////////
// 版本1：A要找B，再找C来帮忙
// 
class C {
public:
    C(std::string name) {
        this->_name = name;
    }

    void work() {
        std::cout << _name << "把这件事做好了." << std::endl;
    }

private:
    std::string _name;
};

class B {
public:
    B(std::string name) {
        this->_name = name;
    }
    C* getC(std::string name) {
        std::cout << "找到" << _name << std::endl;
        return new C(name);
    }
private:
    std::string _name;
};

class A {
public:
    A(std::string name) { 
        this->_name = name; 
    }
    B* getB(std::string name) { 
        return new B(name); 
    }
    void work() {
        std::cout << _name << "想要帮助" << std::endl;
        B* b = getB("李四");
        C* c = b->getC("王五");
        c->work();
        delete b;
        delete c;
    }
private:
    std::string _name;
};

//////////////////////////////////////////////////
// 上面的版本中，虽然事情成功办好了，但是业务逻辑有点问题。A并不认识C为什么在A中出现了类C呢。
// 版本2: 类A只与最直接的朋友类B通信，不与类C通信
// 类A只调用类B提供的方法即可，不用关心类B内部是如何实现的
class C2 {
public:
    C2(std::string name) {
        this->_name =name;
    }
    void work() {
        std::cout << _name << "把事情做好了" << std::endl;
    }
private:
    std::string _name;
};

class B2 {
public:
    B2(std::string name) {
        this->_name = name;
    }

    C2* getC2(std::string name) {
        return new C2(name);
    }

    void work() {
        C2* c2 = getC2("王五2");
        c2->work();
    }
private:
    std::string _name;
};

class A2 {
public:
    A2(std::string name) {
        this->_name = name;
    }
    B2* getB2(std::string name) {
        return new B2(name);
    }

    void work() {
        B2* b2 = getB2("李四2");
        b2->work();
    }
private:
    std::string _name;
};

int main()
{
    A* a = new A("张三");
    a->work();

    A2* a2 = new A2("张三2");
    a2->work();

    return 0;
}
