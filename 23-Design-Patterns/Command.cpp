#include <string>
#include <iostream>

class ICommand {
    public:
        virtual void execute() = 0;
};

// 调用者Invoker和命令的执行者Command进一步解耦
class Invoker {
    public:
        void setCommand(ICommand* command) {
            this->_command = command;
        }
        void action() {
            this->_command->execute();
        }

    private:
        ICommand* _command;
};

// 负责接收命令并执行命令
// 实现命令的原子操作
class Receiver {
    public:
        void doA() {
            std::cout << "Recvier handling A ..." << std::endl;
        }
        void doB() {
            std::cout << "Recvier handling B ..." << std::endl;
        }

};

class ConcreteCommandA : public ICommand {
    public:
        ConcreteCommandA(Receiver* receiver) {
            this->_receiver = receiver;
        }

        // 在原子命令上封装的一层执行调用函数，公共对外公布函数
        void execute() {
            // 可以在这决定命令是怎么调用
            this->_receiver->doA();
        }
    private:
        Receiver* _receiver;
};

class ConcreteCommandB : public ICommand {
    public:
        ConcreteCommandB(Receiver* receiver) {
            this->_receiver = receiver;
        }

        // 在原子命令上封装的一层执行调用函数，公共对外公布函数
        void execute() {
            // 可以在这决定命令是怎么调用
            this->_receiver->doB();
        }
    private:
        Receiver* _receiver;
};


int main()
{
    Receiver* receiver = new Receiver;
    ICommand* command_a = new ConcreteCommandA(receiver);
    ICommand* command_b = new ConcreteCommandB(receiver);

    Invoker* invoker = new Invoker;
    invoker->setCommand(command_a);
    invoker->action();

    invoker->setCommand(command_b);
    invoker->action();

    return 0;
}
