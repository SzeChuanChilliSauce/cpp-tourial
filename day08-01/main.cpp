#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cerrno>

class A {
public:
    A(size_t size) : _pData(new int[size]) {
        FILE* fp = fopen("none", "r");
        if (!fp) {
            // throw之前释放资源
            if (_pData) {
                std::cout << "释放内存" << std::endl;
                delete [] _pData;
            }
            // 抛出异常
            throw -1;
        }
        fclose(fp);
    }
    ~A() {
        if (_pData) {
            std::cout << "释放内存" << std::endl;
            delete [] _pData;
        }
    }

private:
    int* _pData;
};

int main() {
    try {
        A a(1024);
    }
    catch (int& ex) {
        std::cout << ex << std::endl;
    }
    return 0;
}
