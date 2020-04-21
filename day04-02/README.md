# 常函数
* 在类成员函数的参数表之后函数体的左花括号之前，加上const关键字，该成员函数的this指针具有常属性，这样的成员函数被称为常函数。
* 因为this指针被声明为常量指针（即目标只读的指针），所以无法修改成员变量的值，除非该成员变量被mutable关键字修饰。
```c++
    class Student {
    public:
        Student(const std::string name = "", int age = 0)
            : _name(name), _age(age), _times(0) {}   
        // 常函数：在该函数中不能修改成员变量
        // const修饰this
        // void show(const Student* this)
        void show() const {
            std::cout << _name << ", " << _age << std::endl;
            // 常含数中不能修改成员变量
            // _name = "sb";
            // _age = 10000;
    
            // 如果确实要修改，用去常转换
            // ++const_cast<Student*>(this)->_times;
    
            // 加mutable关键字，在常函数中也能修改
            ++_times;
        }
        int times() const {
            return _times; 
        }
    private:
        std::string _name;
        int _age;
        mutable int _times;
    };

    int main() {
        Student s("风清扬", 98);
        s.show();
        s.show();
        std::cout << s.times() << std::endl;
        return 0;
    }   
```
* 常对象（带有常属性的对象、指针、引用）只能调用常函数，非常对象既可以调用非常函数也可以调用常函数。原型相同的常函数和非常函数可以构成重载。
```c++
    class A {
    public:
        void foo() {}
        void bar() const {}
    
        // 重载
        void hum() { std::cout << "non-const" << std::endl; }
        void hum() const { std::cout << "const" << std::endl; }
    };

    int main() {
        A a;
        // 非常对象，即可调用非常函数也可调用常函数
        a.foo(); 
        a.bar(); 
    
        // 常对象只能调用常函数
        const A b;      // 常对象
        b.hum();
        const A& r = b; // 常对象
        r.hum();
        const A* p=&b;  // 常对象
        p->hum();
        return 0;
    }

```
# 析构函数
### 1.析构函数是类的特殊的成员函数
* 析构函数的函数名就是在类名前面加"~"。
* 析构函数没有返回类型。
* 析构函数没有参数。
* 析构函数不能重载。
### 2.析构函数在对象被销毁时自动调用
* 局部对象的析构函数由其所在最小作用域的右花括号调用。
* 堆对象的析构函数被delete操作符调用。
* 全局对象的析构函数，被进程加载器调用。
```c++
    class Array {
    public:
        Array(size_t size) : _array(new int[size]), _size(size) {
            std::cout << "构造函数: " << this << std::endl;
        }
        // 析构函数
        // 谁调用析构函数？
        // 包含该对象的最小作用域的右花括号
        ~Array() {
            std::cout << "析构函数: " << this << std::endl;
           delete[] _array;
        }
    
        int& at(size_t i) {
            if (i >= _size)
                throw std::string("out of index");
            return _array[i];
        }
    
        const int& At(size_t i) const {
            return const_cast<Array*>(this)->at(i);
        }
    
    private:
        int* _array;
        size_t _size;
    };

    int main() {
        {
            Array a(5);
            for (size_t i = 0; i < 5;i++) {
                a.at(i) = i+1;
            }
            for (size_t i = 0; i < 5;i++) {
                std::cout << a.at(i) << ' ';
            }
            std::cout << std::endl;
        }  
        std::cout << "再见喽！" << std::endl;
    
        // new分为两步：
        // 1.分配内存
        // 2.用所分配的内存作为this指针的形参调构造函数
        // a = malloc(sizeof(Array));
        // Array::Array(a);
        Array* pa = new Array(10);
    
        // delete分为两步：
        // 1.用对象的地址作this指针的形参调析构函数
        // 2.释放内存
        // Array::~Array(a);
        // free(a);
        delete  pa;
    
        return 0;
    } 
```
### 3.缺省析构函数
如果一个类没有定义析构函数，编译器会提供一个缺省析构函数。该函数对于基本类型的成员变量阿什么也不做，对于类类型的成员变量，则会调用其相应类型的析构函数。
```c++
    class A {
    public:
        A() {
            std::cout << "A构造" << std::endl;
        }
        ~A() {
            std::cout << "A析构" << std::endl;
        }
    };
    
    class B {
    private:
        A _a;
    };
    
    class C {
    public:
        C() : _a(new A) {}
        ~C() {
            delete _a;
        }
    private:
        A* _a;
    };

    int main() {
        B b;
        C c;
        return 0;
    }
```
### 4.拷贝构造和拷贝赋值
* 缺省方式的拷贝构造和拷贝赋值，对包括指针在内的基本类型成员变量安字节复制，导致浅拷贝问题。
* 为了获得完整意义上的对象副本，必须自己睇你工艺拷贝构造函数和拷贝赋值操作符函数，针对指针型成员变量做身拷贝。
* 拷贝赋值操作符函数的实现  
    1.避免自赋值  
    2.分配新资源  
    3.释放旧资源  
    4.拷贝新内容  
    5.返回自引用
```c++
    class String {
    public:
        // 构造
        String(const char* str = nullptr)
            : _str(strcpy(
                new char[strlen(str ? str : "") + 1], 
                str ? str : "" )) {}

        // 析构
        ~String() {
            if (_str) {
                delete[] _str;
            }           
        }    

        // 拷贝构造
        String(const String& that)
            : _str(strcpy(
                new char[strlen(that._str)+1],
                that._str)){}  

        // 拷贝赋值
        String& operator=(const String& rhs) {
            if (this != &rhs) {
                String str(rhs);
                swap(_str, str._str);
            }            
            return *this;
        }       
        
        // 
        const char* c_str() const {
            return _str;
        }
    private:
        char* _str;
    };

    int main() {
        String s1("hello");
        std::cout << s1.c_str() << std::endl;
        
        return 0;
    }
```





