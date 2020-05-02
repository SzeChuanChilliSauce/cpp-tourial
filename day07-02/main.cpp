#include <iostream>
#include <typeinfo>
#include <cstring>


class A {
public:
    A() {
        std::cout << "A构造" << std::endl;
    }
    virtual ~A() {
        std::cout << "A析构" << std::endl;
    }
};

class B : public A {
public:
    B() {
        std::cout << "B构造" << std::endl;
    }
    ~B() {
        std::cout << "B析构" << std::endl;
    }
};

int main() {
    // B* p = new B;
    A* p = new B;
    delete p;
    return 0;
}