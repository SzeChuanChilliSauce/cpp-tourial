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
# 单例模式
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
# 成员指针
通过类型的约束，表达指向类特定类型成员的指针。  




