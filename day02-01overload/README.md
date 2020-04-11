# 重载（overload）
C语言中在同一作用域中不能定义同名的函数，但在C++中可以。   
C++如何区分呢？虽然函数名相同，但是参数表不同。
#### 同一个作用域中，函数名相同，参数表（类型、个数、顺序）不同的函数，构成重载。
#### 调用函数时，根据实参与形参的类型匹配情况，选择一个确定的重载版本，这个过程成为重载解析。
```c++
    void foo()                { std::cout << 1 << std::endl; }  
    void foo(int n)           { std::cout << 2 << std::endl; }   
    void foo(int* n)          { std::cout << 3 << std::endl; }  
    void foo(int n, double d) { std::cout << 4 << std::endl; }
    void foo(double d, int n) { std::cout << 5 << std::endl; }

    // void foo(double d, int n) { } // ERROR
    // int foo() { }                 // ERROR

    foo();            // 1
    foo(1);           // 2
    int n = 100;      
    foo(&n);          // 3
    foo(100, 1.23);   // 4
    foo(3.15, 200);   // 5
```
#### 问题：如下函数构成重载吗？如果不是那么是什么关系？
#### 不构成重载关系，因为不在同一作用域（同一作用域是构成重载的必要条件）。它们是隐藏关系。
```c++
    void foo() { std::cout << 1 << std::endl; }
    
    namespace s1 {
        void foo(int n) { std::cout << 2 << std::endl; }
        
        namespace s2 {
            void foo(int a,int b) { std::cout << 3 << std::endl; }
            
            void bar() { 
                foo(10, 20);  
                s1::foo(10);  
                ::foo();      
            }           
        }
    }  
```
#### 如下两个函数能构成重载关系吗？不能。
#### 如果我想让它们构成重载，有什么办法呢？
```c++
    namespace nsa {
        void fun(int x) { std::cout << 'a' << std::endl; }
    }

    namespace nsb {
        void fun(double x) { std::cout << 'b' << std::endl; }   
    }

    // 名字空间指令，以下对两个函数都可见，构成重载
    using namespace nsa;
    using namespace nsb;
    foo(100);   // a
    foo(1.23);  // b

    // 名字空间声明，内层作用域隐藏外层作用域
    using nsa::fun;
    fun(100);   // a
    fun(1.23);  // a

    using nsb::fun;
    fun(100);   // a
    fun(1.23);  // b
```
#### 注意：重载不完全由函数在哪定义决定，也和调用有关。因为重载解析不是发生在定义函数时，而是发生在调用函数时。
## 重载匹配规则：安全第一，最小工作量
#### 优先级：完全匹配 -> 常量转换 -> 升级转换 -> 标准转化 -> 可变常参数
```c++
    void funa(char* p)       { std::cout << 1 << std::endl; } 
    void funa(const char* p) { std::cout << 2 << std::endl; }
    char* p;
    // 完全匹配优于常量转换
    funa(p);    // 1  

    void funb(const char* p, char c) { std::cout << 1 << std::endl; }
    void funb(char* p, int n)        { std::cout << 2 << std::endl; }
    char c;
    // 常量转换好于升级转换
    // 常量转换不需要做额外的工作，升级转换要做初始化工作等
    funb(p, c); // 1  

    void func(char c) { std::cout << 1 << std::endl; }
    void func(int n)  { std::cout << 2 << std::endl; }
    void func(long l) { std::cout << 3 << std::endl; }
    short h;
    // 升级转换优于标准转换，但是没有必要过分升级
    func(h); // 2
    
    void fund(int n, void* p) { std::cout << 1 << std::endl; }
    void fund(double d, ...)  { std::cout << 2 << std::endl; }
    double d;
    void* pv;
    // 可变长参数表匹配度最低
    fund(d, pv); // 1
```
