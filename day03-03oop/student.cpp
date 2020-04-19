#include "student.h"


Student2::Student2(const std::string& name, int age, int no) {
    std::cout << "-----构造函数-----" << std::endl;
    _name = name;
    _age = age;
    _no = no;
}

void Student2::eat(const std::string& food) {
    std::cout << "我叫" << _name << "，正在吃" << food << std::endl;
}

void Student2::sleep(int time) {
    std::cout << "我今年"  << _age << "岁，睡了" << time << "小时" << std::endl;
}

void Student2::learn(const std::string& course) {
    std::cout << "我的学号是" << _no << "，现在学" << course << "课" <<std::endl;
}

void Student2::setName(const std::string& name) {
    if (name == "sb") {
        std::cout << "不雅姓名"<< std::endl;
    } else {
        _name = name;
    }
}

void Student2::setAge(int age) {
    if (age < 0 || age > 128) {
        std::cout << "非法年龄" << std::endl;
    } else {
        _age = age;
    }
}

void Student2::setNo(int no) {
    if (no < 0 || no > 10000) {
        std::cout << "非法学号" << std::endl;
    } else {
        _no = no;
    }
}