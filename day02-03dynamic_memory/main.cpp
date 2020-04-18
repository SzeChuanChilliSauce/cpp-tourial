#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstring>

int main() {
    int* p = new int; // 用0初始化
    std::cout << *p << std::endl;
    *p = 1234;
    std::cout << *p << std::endl;
    p = new int(5678); // 指定初始值
    std::cout << *p << std::endl;
    delete p;

    int* pa = new int[5]{10, 20, 30, 40, 50}; // 初始化表
    for (int i = 0; i < 5; i++) {
        std::cout << pa[i]<< std::endl;
    }
    delete[] pa;

    int(*prow)[4] = new int[3][4];
    // C++11
    // auto prow = new int[3][4];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            prow[i][j] = (i+1)*10+(j+1);
        }
    }
    delete[] prow;

    int(*ppage)[4][5] = new int[3][4][5];
    // int(*ppage)[4][5] = (int(*)[4][5])malloc(3*4*5);
    delete[] ppage;

    // 抛出异常 std::bad_alloc
    // p = new int[0xFFFFFFFF];
    try{
        p = new int[0xFFFFFFFF];
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
        perror("new");
    }

    // 定位分配
    char* pool = new char[1024];            // 分配内存池
    int* pn = new(pool) int(123);           // 再分一个int的内存
    char* ps = new(pool+4) char[15];        // 再分15个char的内存
    strcpy(ps, "Hello, World!");
    double* pd = new(pool+19) double(3.14); // 再分一个double的内存
    std::cout << *pn << ' ' << ps << ' '  << *pd << std::endl;
    delete[] pool;


    return 0;
}
