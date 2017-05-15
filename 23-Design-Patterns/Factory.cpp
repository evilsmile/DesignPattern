#include <string>
#include <iostream>

#define CHCK_PRODUCT(p)                                  \
    if (prt == NULL) {                                   \
        std::cerr << "get no product." << std::endl;     \
        return -1;                                       \
    } 

// 假设生产两种产品A, B
enum PRODUCT_TYPE{
    A = 0, 
    B = 1
};

class IProduct {
public:
    virtual void sell() = 0;
};

class ProductA : public IProduct {
public:
    void sell() {
        std::cout << "I'm selling A" << std::endl;
    }
};

class ProductB : public IProduct {
public:
    void sell() {
        std::cout << "I'm selling B" << std::endl;
    }
};

// 1. 简单工厂模式 
// 每增加一种产品就要改工厂代码 
// 违反开闭原则 
class IFactory {
public:
    virtual IProduct* produce(PRODUCT_TYPE ) = 0;
};

class Factory : public IFactory {
public:
    IProduct* produce(PRODUCT_TYPE type) {
        if (type == A) {
            return new ProductA;
        } else if (type == B) {
            return new ProductB;
        }else {
            std::cerr << "Unknown type: " << type << std::endl;
            return NULL;
        }
    }
};

// 2. 工厂方法模式
// 需要更多的类定义
class IFactory2 {
public:
    virtual IProduct* produce() = 0;
};

// 每增加一个产品就要增加一个工厂类
class FactoryA : public IFactory2 {
public:
    IProduct* produce() {
        return new ProductA;
    }
};

class FactoryB : public IFactory2 {
public:
    IProduct* produce() {
        return new ProductB;
    }
};

// 3. 抽象工厂模式
// 提供一个创建一系列想着或相互依赖对象的接口，而无需指定它们具体的类

// 又有了新的产品
class INewProduct {
public:
    virtual void sell() = 0;
};

class NewProductA : public INewProduct {
public:
    void sell() {
        std::cout << "I'm selling new A" << std::endl;
    }
};

class NewProductB : public INewProduct {
public:
    void sell() {
        std::cout << "I'm selling new B" << std::endl;
    }
};

// 工厂既要生产新的产品，也要生产旧产品
class ICompoundFactory {
public:
    virtual IProduct* produce() = 0;
    virtual INewProduct* produce_new() = 0;
};

class CompoundFactoryA : public ICompoundFactory {
public:
    IProduct* produce() { 
        return new ProductA;
    }
    INewProduct* produce_new() {
        return new NewProductA;
    }
};

class CompoundFactoryB : public ICompoundFactory {
public:
    IProduct* produce() { 
        return new ProductB;
    }
    INewProduct* produce_new() {
        return new NewProductB;
    }
};

int main()
{
    Factory f;
    IProduct *prt = f.produce(A);
    CHCK_PRODUCT(prt);
    prt->sell();

    FactoryB fb;
    prt = fb.produce();
    CHCK_PRODUCT(prt);
    prt->sell();

    CompoundFactoryA cfa;
    prt = cfa.produce();
    INewProduct *nprt = cfa.produce_new();
    prt->sell();
    nprt->sell();

    return 0;
}
