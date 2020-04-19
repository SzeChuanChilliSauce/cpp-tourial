#include <iostream>
#include <cstring>

class Student {
public:
    // Student(Student* this, const char* name, int age);
    Student(const char* name, int age) : _name{ 0 }, _age(age) {
        std::cout << "构造函数this: " << this << std::endl;
        strcpy(_name, name);
    }

    // 编译器编译为
    // void show(Student* this) {
    //  std::cout << this->_name << ", " << this->_age << std::endl;
    // }
    void show() {
        std::cout << "show函数this: " << this << std::endl;
        std::cout << _name << ", " << _age << std::endl;
    }


private:
    char _name[256];
    int _age;
};

int main() {
    // s1.Student(&s1, "令狐冲", 25);
    Student s1("令狐冲", 25); // s1在栈中
    std::cout << "&s1: " << &s1 << std::endl;
    s1.show(); // s1.show(&s1);

    // 成员函数不在对象中，而是在代码区
    std::cout << sizeof(s1) << std::endl; // 260

    Student s2("任盈盈", 21);
    std::cout << "&s2: " << &s2 << std::endl;
    s2.show(); // s2.show(&s2);

    // show在代码区，编译后二进制指令也只有一份，为什么s1、s2都打印各自的信息，不会打印错误或混淆呢？是怎么区分的呢？
    // 因为编译器编译后传了参数，参数就是调用者

    return 0;
}
