# 一、C++对象模型
* C++的对象模型和C的结构模型没有任何区别，包括成员布局以及对齐补齐的规则。
* 对象中只有成员变量，没有成员函数。类的成员变量在该类的每个对象中都有一份独立的拷贝。但是类的成员函数只有一份，且为该类的所有对象共享。
* 为了在一个函数中区分出不同的调用对象，编译器会为每个成员函数提供一个隐藏的指针参数——this指针，指向调用该成员函数的对象。在成员函数中
所有的成员变量的访问以及对其他成员函数的调用，实际上都是通过this指针完成的。
* 类的构造函数中同样具有this指针，指向这个正在被构造的对象。
```c++
    class Student {
    public:
        // Student(Student* this, const char* name, int age);
        Student(const char* name, int age) : _name{ 0 }, _age(age) {
            std::cout << "构造函数this: " << this << std::endl;
            strcpy(_name, name);
        }

        // 编译器编译为
        // void show(Student* this) {
        //     std::cout << this->_name << ", " << this->_age << std::endl;
        // }
        void show() {
            std::cout << "show函数this: " << this << std::endl;
            std::cout << _name << ", " << _age << std::endl;
        }
    
    private:
        char _name[256];
        int _age;
    };

    int main() {
        Student s1("令狐冲", 25); // s1在栈中
        std::cout << "&s1: " << &s1 << std::endl;
        s1.show(); // s1.show(&s1);
    
        // 成员函数不在对象中，而是在代码区
        std::cout << sizeof(s1) << std::endl; // 260
    
        Student s2("任盈盈", 21);
        std::cout << "&s2: " << &s2 << std::endl;
        s2.show(); // s2.show(&s2);
    
        // show在代码区，编译后二进制指令也只有一份，为什么s1、s2都打印各自的信息，不会打印错误或混淆呢？是怎么区分的呢？
        // 因为编译器编译后传了参数，参数就是调用者    
    }
```
## 显式使用this指针的场合
* 解决成员变量的名字冲突。
* 从成员函数中返回调用对象的自引用。
* 通过成员函数实现对象间的交互。
* 在成员函数销毁调用对象自身。
```c++
    /////////////////////////////////////////////////////////////////////////////////////////
    // 1.区分成员变量和局部变量
    class A {
    public:
        A(int* data, int num) {
            for (int i = 0; i < num; i++) {
                this->data[i] = data[i];
            }
            // 参数和成员便令重名，用this区分
            this->num = num;
        }
    private:
        int data[1024];
        int num;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
    // 2.对返回值做连续操作
    class B {
    public:
        B(): _counter(0) {}  
        B& inc() {
            ++_counter;
            return *this; // 返回自引用
        }
        int counter() { return _counter; } 
    private:
        int _counter;
    };
    ////////////////////////////////////////////////////////////////////////////////////////
    // 3.对象之间交互
    // 类的短式声明
    class Student;   
    class Teacher {
    public:
        void teach(Student* s);
        void reply(const char* answer) { _answer = answer; }
    private:
        std::string _answer;
    };
    
    class Student {
    public:
        void acceptQuestion(const char* question, Teacher* t) {
            std::cout << "老师提问: " << question << std::endl;
            t->reply("我不知道");
        }
    };
    
    void Teacher::teach(Student* s) {
        s->acceptQuestion("什么是this指针?", this);
        std::cout << "学生回答: "  << _answer << std::endl;
    }

    Teacher t;
    Student s;
    t.teach(&s);
    //////////////////////////////////////////////////////////////////////////////////////
    // 4.对象自我毁灭
    class C {
    public:
        A() { std::cout << "我出生了" << std::endl; }

        // 析构函数
        ~A() { std::cout << "我要死了" << std::endl; }

        void work() {
            std::cout << "工作..." << std::endl;
            delete this;
        }   
    };

    (new A)->work();
```




