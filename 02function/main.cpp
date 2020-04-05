#include <iostream>

int Multiply(int a, int b) {
    return a * b;
}

void MultiplyAndLog(int a, int b) {
    int res = Multiply(a, b);
    std::cout << res << std::endl;
}

// 只有main函数在有返回值时可以不用显示返回一个值
int main() {
    MultiplyAndLog(3,2);

    // return 0;
}
