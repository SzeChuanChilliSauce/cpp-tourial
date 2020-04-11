#include <iostream>

void funa(char* p)       { std::cout << 1 << std::endl; }
void funa(const char* p) { std::cout << 2 << std::endl; }

void funb(const char* p, char c) { std::cout << 1 << std::endl; }
void funb(char* p, int n)        { std::cout << 2 << std::endl; }

void func(char c) { std::cout << 1 << std::endl; }
void func(int n)  { std::cout << 2 << std::endl; }
void func(long l) { std::cout << 3 << std::endl; }

void fund(int n, void* p) { std::cout << 1 << std::endl; }
void fund(double d, ...)  { std::cout << 2 << std::endl; }

int main() {
    char* p;
    funa(p);

    char c;
    funb(p, c);

    short h;
    func(h);

    double d;
    void* pv;
    fund(d, pv);


    return 0;
}
