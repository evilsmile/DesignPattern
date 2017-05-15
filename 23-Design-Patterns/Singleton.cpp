#include <iostream>
#include <string>

// 饿汉式初始化
// 线程安全，在类创建的同时就已经创建好一个静态的对象供系统调用，以后不再改变。
class CSingleton1 {
public:
    static CSingleton1* getInstance() {
        static CSingleton1 _s1;
        return &_s1;
    }

    void pp() {
        std::cout << "CSingleton does something" << std::endl;
    }

private:
    CSingleton1() {}
};

// 懒汉式初始化
// 不加锁的话可能导致线程不安全
#define lock()  
#define unlock()
class CSingleton2 {
public:
    static CSingleton2* getInstance() {
        // 对于加锁的优化，在外围先判断
        if (_s2 == NULL) {
            lock();
            if (_s2 == NULL) {
                _s2 = new CSingleton2;
            }
            unlock();
        }
        return _s2;
    }

    void pp() {
        std::cout << "CSingleton2 does something" << std::endl;
    }

private:

    // 为防止内存泄露，加上一个释放类
	class CGarbo {
	public:
	    ~CGarbo() {
	        if (CSingleton2::_s2) {
	            std::cout << "release s2 " << std::endl;
	            delete CSingleton2::_s2;
	        } 
        }
	};

    CSingleton2(){}

    static CSingleton2 *_s2;

    static CGarbo _g;
};
CSingleton2* CSingleton2::_s2 = NULL;
CSingleton2::CGarbo CSingleton2::_g;

int main()
{
    CSingleton1* s1 = CSingleton1::getInstance();
    if (s1 == NULL) {
        std::cerr << "Get NULL s1" << std::endl;
        return -1;
    }
    s1->pp();

    CSingleton2 *s2 = CSingleton2::getInstance();
    if (s2 == NULL) {
        std::cerr << "Get NULL s2" << std::endl;
        return -2;
    }
    s2->pp();

    return 0;
}
