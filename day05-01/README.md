# 一、静态成员
### 1.属于类而非对象。
* 静态成员变量并不包含于对象实例对象中，具有进程级的生命周期。
* 静态成员函数没有this指针，也就没有常属性。
* 静态成员函数只能访问静态成员（变量或函数），非静态的成员函数既可以静态成员也可以访问非静态成员。
### 2.静态成员也受访控属性影响。
### 3.静态成员变量必须在类的外面做定义或初始化，静态成员函数既可以在类的外部也可以在类的内部定义。
```c++
    static int g = 100; // 限制可见性
    
    static void foo() { // 静态全局函数，限制可见性
        static int i = 10; // 静态局部变量，加载进程时初始化
        int j= 10;
        std::cout << ++i << ' ' << ++j << std::endl;
    }
    
    class A {
    public:
        A() : _data(300) {}
        int& data() { return _data; }
        int& s_data() { return _s_data; }
        void bar() {
            std::cout << _data << std::endl;
            std::cout << _s_data << std::endl;
            foo();
        }   
        // 静态成员函数
        static void foo() {
            // std::cout << _data << std::endl; // ERROR
            std::cout << _s_data << sdt::endl;
            // bar(); // ERROR
        }
    private:
        int _data;
        // 静态成员变量
        static int _s_data; 
        // 只有常静态成员变量才能在类的声明部分初始化
        const static int _cs_i = 10;
    };
    
    int A::_s_data = 200; // 定义静态成员变量
    
    int main() {
        foo(); // 11 11
        foo(); // 12 11
        foo(); // 13 11
    
        A a1, a2;
        std::cout << &a1.s_data() << ' ' << &a1.data() << std::endl;
        std::cout << &a2.s_data() << ' ' << &a2.data() << std::endl;
        
        ++a1.s_data();
        std::cout << a2.s_data() << std::endl; // 201
        
        ++a1.data();
        std::cout << a2.data() << std::endl; // 300
        
        return 0;
    }
```
```c++
    class Account {
    public:
        Account(double balance) : _balance(balance) {}
        double settle() {
            _balance *= (1+_s_interest);
        }
        static void set_interest(double interest) {
            _s_interest = interest;
        }
    private:
        double _balance; // 余额
        static double _s_interest; // 利率
    };
    
    double Account::_s_interest = 0.01;
    
    
    int main() {
        Account a1(1000), a2(10000);
        std::cout << a1.settle() << ' ' << a2.settle() << std::endl;
        Account::set_interest(0.05);
        std::cout << a1.settle() << ' ' << a2.settle() << std::endl;
        return 0;
    }
```
### 4.单例模式
```c++
    // 单例模式
    // 饿汉模式
    class A {
    public:
        void work() { std::cout << "work..." << std::endl; }
        static A& get_instance() { return _s_a; }
    private:
        A() {}
        A(const A&) {}
        static A _s_a;
    };
    A A::_s_a;
    
    // 懒汉模式
    class B {
    public:
        void work() { std::cout << "work..." << std::endl; }
        static B& get_instance() {
            if (_ps_b) {
                return *_ps_b;
            }
            _ps_b = new B;
            return *_ps_b;
        }
    private:
        B() {}
        B(const B&) {}
        static B* _ps_b;
    };
    B* B::_ps_b = nullptr;
    
    int main() {
        A& a = A::get_instance();
        a.work();
        B& b = B::get_instance();
        b.work();
        return 0;
    }
```
# 二、成员指针
通过类型的约束，表达指向类特定类型成员的指针。  
 ```c++
    class Student{
    public:
        Student(const std::string name = "", int age = 0) : _name(name), _age(age), _score(0) {}
        void who() const {
            std::cout << _name  << ", " << _age << std::endl;
        }
        double _score; // 8字节
        std::string _name; // 32字节
        int _age; // 4字节
        double _height;
    };
    
    int main() {
        std::string Student::*pname = &Student::_name;
        int Student::*page = &Student::_age;
        double Student::*pheight = &Student::_height;
    
        Student s("令狐冲", 19), *p = &s;
        // .* 成员指针解引用操作符
        std::cout << s.*pname << std::endl;
        std::cout << s.*page << std::endl;
        // ->* 间接成员指针解引用操作符
        std::cout << p->*pname << std::endl;
        std::cout << p->*page << std::endl;
    
        long i = 0;
        memcpy(&i, &pname, 8);
        std::cout << i << std::endl; // 8
        memcpy(&i, &page, 8);
        std::cout << i << std::endl; // 40
        memcpy(&i, &pheight, 8);
        std::cout << i << std::endl; // 48
    
        void(Student::*pwho)() const = &Student::who;
        memcpy(&i, &pwho, 8);
        std::cout << std::hex << std::showbase << i << std::endl;
        (s.*pwho)();
        (p->*pwho)();
    
        return 0;
    }
```
# 三、操作符（运算符）重载
## 1.操作符标记
* 单目操作符：只有一个操作数的操作符。  
++  --  & *  ->  !  ~  ()  -  类型转换
* 双目操作符：有左右两个操作数的操作符。  
算数运算：* / % + -   
关系运算：> >= < <=  
逻辑运算：&& ||   
位运算：& | ^ >>  <<   
赋值和复合赋值: = += -= *= /=  
下标运算：[]
* 三目操作符：包含三个操作数的操作符。  
条件运算： A ? B : C
## 2.操作符函数
* 在特定的条件下，编译器有能力把一个由操作数和操作符组成的表达式，解释成为一个全局或成员函数调用，该全局或成员函数就被称为操作符函数。
* 通过定义操作符函数，可以实现指针自定义类型的运算法则，并使之与内置类型具有一致的语义。
* 双目操作符 。  
L#R -> L.operator#(R)   // 成员，左调右参      
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> ::operator#(L,R) // 全局，左一右二  
（1）运算类：左右操作数都可以为左值或右值，表达式的值必须是右值。  
友元：可以通过friend关键字，把一个函数或类声明为一个类友元。被声明有关的函数或类可以自由访问授权类的任何私有成员。友元声明可以位于授权类的公有、私有、保护任何区域，其效果都一样。
```c++
    class Complex {
    public:
        Complex(int r=0, int i=0) : _real(r), _imaginary(i) {}
    
        void print() const {
            std::cout << _real << "+" << _imaginary << "i" << std::endl;
        }
    
        const Complex add(const Complex& rhs) const {
            return Complex(_real+rhs._real, _imaginary+rhs._imaginary);
        }

        // 第一个const：返回常对象，禁止对返回值赋值
        // 第二个const：支持常对象形式的右操作数
        // 第三个const：支持常对象形式的左操作数
        const Complex operator+(const Complex& rhs) const {
            return Complex(_real+rhs._real, _imaginary+rhs._imaginary);
        }

        // 友元声明在授权类中
        friend const Complex& operator-(const Complex&, const Complex&);
    private:
        int _real;
        int _imaginary;
    };
    
    const Complex& operator-(const Complex& lhs, const Complex& rhs) {
        return Complex(lhs._real-rhs._real, lhs._imaginary-rhs._imaginary);
    }
    
    int main() {
        Complex c1(1,2), c2(3,4), c3(5,6);
        c1.print();
        c2.print();
        c3.print();
    
        // Complex c4 = c1.add(c2).add(c3);
        // Complex c4 = c1.operator+(c2).operator+(c3);
        Complex c4 = c1 + c2 + c3;
        c4.print();
    
        // Complex ::operator-(c4, c1);
        c4 = c4 - c1;
        return 0;
    }
```
（2）赋值类：右操作数可以为左值或右值，但左操作数必须为左值，表达式的值是左值，且为左操作数本身（而非副本）。  
```c++
    class Complex {
    public:
        Complex(int r = 0, int i = 0) : _real(r), _imaginary(i) {}
    
        void print() const {
            std::cout << _real << "+" << _imaginary << "i" << std::endl;
        }
    
        Complex& operator+=(const Complex& rhs) {
            _real += rhs._real;
            _imaginary += rhs._imaginary;
            return *this;
        }
    
        // 友元函数
        friend Complex& operator-=(Complex& lhs, const Complex& rhs) {
            lhs._real -= rhs._real;
            lhs._imaginary -= rhs._imaginary;
            return lhs;
        }
    
    private:
        int _real;
        int _imaginary;
    };
    
    int main() {
        Complex c1(1,2),c2(3,4), c3(5,6);
        c1 += c2;
        c1.print(); // 4+6i
    
        (c1 += c2) += c3;
        c1.print(); // 12+16i
    
        c1 -= c3;
        c1.print(); // 7+10i
    
        return 0;
    }
```
（3）输入输出操作符：左操作数是ostream/istream，右操作数对于输出可以是左值也可以是右值，对于输入只能是左值，表达式的值是左操作数本身。
```c++
    Complex c1;  
    const Complex c2;  
    // 对于输出，右操作数可以是左值也可以是右值  
    cout << c1;   
    cout << c2;  
    // 对于输入，右操作数只能是左值  
    cin >> c1;   
    cin >> c2; // ERROR  
    // 表达式本身就是左操作数
    cout << c1 << c2 << endl; 
    cin >> c1 >> c2; 
```
```c++
    class Complex {
    public:
        Complex(int r = 0, int i = 0) : _real(r), _imaginary(i) {}
    
        void print() const {
            std::cout << _real << "+" << _imaginary << "i" << std::endl;
        }
    
        friend std::ostream& operator<<(std::ostream& lhs, const Complex& rhs) {
            return lhs << rhs._real << '+' << rhs._imaginary << 'i';
        }
    
        friend std::istream& operator >> (std::istream& lhs, Complex& rhs) {
            return lhs >> rhs._real >> rhs._imaginary;
        }
    
    private:
        int _real;
        int _imaginary;
    };
    
    int main() {
        Complex c1, c2;
        // ::operator>>(::operator>>(cin, c1), c2)
        std::cin >> c1 >> c2;
        // ::operator<<(::operator<<(::operator<<(cout, c1), ','), c2);
        std::cout << c1 << ',' << c2;
        std::cout << std::endl;
    
        return 0;
    }
```
（4）单目操作符  
* 运算类：操作数既可以是左值也可以是右值，操作数本身在计算前后不发生变化，表达式的值是右值。  
```c++
    class Complex {
    public:
        Complex(int r = 0, int i = 0) : _real(r), _imaginary(i) {}
    
        void print() const {
            std::cout << _real << "+" << _imaginary << "i" << std::endl;
        }
    
        friend std::ostream& operator<<(std::ostream& lhs, const Complex& rhs) {
            return lhs << rhs._real << '+' << rhs._imaginary << 'i';
        }
    
        friend std::istream& operator >> (std::istream& lhs, Complex& rhs) {
            return lhs >> rhs._real >> rhs._imaginary;
        }
    
        // 成员函数方式
        // 取反
        const Complex operator-() const {
            return Complex(-_real, -_imaginary);
        }
        // 全局函数方式
        // 自定义～为复数取模
        friend int operator~(const Complex& opd) {
            return sqrt(opd._real * opd._real + opd._imaginary * opd._imaginary);
        }
    
    private:
        int _real;
        int _imaginary;
    };
        
    int main() {
        Complex c1(3,4);
        std::cout << -c1 << std::endl;
        std::cout << ~c1 << std::endl;
        return 0;
    }
```
* 前缀类：操作数必须是左值（因为计算后要变化），表达式的值为左值，而且就是操作数本身。运算前后操作数的值会发生变化，表达式的值是变化之后的值。
* 后缀类：操作数是左值，表达式的值是右值，而且是操作数运算之前的历史备份。运算前后操作数的值发生变化，表达式的值变化以前的值。
```c++
    class Complex {
    public:
        Complex(int r = 0, int i = 0) : _real(r), _imaginary(i) {}
    
        void print() const {
            std::cout << _real << "+" << _imaginary << "i" << std::endl;
        }
    
        friend std::ostream& operator<<(std::ostream& lhs, const Complex& rhs) {
            return lhs << rhs._real << '+' << rhs._imaginary << 'i';
        }
    
        // 成员函数
        // 前++
        Complex& operator++() {
            ++_real;
            ++_imaginary;
            return *this;
        }
    
        // 全局函数
        // 前--
        friend Complex& operator--(Complex& opd) {
            --opd._real;
            --opd._imaginary;
            return opd;
        }
    
        // 成员函数
        // 后++
        const Complex operator++(int) {
            Complex old = *this;
            ++*this;
            return old;
        }
    
        // 全局函数
        // 后--
        friend const Complex operator--(Complex& opd, int) {
            Complex old = opd;
            --opd;
            return old;
        }
    private:
        int _real;
        int _imaginary;
    };
    
    int main() {
        Complex c1(1,2), c2(30,40);
        std::cout << ++c1 << std::endl; // 2+3i
        std::cout << c1 << std::endl;   // 2+3i
        ++c1 = c2;
        std::cout << c1 << std::endl;   // 30+40i
        ++++++++c1;
        std::cout << c1 << std::endl;   // 34+44i
        std::cout << --c1 <<std::endl;  // 33+43i
        std::cout << c1 << std::endl;   // 33+43i
        std::cout << c1++ << std::endl; // 33+43i
        std::cout << c1 << std::endl;   // 34+44i
        std::cout << c1-- << std::endl; // 34+44i
        std::cout << c1 << std::endl;   // 33+43i
        return 0;
    }
```
（5）三目操作符：无法重载。  
（6）其他：标操作符、函数操作符、类型转换操作符。
```c++
    class A {
    public:
        int& operator[](int i) {
            return _array[i];
        } 
        const int& operator[](int i) const {    
            return const_cast<A&>(*this)[i];  // 显式去常，隐式加常
        }   
    private:
        int _array[10];
    };
    
    class B{
    public:
        int operator()(int x, int y) {
            return x+y;
        }
    private:
    };
     
    class Integer {
    public:
        Integer(int i = 0): _i(i) {}
    
        // 类型转换操作符函数
        operator int() const {
            return _i;
        }
    
        int _i;
    };
    
    
    int main() {
        A a;
        a[0] = 100;
        a[1] = 101;
        std::cout << a[0] << " " << a[1]<< std::endl;
        const A& ra = a;
        std::cout << ra[0] << " " << ra[1]<< std::endl;
    
        B b;
        std::cout << b(12, 34) << std::endl;
    
        Integer x;
        x = 123;
        std::cout << x._i << std::endl;
    
        int y;
        y = x;
        std::cout << y << std::endl; 
        return 0;
    }
```
（7）不能重载的操作符：/:: /. /.* /?: /sizeof /typeid。   
（8）操作符重载的限制。  
* 所有操作数都是基本类型的不能重载。  
* 无法改变操作符的优先级。  
* 无法改变操作符的目数。  
* 无法发明新的操作符。  
* 保持操作符的语义一致性。   


















