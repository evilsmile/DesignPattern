#include <string>
#include <iostream>

class CaffeineBeverage {
    public:
        void PrepareRecipe() {
            BoilWater();
            Brew();
            PourInCup();
            AddCondiments();
        }
        void BoilWater() {
            std::cout << "boil water" << std::endl;
        }
        virtual void Brew() = 0;

        void PourInCup() {
            std::cout << "pour coffee to cup" << std::endl;
        }

        virtual void AddCondiments() = 0;
};

class Coffee : public CaffeineBeverage {
    public:
        void Brew() {
            std::cout << "brew caffeine use boiling water" << std::endl;
        }

        void AddCondiments() {
            std::cout << "add sugar and milk" << std::endl;
        }
};


int main()
{
    Coffee c;
    c.PrepareRecipe();

    return 0;
}
