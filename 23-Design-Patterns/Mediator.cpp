#include <string>
#include <iostream>

// 示例中的两个类，B的值是A值的1000倍，形成同事类关系
////////////////// 修改前 /////////////
class IColleague {
public:
    int getNumber() {
        return _number;
    }

    void setNumber(int number) {
        this->_number = number;
    }

    void showNumber() {
        std::cout << "number: " << _number << std::endl;
    }

    virtual void setNumber(int number, IColleague* coll) = 0;

protected:
    int _number;
};

class ColleageA : public IColleague {
public:
    void setNumber(int number, IColleague *coll) {
        this->_number = number;
        coll->setNumber(number * 1000);
    }
};

class ColleageB : public IColleague {
public:
    void setNumber(int number, IColleague *coll) {
        this->_number = number;
        coll->setNumber(number / 1000);
    }
};


////////////////// 修改后 /////////////
class IColleague2;

class IMediator {
public:
    IMediator(IColleague2* a, IColleague2* b) {
        this->_a = a;
        this->_b = b;
    }

    virtual void AAffectB() = 0;
    virtual void BAffectA() = 0;

protected:
    IColleague2* _a;
    IColleague2* _b;
};

class IColleague2 {
public:
    int getNumber() {
        return _number;
    }

    void setNumber(int number) {
        this->_number = number;
    }

    void showNumber() {
        std::cout << "number: " << _number << std::endl;
    }

    virtual void setNumber(int number, IMediator* im) = 0;

protected:
    int _number;
};

class ColleageA2 : public IColleague2 {
public:
    void setNumber(int number, IMediator *im) {
        this->_number = number;
        im->AAffectB();
    }
};

class ColleageB2 : public IColleague2 {
public:
    void setNumber(int number, IMediator *im) {
        this->_number = number;
        im->BAffectA();
    }
};


class Mediator : public IMediator {
public:
    Mediator(IColleague2* a, IColleague2* b) : IMediator(a, b) {}

    void AAffectB() {
        int number = _a->getNumber();
        _b->setNumber(number * 1000);
    }

    void BAffectA() {
        int number = _b->getNumber();
        _a->setNumber(number / 1000);
    }
};


int main()
{
    IColleague *coll_a = new ColleageA();
    IColleague *coll_b = new ColleageB();

    coll_a->setNumber(1288, coll_b);
    coll_a->showNumber();
    coll_b->showNumber();

    IColleague2 *coll_a2 = new ColleageA2();
    IColleague2 *coll_b2 = new ColleageB2();
    IMediator* im = new Mediator(coll_a2, coll_b2);
    coll_a2->setNumber(222, im);
    coll_b2->setNumber(2222334, im);
    coll_a2->showNumber();
    coll_b2->showNumber();

    return 0;
}
