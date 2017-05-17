#include <string>
#include <iostream>

class Memento {
    public:
        Memento() { }
        Memento(const std::string& state) {
            this->_state = state;
        }

        const std::string& getState() const {
            return _state;
        }

        void setState(const std::string& state) {
            this->_state = state;
        }

    private:
        std::string _state;
};

class Originator {
    public:
        Originator() {}

        const std::string& getState() const {
            return _state;
        }

        void setState(const std::string& state) {
            this->_state = state;
        }

        Memento createMemento() {
            return Memento(this->_state);
        }

        void restoreMemento(const Memento& memento) {
            this->_state = memento.getState();
        }

    private:
        std::string _state;
};

class Caretaker {
    public:
        const Memento& getMemento() const {
            return _memento;
        }

        void setMemento(const Memento& memento) {
            this->_memento = memento;
        }

    private:
        Memento _memento;
};

int main()
{
    Originator originator;
    originator.setState("State I");
    std::cout << "Init state: " << originator.getState() << std::endl;

    Caretaker caretaker;
    caretaker.setMemento(originator.createMemento());
    originator.setState("State II");
    std::cout << "After change: " << originator.getState() << std::endl;

    originator.restoreMemento(caretaker.getMemento());
    std::cout << "After restore: " << originator.getState() << std::endl;

    return 0;
}
