#include <iostream>

class A {
public:
    A(int data) : _data(data) {}
protected:
    int _data;
};

// 虚继承
class B : virtual public A {
public:
    B(int data) : A(data) {}
    void set(int data) {
        _data = data;
    }
};

class C : virtual public A {
public:
    C(int data) : A(data) {}
    int get() const {
        return _data;
    }
};

class D : public B, public C {
public:
    // 最终子类需要负责公共基类的初始化，如果指明A的构造方式，A将按缺省构造的方式
    // B、C的构造函数参数可以随意传，真正构造A是在调用A的构造函数时
    // 但是B、C的构造函数不能省，因为B、C中没有缺省构造函数
    D(int data) : B(-9), C(23), A(data) {}
};

int main() {
    D d(1000);
    std::cout << d.get() << std::endl; // 1000
    d.set(2000);
    std::cout << d.get() << std::endl; // 1000
    std::cout << sizeof(D) << std::endl; // 24
    std::cout << sizeof(B) << std::endl; // 16
    std::cout << sizeof(C) << std::endl; // 16
    std::cout << sizeof(A) << std::endl; // 4

    return 0;
}
