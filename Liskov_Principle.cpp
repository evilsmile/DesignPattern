#include <iostream>
#include <string>

class Computer {
public:
    virtual void use() = 0;
};

class IBM : public Computer {
public:
    void use() {
        std::cout << "Use IBM Computer" << std::endl;
    }
};

class HP : public Computer {
public:
    void use() {
        std::cout << "Use HP Computer" << std::endl;
    }
};

int main()
{
    Computer *ibm = new IBM();
    Computer *hp = new HP();   // 引用基类的地方能透明地使用其子类的对象

    ibm->use();
    hp->use();

    return 0;
}
