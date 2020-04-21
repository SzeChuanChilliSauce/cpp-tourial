#include <iostream>

class A {
public:
    A() {
        std::cout << "A构造" << std::endl;
    }
    ~A() {
        std::cout << "A析构" << std::endl;
    }
};

class B {
private:
    A _a;
};

class C {
public:
    C() : _a(new A) {}
    ~C() {
        delete _a;
    }
private:
    A* _a;
};

int main() {
    B b;
    C c;
    return 0;
}
