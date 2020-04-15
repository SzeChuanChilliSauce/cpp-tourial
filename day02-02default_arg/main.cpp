#include <iostream>

int add(int a, int, int c) {
    return a+c;
}

// 升级版本
void foo(int) {}

int main() {
    std::cout << add(100, 200, 300) << std::endl;

    return 0;
}
