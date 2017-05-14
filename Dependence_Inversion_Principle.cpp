#include <string>
#include <iostream>

//////////////////////////////////////////////////
// 版本1: 脆弱的设计。Jim现在只能吃苹果，如果要吃香蕉或别的水果，则要不断地个性Jim里的代码。频繁修改会带来很大的系统风险。
// Jim类依赖于Apple，两者是紧耦合的关系，其导致的结果就是系统的可维护性大大降低。

class Apple {
public:
    std::string getName() {
        return "apple";
    }
};

class Jim {
public:
    void eat(Apple* apple) {
        std::cout << "Jim eat " + apple->getName() << std::endl;
    }
};

//////////////////////////////////////////////////
// 版本2: 根据依赖倒置原则，提取抽象的部分：People, Fruit, 提供各自必需的方法，这样无论以后是增加别的人类或是水果，都只需要增加自己的实现类。由于遵循依赖倒置原则，只依赖于抽象，而不依赖于细节，所以增加类无需修改其他类.

// People类是复杂的业务逻辑，属于高层模块。而Fruit是原子模块，属于低层模块。People依赖于抽象的Fruit接口，这就做到了：高层模块不应该依赖于低层模块，两者都依赖于抽象类或接口。
// People和Fruit接口与各自的实现类没有关系，增加实现类不会影响接口，这就做到了：抽象不应该依赖于细节。
// Jim2、Apple2、Banana实现类都要去实现各自的接口所定义的抽象方法，所以是依赖于接口的。这就做到了：细节应该依赖抽象。

class Fruit {
public:
    virtual std::string getName() = 0;
};

class People {
public:
    virtual void eat(Fruit *fruit) = 0;
};

class Jim2 : public People {
    void eat(Fruit *fruit) {
        std::cout << "Jim2 eats " + fruit->getName() << std::endl;
    }
};

class Apple2 : public Fruit {
    std::string getName() {
        return "apple2";
    }
};

class Banana : public Fruit {
    std::string getName() {
        return "banana";
    }
};

//////////////////////////////////////////////////
// 依赖的传递：
class Jim3 : public People {
public:
    // 通过构造函数传递
    Jim3(Fruit* fruit) {
        this->_fruit = fruit;
    }

    // 通过setXXX方法传递依赖对象
    void setFruit(Fruit* fruit) {
        this->_fruit = fruit;
    }

    void eat(Fruit* fruit) {
        std::cout << "Jim3 eats " + this->_fruit->getName() << std::endl;
    }
private:
    Fruit *_fruit;
};

int main()
{
    Jim* jim = new Jim;
    Apple* apple = new Apple;
    jim->eat(apple);

    People* jim2 = new Jim2;
    Fruit* apple2 = new Apple2;
    jim2->eat(apple2);
    Fruit* banana = new Banana;
    jim2->eat(banana);

    Banana* banana2 = new Banana;
    People* jim3 = new Jim3(banana2);
    jim3->eat(apple2);
    dynamic_cast<Jim3*>(jim3)->setFruit(apple2);
    jim3->eat(banana2);

    return 0;
}
