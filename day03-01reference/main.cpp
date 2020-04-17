#include <iostream>
#include <cmath>

struct A {
    int data;
    int& foo() { return data; }
};

int& bar(int& a) { return a; }

int& hum() {
    int n = 123;
    return n;
}


int main() {
    A a = { 100 };
    std::cout << a.data << std::endl; // 100
    a.foo() = 200;
    std::cout << a.data << std::endl; // 200

    int x;
    bar(x) = 1000;
    std::cout << x << std::endl;

//    int& r = hum();
//    std::cout << r << std::endl;


    return 0;
}
