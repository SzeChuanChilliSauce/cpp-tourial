#include <iostream>


// 变量就是一段内存空间(栈或堆)的别名,用来存储数据.
int main() {
    // int占4字节,返回约为-2billion ~ 2billion
    int variable = 8;
    std::cout << variable << std::endl; // 读取变量的值打印
    // 改变变量的值(存储其他值)
    variable = 20;
    std::cout << variable << std::endl;
    unsigned int v2 = 12; // 无符号整型

    // 基本类型:
    // char      , unsigned char       1字节
    // short     , unsigned char       2字节
    // int       , unsigned int        4字节
    // long      , unsigned long       4字节(通常),具体取决于编译器
    // long long , unsigned long long  8字节(通常),具体取决于编译器
    // float     ,                     4字节
    // double    ,                     8字节
    // bool      ,                     1字节,0-false,其他-true
    // 其他:
    // 指针 数组 结构体 类

    float f = 5.5f;
    std::cout << f << std::endl;
    double f2 = 5.2;
    std::cout << f2 << std::endl;

    bool bb = false;
    std::cout << bb << std::endl; // 0
    bb = -1;
    std::cout << bb << std::endl; // 1

    // cout根据变量类型打印
    char a = 'A';
    std::cout << a << std::endl; // 'A'
    a = 65;
    std::cout << a << std::endl; // 'A'
    short b = 65;
    std::cout << b << std::endl; // 65
    b = 'A';
    std::cout << b << std::endl; // 65

    // 变量的类型是创建变量时分配多少内存
    std::cout << "[bool]=" << sizeof(bool) << std::endl; // 1
    std::cout << "[char]=" << sizeof(char) << std::endl; // 1
    std::cout << "[short]=" << sizeof(short) << std::endl; // 2
    std::cout << "[int]=" << sizeof(int) << std::endl; // 4
    std::cout << "[long]=" << sizeof(long) << std::endl; // 8
    std::cout << "[longlong]=" << sizeof(long long) << std::endl; // 8
    std::cout << "[float]=" << sizeof(float) << std::endl; //4
    std::cout << "[double]=" << sizeof(double) << std::endl; // 8
    // 指针类型是4字节(通常),具体与机器相关
    std::cout << "[int*]=" << sizeof(int*) << std::endl; // 8
    // 引用的大和对应类型的大小相同
    std::cout << "[int&]=" << sizeof(int&) << std::endl; // 4

    return 0;
}
