# 引用
## 1.引用即别名
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
## 2.引用必须初始化
```c++
    int a = 10;
    int b;
    int* p = NULL;
    int* q;
    // int&; // ERROR
    int& r = a;
```
## 3.无法定义一个什么都不引用的引用。
```c++
    int* p = NULL;
    // int& r = NULL; // ERROR
    
    int& g = *new int(100);
    std::cout << g << std::endl;
    delete &g;
    // 此时g是野引用
```
## 4.引用已经初始化便不能再引用其他对象。
```c++
    int a = 100;
    int& r = a;
    int b = 200;
    r = b; // 将b的值赋给a
```