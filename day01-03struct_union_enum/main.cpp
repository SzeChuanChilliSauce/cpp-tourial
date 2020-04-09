#include <iostream>
#include <cstdio>
struct Student {
    // 成员变量
    char name[128];
    int age;
    int score;
    // 成员函数
    void who() {
        std::cout << "我是" << name << ",今年" << age << "岁,今天考试" << score << "分." << std::endl;
    }
};

enum Color { RED, GREEN, BLUE };

int main() {
    //
    Student s = {"cdd", 30, 89},*p = &s;
    std::cout << s.name << ' ' << s.age << ' ' << s.score << std::endl;
    std::cout << p->name << ' ' << p->age << ' ' << p->score << std::endl;
    s.who();
    p->who();
    Student t = {"chensq", 22, 45};
    t.who();

    //
    union {
        int n;
        char c[4];
    };

    n = 0x12345678;
    for (char i : c) {
        printf("%#x ", i);
    }
    std::cout << std::endl;

    //
    std::cout << RED << ' ' << GREEN << ' ' << BLUE << std::endl; // 0 1 2
    // Color color = 0; // ERROR
    Color color = RED;
    int m = color;
    std::cout << m << std::endl;



    return 0;
}
