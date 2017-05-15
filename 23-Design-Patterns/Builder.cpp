#include <string>
#include <iostream>

class Builder {
public:
    virtual void BuildHeader() {}
    virtual void BuildBody() {}
    virtual void BuildLeftArm() {}
    virtual void BuildRightArm() {}
    virtual void BuildLeftLeg() {}
    virtual void BuildRightLeg() {}
};

class ThinBuilder : public Builder {
public:
    void BuildHeader() { std::cout << "Build thin head." << std::endl; }
    void BuildBody() { std::cout << "Build thin body." << std::endl; }
    void BuildLeftArm() { std::cout << "Build thin left arm." << std::endl; }
    void BuildRightArm() { std::cout << "Build thin right arm." << std::endl; }
    void BuildLeftLeg() { std::cout << "Build thin left leg." << std::endl; }
    void BuildRightLeg() { std::cout << "Build thin right leg." << std::endl; }
};

class FatBuilder : public Builder {
public:
    void BuildHeader() { std::cout << "Build fat head." << std::endl; }
    void BuildBody() { std::cout << "Build fat body." << std::endl; }
    void BuildLeftArm() { std::cout << "Build fat left arm." << std::endl; }
    void BuildRightArm() { std::cout << "Build fat right arm." << std::endl; }
    void BuildLeftLeg() { std::cout << "Build fat left leg." << std::endl; }
    void BuildRightLeg() { std::cout << "Build fat right leg." << std::endl; }
};

class Director {
public:
    Director(Builder* builder) { this->_builder = builder; }
    void Create() {
        _builder->BuildHeader();
        _builder->BuildLeftArm();
        _builder->BuildRightArm();
        _builder->BuildLeftLeg();
        _builder->BuildRightLeg();
    }
private:
    Builder* _builder;
};

int main()
{
    FatBuilder fb;
    Director director(&fb);
    director.Create();

    return 0;
}
