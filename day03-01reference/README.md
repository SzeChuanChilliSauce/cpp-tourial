# 引用
## 1.引用的基本特性
### （1）引用即别名。
声明一个标识符为引用，即表示该标识符可作为另一个又名或无名对象的别名。  
常引用的目标不可修改，只能读取。    
C++中，无名对象（字面值常量、临时变量）都被视作右值，只能通过常左值引用或右值引用引用。
```c++
    int a = 10;
    int& b = a; // b是a的一个引用，即b是a的一个别名
    ++b;
    std::cout << a << std::endl; // 11
    std::cout << &a << ' ' << &b << std::endl;

    int& c = b; // c是a的另一个引用
    ++c;
    std::cout << a << std::endl; // 12

    const int& d = a; // 不能通过d来改变a
    std::cout << d << ' ' << &d << std::endl;
    // d = 20; // ERROR
    a = 20;
    b++;
    --c;

    // int& e = 10; // 左值引用不能接受右值
    int x = 100, y = 200;
    // 如果用常左值引用接受一个右值，那么右值的生命期会延长至其左值引用的生命周期
    const int& e = x + y;
    std::cout << e << std::endl;
    const int& f = e;
    std::cout << f << std::endl;
``` 
注意：  
* 临时变量的生命期是语句级的；有名变量的生命周期是作用域级。  
* 右值：临时变量（将亡右值）、字面量（纯右值）都是右值。  
### （2）引用必须初始化。
```c++
    int a = 10;
    int b;
    int* p = NULL;
    int* q;
    // int&; // ERROR
    int& r = a;
```
### （3）无法定义一个什么都不引用的引用。
```c++
    int* p = NULL;
    // int& r = NULL; // ERROR
    
    int& g = *new int(100);
    std::cout << g << std::endl;
    delete &g;
    // 此时g是野引用
```
### （4）引用已经初始化便不能再引用其他对象。
```c++
    int a = 100;
    int& r = a;
    int b = 200;
    r = b; // 将b的值赋给a
```
## 2.引用型参数
* 函数的形参是实参的别名。  
可以将函数的形参声明为引用形式，该形参在参数的传递过程中由对应的实参初始化，并成为该实参的别名。
* 在函数中修改实参的值。  
通过引用型形参，可以在函数体内部修改调用者实参的值，成为除返回值和指针以外，第三种由函数内部向函数外部输出数据的途径。
* 避免对象复制的开销。  
通过引用传递参数，形参只是实参的别名而非副本，这样就避免了从实参到形参的对象复制。这对具有复杂数据结构的参数而言可以提高其传参的性能。  
如果函数只是通过读取引用类型参数的目标对象，那么最好通过常引用接受实参，防止在函数中意外地修改实参变量的值。
```c++
    // 传递实参的拷贝
    void foo(int a) {
        std::cout << "foo: " << &a << std::endl;
        ++a;
        std::cout << "a = " << a << std::endl;
    }
    
    // 传递实参
    void bar(int& a) {
        std::cout << "bar: " << &a << std::endl;
        ++a;
        std::cout << "a = " << a << std::endl;
    }

    int x = 123;
    std::cout << "main: " << &x << std::endl;

    foo(x);
    std::cout <<"x = " << x << std::endl;

    bar(x);
    std::cout <<"x = " << x << std::endl;

    double rect(double w, double h, double* c, double& s) {
        *c = (w+h)*2; // 周长
        s = w*h; // 面积
        return sqrt(w*w+h*h); // 对角线长度
    }

    // 引用向外传值
    double w = 3, h = 4, c, s, t;
    t = rect(w, h, &c, s)

    struct Student {
        char name[64];
        char addr[256];
        char email[128];
    };
    
    // 实参复制，开销比较大
    // void insert(Student s) {}

    // 不用复制，但是存在被修改的风险
    // void insert(Student& s) {}

    // 常引用，防止意外修改
    void insert(const Student& s) {}
```
## 3.引用型返回值
* 返回左值。
* 函数的局部变量只具有函数级甚至语句级的生命周期。  
函数一旦返回，所有的局部变量，即刻销毁。即使通过返回值获得它们的引用，其目标也是为定义的。因此，不要从函数中返回局部变量的引用，返回全局、静态、成员、堆的引用是安全的。
```c++
    struct A {
        int data;
        int& foo() { return data; }
    };
    
    int& bar(int& a) { return a; }
    
    A a = { 100 };
    std::cout << a.data << std::endl; // 100
    a.foo() = 200;
    std::cout << a.data << std::endl; // 200

    int x;
    bar(x) = 1000;
    std::cout << x << std::endl; // 1000

    
    int& hum() {
        int n = 123;
        return n;
    }   
  
    // 返回局部变量的引用
    // int& r = hum(); // compile error
```
## 4.虽然引用是通过指针实现的，但是在高级语言层面引用和指针还是具有若干不同的特性。
* 指针可以不初始化，其目标可以在初始化后随意变更；引用必须初始化，且一旦初始化，就无法变更其目标。
* 可以定义空指针，即什么也不指向的指针；但无法定义空引用，引用必须有所引用，否则将失去其意义。
* 可以定义指向指针的指针，但无法定义引用引用的引用。
* 可以定义引用指针的引用，但无法定义指向引用的指针。
* 可以定义存放指针的数组，但无法定义存放引用的数组。

## 5.函数指针和函数引用
```c++
    int add(int x, int y) {
     return x + y;
    }
    
    // 古典写法
    int(*pfunc)(int, int) = &add;
    std::cout << (*pfunc)(100, 200) << std::endl;
    
    // 现代写法
    int(*pfunc2)(int, int) = add;
    std::cout << pfunc2(100, 200) << std::endl;
    
    // 函数引用
    int(&rfunc)(int, int) = add;
    std::cout << rfunc(100, 200) << std::endl;    
```
