# struct union enum
## C++中可以省略关键字
```c++
    struct Student { ... };
    struct Student s1 = { ... };  // C
    Student s2 = { ... };         // C++
    
    union Array { ... };
    union Array a1;      // C
    Array a2;            // C++
    
    enum COLOR { ... };
    enum COLOR c1;       // C
    COLOR c2;            // C++
```
## C++的结构体可以定义函数，而且在这些函数中可以直接访问结构体的字段（成员变量）
```c++
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
    
    Student s = {"cdd", 30, 89},*p = &s;
    std::cout << s.name << ' ' << s.age << ' ' << s.score << std::endl;
    std::cout << p->name << ' ' << p->age << ' ' << p->score << std::endl;
    s.who();
    p->who();
```
## C++中可以定义匿名联合（是一种使不同变量共用内存的方法）
```c++
    union {
        int n;
        char c[4];
    };
    
    n = 0x12345678;
    
    for (char i : c) {
        printf("%#x ", i);  // 0x78 0x56 0x34 0x12
    }
    std::cout << std::endl;
```
## C++中的枚举不能和整型通用
```c++
    enum Color { RED, GREEN, BLUE };
    
    void foo(int n) { }
    void bar(Color c) { }
    
    std::cout << RED << ' ' << GREEN << ' ' << BLUE << std::endl; // 0 1 2
    Color color = RED;
    Color color = 0; // ERROR
    int n = color;   // OK
    
    foo(RED); // OK
    bar(0);   // ERROR
```
#### 为什么可以将Color赋值给int，而反过来将int赋值给Color不行呢？  
因为C++认为枚举是一个有限整数集（枚举的值域也是类型的一部分）。int的值域比Color大得多，当把一个小值域的值赋给一个大范围的值域，编译器认
为是安全的。但是反过来就不行，有可能得到是值域以外的值，编译器认为这样是有风险的。

