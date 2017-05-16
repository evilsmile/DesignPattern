#include <iostream>
#include <string>
#include <vector>

class IObserver {
    public:
        virtual void update() = 0;
};


class Supermarket {
    public:
        Supermarket(const std::string& name) : _name(name){}

        void append(IObserver* o) {
            _observers.push_back(o);
        }

        void detach(IObserver* o) {
            std::vector<IObserver*>::iterator iter;
            for (iter = _observers.begin();
                    iter != _observers.end();
                    ++iter) {
                if (o == *iter) {
                    _observers.erase(iter);
                }
            }
        }

        void notify() {
            std::cout << _name << " is notifying..." << std::endl;
            std::vector<IObserver*>::iterator iter;
            for (iter = _observers.begin();
                    iter != _observers.end();
                    ++iter) {
                (*iter)->update();
            }           
        }

    private:
        std::string _name;
        std::vector<IObserver*> _observers;
};

class Buyer1 : public IObserver {
    public:
        void update() {
            std::cout << "Buyer 1 notified." << std::endl;
        }
};

class Buyer2 : public IObserver {
    public:
        void update() {
            std::cout << "Buyer 2 notified." << std::endl;
        }
};

int main()
{
    Supermarket sm("Wow");

    Buyer1 *buyer1 = new Buyer1;
    Buyer2 *buyer2 = new Buyer2;

    // 添加两个观察者
    sm.append(buyer1);
    sm.append(buyer2);

    // 测试通知
    sm.notify();

    // 去除一个观察者
    sm.detach(buyer1);
    // 测试通知
    sm.notify();

    return 0;
}
