#include <iostream>
#include <string>
#include <memory>

class Tank {
    public:
        virtual void shot() = 0;
        virtual void run() = 0;

        virtual ~Tank() {
            std::cout << "Tank destroyed" << std::endl;
        }
};

class T50 : public Tank {
    public:
        void shot() {
            std::cout << "shot in 50 yards" << std::endl;
        }
        void run() {
            std::cout << "run in 50 yards" << std::endl;
        }
    
        virtual ~T50() {
            std::cout << "T50 destroyed" << std::endl;
        }
};

class T75 : public Tank {
    public:
        void shot() {
            std::cout << "shot in 75 yards" << std::endl;
        }
        void run() {
            std::cout << "run in 75 yards" << std::endl;
        }
    
        virtual ~T75() {
            std::cout << "T75 destroyed" << std::endl;
        }
};

class Decorator : public Tank {
    public:
        Decorator(Tank* tank) : _tank(tank) {}
        virtual ~Decorator() {
            std::cout << "tank decorator destroyed" << std::endl;
        }

        void shot() {
            _tank->shot();
        }
        void run() {
            _tank->run();
        }

    protected:
        Tank* _tank;
};

class InfraredDecorator : public Decorator {
    public:
        InfraredDecorator(Tank* tank) : Decorator(tank) {}
        virtual ~InfraredDecorator() {
            std::cout << "infrared decorator destroyed" << std::endl;
        }

        void set_infared(const std::string& infrared) {
            this->_infrared = infrared;
        }

        std::string get_infrared() const {
            return _infrared;
        }

        void run() {
            _tank->run();
            set_infared("+Infrared");
            std::cout << get_infrared() << std::endl;
        }

        void shot() {
            _tank->shot();
        }

    private:
        std::string _infrared;
};

class AmphibianDecorator : public Decorator {
    public:
        AmphibianDecorator(Tank* tank) : Decorator(tank) {}

        ~AmphibianDecorator() {
            std::cout << "amphibian decorator destroyed" << std::endl;
        }

        void set_amphibian(const std::string& hibian) {
            this->_amphibian = hibian;
        }

        std::string get_amphibian() const {
            return _amphibian;
        }

        void run() {
            _tank->run();
            set_amphibian("+amphibian");
            std::cout << get_amphibian() << std::endl;
        }

        void shot() {
            _tank->shot();
        }
    private:
        std::string _amphibian;
};

int main()
{

    Tank* tank50 = new T50;
    Tank* infr_tank50 = new InfraredDecorator(tank50);
    infr_tank50->shot();
    infr_tank50->run();

    Tank* tank70 = new T75;
    tank70->run();
    Tank* infra_tank70 = new InfraredDecorator(tank70);
    Tank* infra_amp_tank70 = new AmphibianDecorator(infra_tank70);
    infra_amp_tank70->shot();
    infra_amp_tank70->run();

    return 0;
}
