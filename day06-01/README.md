# 一、继承的基本概念
## 1.共性和个性
|类型|属性|行为|
|:---:|:---:|:---:|
|学生|姓名|吃饭|
|&nbsp;|年龄|睡觉|
|&nbsp;|学号|学习|
|&nbsp;|&nbsp;|&nbsp;|
|教师|姓名|吃饭|
|&nbsp;|年龄|睡觉|
|&nbsp;|工资|授课|
|&nbsp;|&nbsp;|&nbsp;|
|人|姓名|吃饭|
|&nbsp;|年龄|睡觉|
|学生（人）|学号（特性）|学习（特性）|
|教师（人）|工资（特性）|授课（特性）|
* 共性表达类不同类型事物之间共有的属性和行为。
* 个性则着意刻画每种类型事物特有的属性和行为。
## 2.超集与子集
* 超集体现了基于共性的一般。
* 子集体现类针对个性的特殊。
## 3.基（父）类和子类
* 基类表示超集，体现共性，描述共有的属性和行为。
* 子类表示子集，体现个性，描述特有的属性和行为。
## 4.继承与派生
|基类|子类|
|:---:|:---:|
|人类<br>（姓名、年龄、吃饭、睡觉）|学生<br>（学号、学习）|
|&nbsp;|教师<br>（工资、授课）|
## 5.继承语法
* class 子类 : 继承方式1 基类1, 继承方式2 基类2, ... {};
```c++
    // 人类
    class Human {};
    // 学生
    class Student : public Human {};
    // 教师
    class Teacher : public Human {};
    // 助教
    class Assistant : public Student, public Teacher {};
```
* 继承方式  
public：共有继承，最常见的继承方式。    
protected：保护继承。  
private：私有继承。
## 6.共有继承的特点
* 皆然性：子类即基类。  
任何子类对象中都包含着它的基类子对象，而且通常位于子类对象的低地址部分。因此把一个指向子类对象的指针或引用子类对象的引用转换为其基类类型
可以隐式完成。实际上指这种转换就意味着把一个子类对象的基类部分看作是一个实际的基类对象。这种类型转换亦称向上造型。
```c++
    class Human{
    public:
        Human(const std::string& name = "", int age = 0) : _name(name), _age(age) {}
        void eat(const std::string& food) const {
            std::cout << _name << "吃" << food << std::endl;
        }
        void sleep(int hours) const {
            std::cout << _name << "睡" << hours << "小时" << std::endl;
        }
        void old() const {
            std::cout << "我今年" << _age << "岁" << std::endl;
        }
    protected: // 只有本类和子类可以访问
        std::string _name;
        int _age;
    };
    
    class Student : public Human {
    public:
        // 继承的成员不能写在初始化表中
        // Student(const std::string& name, int age, int no) : _name(name), _age(age), _no(no) {}
        Student(const std::string& name, int age, int no)
            : Human(name, age), // 指定基类的构造方式，如果不别，就安基类的缺省构造方式
            _no(no) {
             // 如下写法可以，但是不好，不满足类型自恰性
             // _name = name;
             // _age = age;
        }
        void learn(const std::string& course) const {
            std::cout << "我的学号" << _no << ",我学习" << course << std::endl;
        }
    private:
        int _no;
    };
    
    class Teacher : public Human {
    public:
        Teacher(const std::string& name, int age, double salary) : Human(name,age), _salary(salary) {}
        void teach(const std::string& course) const {
            std::cout << "我的工资" << _salary << "，我教" << course << "课程" << std::endl;
        }
    private:
        double _salary;
    };
    
    int main() {
        Student s1("乔峰", 30, 10001);
        s1.eat("牛肉");
        s1.sleep(5);
        s1.old();
        s1.learn("降龙十八掌");
    
        Teacher t1("段誉", 21, 8888.88);
        t1.eat("小龙虾");
        t1.sleep(8);
        t1.old();
        t1.teach("六脉神剑");
    
        Human* h = &s1; // 向上造型
        h->eat("肯德基");
        h->sleep(10);
        h->old();
        Student* ps = static_cast<Student*>(h);
        ps->learn("打狗棍法");
    
        Human& rt = t1; // 向上造型
        rt.eat("火锅");
        rt.sleep(7);
        rt.old();
        Teacher& t2 = static_cast<Teacher&>(rt);
        t2.teach("凌波微步");
    
        return 0;
    }
```
* 可访问性  
子类可以访问基类中哪些成员？公有成员、保护成员，基类的私有成员不能为子类所直接访问，但在子类中存在。
```c++
     class A {
     public:
         int _pub;
         void pub() {
             std::cout << "pub" << std::endl;
         }
     protected:
         int _pro;
         void pro() {
             std::cout << "pro" << std::endl;
             _pri = 100; // 子类间接访问基类私有成员
         }
     private:
         int _pri;
         void pri() {
             std::cout << "pri" << std::endl;
         }
     };
     
     class B : public A {
     public:
         void foo() {
             _pub = 0;
             pub();
             _pro = 0;
             pro();
             // _priv = 300; // ERROR
             // priv();      // ERROR
         }
     };
     
     int main() {
         B b;
         b._pub = 1;
         b.pub();
         // 保护成员类外不能访问
         // b._pro;  // ERROR
         // b.pro(); // ERROR
         // 私有成员类外不能访问
         // b._pri;  // ERROR
         // b.pri(); // ERROR
         return 0;
     }   
```
* 隐藏性  
在子类中定义了和基类同名的标识符（变量、函数、类型），那么子类中标识符就会隐藏基类中的标识符。除非通过作用域限定符显式地指明所访问的标识符源
自基类。
```c++
    class A {
    public:
        void foo() {
            std::cout << "A::foo" << std::endl;
        }
    
        void bar() {}
        int hum;
    };
    
    class B : public A {
    public:
        using A::foo; // 名字空间声明，形成重载
        void foo(int x) {
            std::cout << "B::foo" << std::endl;
            // hum = 10; // 子类隐藏基类
            A::hum = 10;
        }
    
        int bar;
        typedef unsigned int hum;
    };
    
    int main() {
        B b;
        // b.A::foo(); // 显式调用基类同名函数
        b.foo(100);
        b.foo();
    
        // b.bar(); // 被B中成员变量bar隐藏
        b.A::bar();
    
        // b.hum = 10; // 被B中hum类型隐藏
        b.A::hum = 10;
    
        return 0;
    }
```
* 传导性  
当子类对象被构造、析构、复制时，其基类子对像也需要同时被构造、析构、复制。  
当通过delete操作一个指向子类对象的基类指针时，实际被执行的是基类的析构函数，该函数不会调用（传导）子类的析构函数，此子类所特有的动态资源
将形成内存泄漏。
```c++
    class A {
    public:
        A() : _x(0) {
            std::cout << "A缺省构造" << std::endl;
        }
        A(int x) : _x(x) {
            std::cout << "A有参构造" << std::endl;
        } 
        A(const A& that) : _x(that._x) {
            std::cout << "A拷贝构造" << std::endl;
        }  
        A& operator=(const A& rhs) {
            std::cout << "A拷贝赋值" << std::endl;
            _x = rhs._x;
            return *this;
        }  
        ~A() {
            std::cout << "A析构函数" << std::endl;
        }   
        friend std::ostream& operator<<(std::ostream& lhs, const A& rhs) {
            return lhs << rhs._x;
        }    
    private:
        int _x;
    };
    
    class B: public A {
    public:
        // 没有指定基类的构造方式，默认用缺省方式
        B() : _y(0) {
            std::cout << "B缺省构造" << std::endl;
        }   
        // 指定基类构造方式
        B(int x, int y) : A(x), _y(y) {
            std::cout << "B有参构造" << std::endl;
        } 
        B(const B& that) : A(that), _y(that._y) {
            std::cout << "B拷贝构造" << std::endl;
        }  
        B& operator=(const B& rhs) {
            std::cout << "B拷贝赋值" << std::endl;
            A::operator=(rhs);
            _y = rhs._y;
            return *this;
        }  
        ~B() {
            std::cout << "B析构函数" << std::endl;
        }   
        friend std::ostream& operator<<(std::ostream& lhs, const B& rhs) {
            return lhs << static_cast<const A&>(rhs) << " " << rhs._y;
        }   
    private:
        int _y;
    };

    int main() {
        std::cout << "-----1------" << std::endl;
        B b1;
        std::cout << "-----2------" << std::endl;
        B b2(100, 200);
        std::cout << "-----3------" << std::endl;
        B b3 = b1;
        std::cout << "-----4------" << std::endl;
        b3 = b2;
        std::cout << "-----5------" << std::endl;
    
        std::cout << b3 << std::endl;
        std::cout << "-----6------" << std::endl;
        A* p = new B;
        delete p;
        std::cout << "-----7------" << std::endl;
        return 0;
    }
```
## 7.继承方式对访控属性的影响




