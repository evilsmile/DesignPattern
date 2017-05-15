#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

//////////////////////////////////////////////////
class Student {
public:
    Student(std::string name, std::string grade) {
        this->_name = name;
        this->_grade = grade;
    }

    std::string getName() {
        return _name;
    }

    virtual std::string getGrade() {
        return _grade;
    }

protected:
    std::string _name;
    std::string _grade;
};

class LevelStudent : public Student {
public:
    LevelStudent(std::string name, std::string grade) : Student(name, grade) {}

    virtual std::string getGrade() {
        std::string level;
        int n_grade = atoi(_grade.c_str());
        if (n_grade >= 90) {
            level = "优秀";
        } else if (n_grade >= 80 && n_grade < 90) {
            level = "良好";
        } else if (n_grade >= 70 && n_grade < 80) {
            level = "一般";
        } else if (n_grade >= 60 && n_grade < 70) {
            level = "及格";
        } else if (n_grade < 60) {
            level = "不及格";
        }

        return level;
    }
};


class Teacher {
public:
    void init() {
        this->students.push_back(new LevelStudent("张三", "94"));
        this->students.push_back(new LevelStudent("李四", "67"));
        this->students.push_back(new LevelStudent("王五", "45"));
    }
    void destroy() {
        for (std::vector<Student*>::iterator iter = students.begin();
                iter != students.end();
                ++iter) {
            if (*iter) {
                delete *iter;
            }
        }
    }

    std::vector<Student*> students;
};

//////////////////////////////////////////////////
int main()
{
    Teacher* teacher = new Teacher;
    teacher->init();
    for (std::vector<Student*>::iterator iter = teacher->students.begin();
            iter != teacher->students.end();
            ++iter) {
        std::cout << "Name: " << (*iter)->getName() << " grade: " << (*iter)->getGrade() << std::endl;
    }
    teacher->destroy();

    return 0;
}
