#include <iostream>

//extern "C" {
//#include "add.h"
//}

extern "C" int add(int ,int);

int main() {

    std::cout << add(100, 200) << std::endl;

    return 0;
}
