#include <string>
#include <iostream>
#include <cstring>

class Resume {
    public:
        Resume() {}
        virtual ~Resume() {}
        virtual Resume* Clone() { return NULL; }
        virtual void Set(char *n) {}
        virtual void Show() {}
    protected:
        char *name;
};

class ResumeA : public Resume {
    public:
        ResumeA(const char *str);
        ResumeA(const ResumeA &r);
        ~ResumeA();
        ResumeA* Clone();
        void Show();
};

ResumeA::ResumeA(const char* str) 
{
    if (str == NULL) {
        name = new char[1];
        name[0] = '\0';
    } else {
        name = new char[strlen(str) + 1];
        strncpy(name, str, strlen(str));
    }
}

ResumeA::~ResumeA() 
{
    if (name != NULL) {
        delete name;
    }
}

ResumeA::ResumeA(const ResumeA& r) 
{
    name = new char[strlen(r.name) + 1];
    strncpy(name, r.name, strlen(r.name));
}

ResumeA* ResumeA::Clone() 
{
    return new ResumeA(*this);
}

void ResumeA::Show() {
    std::cout << "ResumeA name: " << name << std::endl;
}

int main()
{
    Resume *r1 = new ResumeA("A");
    Resume *r2 = r1->Clone();
    Resume *r3 = r1->Clone();
    r1->Show();
    r2->Show();
    r3->Show();

    delete r1;
    delete r2;
    delete r3;

    r1 = r2 = r3 = NULL;

    return 0;
}
