//
// Created by chensq on 4/18/20.
//

#ifndef DAY03_03OOP_STUDENT_H
#define DAY03_03OOP_STUDENT_H
#include <iostream>
// 声明学生类
class Student2 {
public:
    Student2(const std::string& name, int age, int no);
    void eat(const std::string& food);
    void sleep(int time);
    void learn(const std::string& course);
    void setName(const std::string& name);
    void setAge(int age);
    void setNo(int no);
private:
    std::string _name;
    int _age;
    int _no;
};


#endif //DAY03_03OOP_STUDENT_H
