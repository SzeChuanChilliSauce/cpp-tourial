#include <iostream>

int main() {
//    int x = 10;
//    const int* cp = &x;
//    // int* p = cp; // ERROR
//    int* p = const_cast<int*>(cp);
//
//    const volatile int y = 100;
//    // int& r = y; // ERROR
//    int& r = const_cast<int&>(y);
//    // y = 200; // ERROR
//    r = 200;
//    std::cout << &r << ' ' << &y << std::endl;
//    std::cout << y << std::endl; // 100


//    char c[] = {0x78, 0x56, 0x34, 0x12};
//    int* n = reinterpret_cast<int*>(c);
//    std::cout << std::hex << std::showbase << *n << std::endl;

    double x = 3.14;
    double* p = &x;
    std::cout  << p << std::endl;

    // 64位机，指针是8字节，int是4字节
    // 丢失精度，加-fpermissive才能编译通过
    // int m = reinterpret_cast<int>(p); // 结果不对
    // std::cout  << *(double*)m << std::endl;
    long m = reinterpret_cast<long>(p); // 用8字节的类型结果就正确
    std::cout  << *(double*)m << std::endl;

    char* pc = reinterpret_cast<char*>(m);
    p = reinterpret_cast<double*>(pc);
    std::cout << *p << std::endl;

    return 0;
}

