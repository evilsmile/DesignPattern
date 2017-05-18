#include <iostream>
#include <string>
#include <map>

class Character {
    public:
        virtual ~Character(){}

        virtual void SetSize(int, int) = 0;
        virtual void Display() = 0;

    protected:
        Character(){}
        // 内部状态
        char _symbol;

        // 外部状态
        int _weight;
        int _height;
};

class CharacterA : public Character {
    public:
        CharacterA() {
            this->_symbol = 'A';
            this->_weight = 100;
            this->_height = 200;
        }

        virtual ~CharacterA() {}

        void SetSize(int weight, int height) {
            this->_weight = weight;
            this->_height = height;
        }

        void Display() {
            std::cout << "Character: " << _symbol << "(" << _weight << ", "
                << _height << ")" << std::endl;
        }
};

class CharacterB : public Character {
    public:
        CharacterB() {
            this->_symbol = 'B';
            this->_weight = 100;
            this->_height = 200;
        }

        virtual ~CharacterB() {}

        void SetSize(int weight, int height) {
            this->_weight = weight;
            this->_height = height;
        }

        void Display() {
            std::cout << "Character: " << _symbol << "(" << _weight << ", "
                << _height << ")" << std::endl;
        }
};


class CharacterFactory {
    public:
        CharacterFactory() {
            _char.insert(std::make_pair<char, Character*>('A', new CharacterA));
            _char.insert(std::make_pair<char, Character*>('B', new CharacterB));
        }

        virtual ~CharacterFactory() {}

        Character* GetCharacter(char c) {
            std::map<char, Character*>::iterator iter = _char.find(c);
            if (iter != _char.end()) {
                return iter->second;
            }

            return NULL;
        }

    private:
        // 享元实例表
        std::map<char, Character*> _char;
};

int main()
{

    CharacterFactory *factory = new CharacterFactory;

    Character *ch1 = factory->GetCharacter('A');
    ch1->Display();

    Character *ch2 = factory->GetCharacter('B');
    ch2->SetSize(500, 300);
    ch2->Display();

    return 0;
}
