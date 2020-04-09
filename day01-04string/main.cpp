#include <iostream>
#include <cstdio>

int main() {
    std::string s1 = "hello";
    std::cout << s1 << std::endl;

    s1 += " ";
    s1 += "world";
    std::cout << s1 << std::endl;

    s1 = "cdd";
    std::cout << s1 << std::endl;
    std::string s2 = "chensq";

    std::cout << (s1 > s2) << std::endl;
    std::cout << s1.length() << std::endl;

    std::string s3 = "./logs.txt";
    FILE* fp = fopen(s3.c_str(), "r");
    s3[2] = 'L';
    std::cout << s3 << std::endl;

    // bool
    bool b = true;
    std::cout << b << std::endl;                    // 1
    std::cout << std::boolalpha <<  b << std::endl; // true
    b = !b;
    std::cout << b << std::endl;                    // 0
    std::cout << std::boolalpha <<  b << std::endl; // false

    std::cout << sizeof(bool) << std::endl; // 1

    b = 1000;
    std::cout << b << std::endl; // true
    b = 3.14;
    std::cout << b << std::endl; // true
    b = "hello world";
    std::cout << b << std::endl; // true
    b = NULL;
    std::cout << b << std::endl; // false

    return 0;
}
