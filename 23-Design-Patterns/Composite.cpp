#include <iostream>
#include <string>
#include <vector>

// Component
class Menu {
    public:
        virtual ~Menu(){}

        virtual void Add(Menu*);
        virtual void Remove(Menu*);
        virtual Menu* GetChild(int);
        virtual void Display() = 0;

    protected:
        Menu();
        Menu(const std::string& );
        std::string _name;
};

Menu::Menu()
{
}

Menu::Menu(const std::string& name) 
            : _name(name) 
{
}

void Menu::Add(Menu* menu)
{
}

void Menu::Remove(Menu* menu)
{
}

Menu* Menu::GetChild(int idx)
{
    return NULL;
}

////////////////////////////////////
// Leaf
class SubMenu : public Menu {
    public:
        SubMenu();
        SubMenu(const std::string& );
        virtual ~SubMenu();


        void Display();
};

SubMenu::SubMenu()
{
}

SubMenu::SubMenu(const std::string& name) 
        : Menu(name)
{
}

SubMenu::~SubMenu()
{
}

void SubMenu::Display()
{
    std::cout << _name << std::endl;
}


////////////////////////////////////
// Composite
class CompositeMenu : public Menu {
    public:
        CompositeMenu();
        CompositeMenu(const std::string& name);
        virtual ~CompositeMenu();

        void Add(Menu*);
        void Remove(Menu*);
        Menu* GetChild(int);
        void Display();

    private:
        std::vector<Menu*> _menu;
};

CompositeMenu::CompositeMenu()
{
}

CompositeMenu::CompositeMenu(const std::string& name)
            : Menu(name)
{
}

CompositeMenu::~CompositeMenu()
{
}

void CompositeMenu::Add(Menu* menu)
{
    _menu.push_back(menu);
}

void CompositeMenu::Remove(Menu* menu)
{
    std::vector<Menu*>::iterator iter = _menu.begin();
    for (; iter != _menu.end(); ++iter) {
        if ((*iter) == menu) {
            _menu.erase(iter);
            break;
        }
    }
}

Menu* CompositeMenu::GetChild(int idx)
{
    return _menu[idx];
}

void CompositeMenu::Display()
{
    std::cout << "+" << _name << std::endl;
    std::vector<Menu*>::iterator iter = _menu.begin();
    for (; iter != _menu.end(); ++iter) {
        std::cout << "|-";
        (*iter)->Display();
    }
}

////////////////////////////////////

int main()
{
    Menu* menu = new CompositeMenu("国内新闻");
    menu->Add(new SubMenu("时事新闻"));
    menu->Add(new SubMenu("社会新闻"));
    menu->Display();

    return 0;
}
