//
// Created by chensq on 4/8/20.
//
#include <iostream>

namespace ns {
    struct type {
        int x;
        char y[256];
    };
}

namespace nu {
    int var = 5678;
    int x = 1234;
    void fun() {
        std::cout << "nu::fun()" << std::endl;
    }
}

int y = 7777;
namespace nv {
    int y = 8888;

    void fun() {
        // 使用无名名字空间中的y
        // 不加::会使用nv::y（小作用域隐藏大作用域）
        std::cout << ::y << std::endl;
    }
}