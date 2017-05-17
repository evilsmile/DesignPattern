#include <iostream>
#include <string>

class SiegeTank;
class ISiegeTankState {
    public:
        virtual void move(int x, int y) = 0;
        virtual void attack() = 0;
};

class SiegeState : public ISiegeTankState {
    public:
        SiegeState(SiegeTank* tank) : _tank(tank) {}

        virtual void move(int x, int y) {
            std::cout << "Can't move in siege mode." << std::endl;
        }

        virtual void attack() {
            std::cout << "Attacking for 40" << std::endl;
        }

    private:
        SiegeTank* _tank;
};

class TankState : public ISiegeTankState {
    public:
        TankState(SiegeTank* tank) : _tank(tank) {}

        virtual void move(int x, int y) {
            std::cout << "Move to (" << x << ", " << y << ")" << std::endl;
        }

        virtual void attack() {
            std::cout << "Attacking for 20" << std::endl;
        }

    private:
        SiegeTank* _tank;
};

class SiegeTank {
    public:
        SiegeTank() {
            _tankState = new TankState(this);
            _siegeState = new SiegeState(this);
            _siegeTankState = _tankState;
        }

        void enterTankMode() {
            _siegeTankState = _tankState;
            std::cout << "Switch to tank mode " << std::endl;
        }

        void enterSiegeMode() {
            _siegeTankState = _siegeState;
            std::cout << "Switch to siege mode " << std::endl;
        }

        // 根据不同的状态去攻击
        void attack() {
            _siegeTankState->attack();
        }

        void move(int x, int y) {
            _siegeTankState->move(x, y);
        }

    private:
        void setState(ISiegeTankState* siegeTankMode) {
            _siegeTankState = siegeTankMode;
        }

    private:
        TankState* _tankState;
        SiegeState* _siegeState;
        ISiegeTankState* _siegeTankState;
};

int main()
{
    SiegeTank tank;
    tank.enterTankMode();
    tank.attack();
    tank.move(1, 20);

    tank.enterSiegeMode();
    tank.attack();
    tank.move(2, 33);

    tank.enterTankMode();
    tank.attack();
    tank.move(3, 32);

    return 0;
}
