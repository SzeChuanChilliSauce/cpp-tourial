# 显示（强制）类型转换
## 1.C风格的显示类型转换
(目标类型)源类型变量
```c++
    int i = 1234;
    // 不对源类型变量做任何修改，而是产生一个目标类型的临时变量
    char c = (char)i; 
```
## 2.C++风格的显示类型转换
### （1）静态类型转换
static_cast<目标类型>(源类型变量)  
编译器会对源类型和目标类型做相容性检查，检查不通过报错。
* A.如果在源和目标之间，至少存在一个方向可以做隐式类型转换，那么这来那两个类型就是相容类型。
```c++
    short x = 10;
    void* v = &x;
    short* p = static_cast<short*>(v);
    int* q = static_cast<int*>(v); // ERROR
```
* B.如果从源类型到目标类型存在自定义的转换规则（类型转换构造函数、类型转换操作符函数），那么它们也可以成为相容类型。
### （2）动态类型转换
dynamic_cast<目标类型>(源类型变量)  
用于具有多态性的父子类型的指针或引用
### （3）去常类型转换
const_cast<目标类型>(源类型变量)   
取出指针或引用的常属性
```c++
    int x = 10;
    const int* cp = &x;
    int* p = const_cast<int*>(cp);
    
    const int y = 100;
    // const volatile int y = 100;
    int& r = const_cast<int&>(y);
    r = 200;
    std::cout << &r << ' ' << &y << std::endl;
    std::cout << y << std::endl; // 100
    // 为什么y不是200？
    // 编译器常量优化
    // 访问字面值的速度比访问内存变量的速度快，因为字面值和代码编译到一起的，放在代码段。访问变量需要到堆或栈中读取，因此慢。
    // 编译器看到某个变量带有常属性时，就会把所有用到该变量的地方用它的字面值替换。
    // 编译器优化为：std::cout << 100 << std::endl;，根本没有用y

    // 加volatile避免常量优化
    // volatile表示变量有挥发性，即变量的值可以在编译器所见范围之外被修改
```
### （4）重解释类型转换
reinterpret_cast<目标类型>(源类型变量)  
转换任意类型的指针或引用；在任意类型的指针和整型之间转换。
```c++
    char c[] = {0x78, 0x56, 0x34, 0x12};
    int* n = reinterpret_cast<int*>(c);
    std::cout << std::hex << std::showbase << *n << std::endl; // 0x12345678

    double x = 3.14;
    double* p = &x;
    std::cout  << p << std::endl;

    // 64位机，指针是8字节，int是4字节
    // 丢失精度，加-fpermissive才能编译通过
    // int m = reinterpret_cast<int>(p); 
    // std::cout  << *(double*)m << std::endl; // 结果不正确
    long m = reinterpret_cast<long>(p); 
    std::cout  << *(double*)m << std::endl;    // 用8字节的类型结果才正确

    char* pc = reinterpret_cast<char*>(m);
    p = reinterpret_cast<double*>(pc);
    std::cout << *p << std::endl;
```










