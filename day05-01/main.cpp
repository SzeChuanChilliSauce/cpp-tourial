#include <iostream>
#include <cstring>
#include <cmath>


class A {
public:
    int& operator[](int i) {
        return _array[i];
    }

    const int& operator[](int i) const {
        // 显式去常，隐式加常
        return const_cast<A&>(*this)[i];
    }

private:
    int _array[10];
};

class B{
public:
    int operator()(int x, int y) {
        return x+y;
    }
private:
};


class Integer {
public:
    Integer(int i = 0): _i(i) {}

    // 类型转换操作符函数
    operator int() const {
        return _i;
    }

    int _i;
};


int main() {
    A a;
    a[0] = 100;
    a[1] = 101;
    std::cout << a[0] << " " << a[1]<< std::endl;
    const A& ra = a;
    std::cout << ra[0] << " " << ra[1]<< std::endl;

    B b;
    std::cout << b(12, 34) << std::endl;

    Integer x;
    x = 123;
    std::cout << x._i << std::endl;

    int y;
    y = x;
    std::cout << y << std::endl;

    return 0;
}
