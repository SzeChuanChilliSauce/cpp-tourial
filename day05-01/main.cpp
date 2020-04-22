#include <iostream>
#include <cstring>

class Student{
public:
    Student(const std::string name = "", int age = 0) : _name(name), _age(age) {}
    void show() {
        std::cout << _name  << ", " << _age << std::endl;
    }
    double _score; // 8字节
    std::string _name; // 32字节
    int _age; // 4字节
    double _height;
};

int main() {
    std::string Student::*pname = &Student::_name;
    int Student::*page = &Student::_age;
    double Student::*pheight = &Student::_height;

    Student s("令狐冲", 19), *p = &s;
    // .* 成员指针解引用操作符
    std::cout << s.*pname << std::endl;
    std::cout << s.*page << std::endl;
    // ->* 间接成员指针解引用操作符
    std::cout << p->*pname << std::endl;
    std::cout << p->*page << std::endl;

    long i = 0, j = 0, k = 0;
    memcpy(&i, &pname, 8);
    std::cout << i << std::endl; // 8

    memcpy(&j, &page, 8);
    std::cout << j << std::endl; // 40

    memcpy(&k, &pheight, 8);
    std::cout << k << std::endl; // 48

    return 0;
}
