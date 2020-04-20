#include <iostream>
#include <cstring>

// 类的短式声明
class Student;

class Teacher {
public:
    void teach(Student* s);
    void reply(const char* answer) { _answer = answer; }
private:
    std::string _answer;
};

class Student {
public:
    void acceptQuestion(const char* question, Teacher* t) {
        std::cout << "老师提问: " << question << std::endl;
        t->reply("我不知道");
    }
};

void Teacher::teach(Student* s) {
    s->acceptQuestion("什么是this指针?", this);
    std::cout << "学生回答: "  << _answer << std::endl;
}

int main() {
    Teacher t;
    Student s;
    t.teach(&s);

    return 0;
}
