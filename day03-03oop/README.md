# 一、面向对象
## 1.为什么要面向对象
* 相比于分而治之的结构程序设计，强调大处着眼的面向对象程序设计思想更适合与开发大型软件。
* 得益于数据抽象、代码复用等面向对象的固有技术，软件开发的效率获得极大的提升，成本却大幅降低。
* 面向对象技术在数据库、网路通信、图形界面等领域的广泛应用，意催生出各种设计模式和应用框架。
* 面向对象已经成为现代计算机程序设计语言的发展潮流，不但几乎所有新诞生的语言都是面向对象的，而且很多传统的结构化语言也在不断地引用
面向对象机制。
## 2.什么是面向对象
* 万物皆对象。
* 把型软件开成一个由对象组成的社会。
* 对象拥有足够的智能，能够理解来自其他对象的信息，并以适当的方式做出反应。
* 对象能够从高层对象继承某些特性，并允许底层对象从自己继承某些特性。
* 编写程序的过程就是一个描述对象的过程，最终使问题域和解域获得完美的统一。
* 面向对象的四大要素：封装、继承、多态、抽象。
# 二、类和对象
## 1.通过属性和行为描述具体的对象，其中属性表示对象的静态特征，行为则表示对象的动态特征。
## 2.拥有相同属性和行为的对象分为一组，即一个类。
|对象|属性|行为|
|:---:|:---:|:---:|
|狗|犬种|进食|
|&nbsp;|犬龄|睡觉|
|&nbsp;|体重|玩耍|
|&nbsp;|毛色|&nbsp;|
|&nbsp;|&nbsp;|&nbsp;|
|学生|姓名|吃饭|
|&nbsp;|年龄|睡觉|
|&nbsp;|学号|学习|
|&nbsp;|&nbsp;|&nbsp;|
|手机|品牌|接打电话|
|&nbsp;|型号|收发短信|
|&nbsp;|价格|上网|
|&nbsp;|&nbsp;|玩游戏|
## 3.类即逻辑抽象
* 简单类型：只能表示一个属性（变量）。
* 数组类型：可以表示多个属性（元素），但是类型必须相同。
* 结构体类型：可以表示多个类型不同的属性（字段），但是缺少对行为（函数）的描述。
* 类类型：既可以表示多个不同类型的属性（成员变量），同时也可以表示多个不同的行为（成员函数）。

|现实世界|逻辑空间|虚拟世界|
|:---:|:---:|:---:|
|狗→<br>（真实对象）|狗类→<br>（抽象对象）<br>↑<br>OOP|→狗对象<br>（逻辑对象）|
# 三、类的定义与实例化
## 1.类的主要类容
* 成员变量：描述对象的各种哦功能属性。
* 成员函数：描述对象的各种行为。
* 构造函数：对对象做初始化。
* 析构函数：对对象做终结化。
* 访控属性：决定成员的访问特性。  
    public（struct缺省） - 共有，谁都可以访问。    
    private（class缺省） - 私有，只有自己可以访问。  
    protected - 保护，只有自己和自己的子类可以访问。 
* 继承方式与基类：继承。
## 2.构造函数
* 函数名与类名相同，且没有返回类型。
* 构造函数在创建对象时被系统自动调用。  
A.直接定义变量，栈对象。  
B.用new操作符创建对象，堆对象。
* 构造函数在对象的整个生命周期内一定会被调用，且只被调用一次。
* 构造函数负责对成员变量初始化，分配必要的资源，设置对象的初始状态。
 ```c++
    class Student {
    public:
        // 构造函数
        Student(const std::string& name, int age, int no) {
            _name = name;
            _age = age;
            _no = no;
        }
    
        void eat(const std::string& food) { 
            std::cout << "我叫" << _name << "，正在吃" << food << std::endl; 
        }

        void sleep(int time) { 
            std::cout << "我今年"  << _age << "岁，睡了" << time << "小时" << std::endl; 
        }

        void learn(const std::string& course) { 
            std::cout << "我的学号是" << _no << "，现在学" << course << "课" <<std::endl; 
        }
    
        void setName(const std::string& name) {
            if (name == "sb") {
                std::cout << "不雅姓名"<< std::endl;
            } else {
                _name = name;
            }
        }
    
        void setAge(int age) {
            if (age < 0 || age > 128) {
                std::cout << "非法年龄" << std::endl;
            }
            else {
                _age = age;
            }
        }
    
        void setNo(int no) {
            if (no < 0 || no > 10000) {
                std::cout << "非法学号" << std::endl;
            } else {
                _no = no;
            }
        }
    private:
        std::string _name;
        int _age;
        int _no;
    };

    Student s1("张无忌", 29, 1001);
    s1.eat("面条");
    s1.sleep(1);
    s1.learn("C++");

    Student* s2 = new Student("令狐冲", 39, 2001);
    s2->eat("米饭");
    s2->sleep(2);
    s2->learn("UNIX-C");

    delete s2;
```
# 四、构造函数与初始化表
## 1.构造函数可以重载
* 构造函数通过其参数表的差异华以重载的形式提供不同的初始化方法。  
* 重载的构造函数通过构造实参的类型选择匹配。  
* 使用缺省参数可以减少构造函数重载版本的数量，注意避免重载冲突。  
```c++
    class Student {
    public:
        Student(const std::string& name, int age) {
            _name = name;
            _age = age;
        }
    
        Student(const std::string& name) {
            _name = name;
            _age = 20;
        }
        // 缺省构造函数
        Student() {
            _name = "";
            _age = 0;
        }
    
        // 也可以通过缺省参数构造函数达到上述三个构造函数的效果
        // Student(const std::string name = "", int age = 20) { _name = name; _age = age; }
        
        void show() {
            std::cout << _name << ", " << _age << std::endl;
        }
    
    private:
        std::string _name;
        int _age;
    };

    // 等价写法：Student s1 = Student("张无忌", 25);
    Student s1("张无忌", 25);
    Student s2("令狐冲");
    // Student s3(); // ERROR，会被编译器误解为函数声明
    Student s3;
    s1.show();
    s2.show();
    s3.show();

    Student* s4 = new Student("赵敏", 20);
    Student* s5 = new Student("周芷若", 19);
    Student* s6 = new Student();
    Student* s7  = new Student;
    s4->show();
    s5->show();
    s6->show();
    s7->show();
    delete s4;
    delete s5;
    delete s6;
    delete s7;

    Student sa[3];
    for (Student& s : sa) {
        s.show();
    }

    Student sc[3] = {
        Student("赵敏", 20),
        Student("周芷若"),
        Student(),
    };
    for (Student& s : sc) {
        s.show();
    }

    Student* sd = new Student[3];
    for (int i = 0; i < 3; i++) {
        (sd+i)->show();
    }
    delete []sd;
   
    Student* se = new Student[3]{
        Student("张无忌", 25),
        Student("令狐冲"),
        Student(),
    };
    for (int i = 0; i < 3; i++) {
        se[i].show();
    }
    delete []se;
```
## 2.具有特殊意义的构造函数
### （1）缺省构造函数
能够以无参的方式被调用的构造函数称为缺省构造函数，它表示对象默认初始化状态。
如果一个类中没有定义任何构造函数，那么编译器就会自动为其生成一个缺省构造函数。对于基本类型的成员变量不做任何处理，对于类类型的成员变量，
调用其相应类型的缺省构造函数。
```c++
    class A {
    public :
        A() {
            std::cout << "A的缺省构造函数" << std::endl;
            _data = 0;
        }
    
        A(int data) {
            std::cout << "A的有参构造函数" << std::endl;
            _data = data;
        }
    
        void show() { std::cout << "A::_data = "<< _data << std::endl; }
    
        int _data;
    };
    
    class B {
    public:
        void show() {
            _a.show();
            std::cout << "B::_i = " << _i << std::endl;
        }
    
        int _i; // 基本类型成员变量
        A _a; // 类类型成员变量
    };

    B b;
    b.show();
```
### （2）类型转换构造函数
凡是可以通过一个参数调用的构造函数都属于类型转换构造函数。
```c++
    class 目标类型 {
        /* explicit */ 目标类型(const 源类型& ) { ... }       
    };
```
通过该构造函数将源类型的对象隐式或显式地转换为目标类型的对象。如果希望该转换必须显式完整，可以在该类型转换构造函数前面加上explicit关键字。
```c++
    class Integer {
    public:
        Integer() {
            _data = 0;
        }

        Integer(int data) {
            std::cout << "Integer类型转换构造函数" << std::endl;
            _data = data;
        }
    
        int _data;
    };

    // 用常引用或右值引用才行，去掉const，编译错误
    void foo(const Integer& i) { std::cout << i._data << std::endl; }
    Integer bar() { return 400; }

    Integer i;
    std::cout << i._data << std::endl;

    // 编译器就在i（Integer）中找，是否存在只接受一个int参数的构造函数
    // 如果有，就调用该函数创建一个Integer对象赋值给i
    i = 200; // ??? 左边是Integer，右边是int
    std::cout << i._data << std::endl; // 200

    foo(300); // 300
    std::cout << bar()._data << std::endl; // 400
```
### （3）拷贝构造函数
当用一个对象构造与它同类型的副本对象时，编译器会通过拷贝构造函数完成该副本对象的初始化。
```c++
    class 类 {
        类(const 类&) { ... }    
    };
```
* 如果一个类没有定义拷贝构造函数，编译器就会自动提供一个缺省的拷贝构造函数，该函数对于基本类型的成员变量，按照字节复制；对于类类型的成员变量，
则会调用其相应类型的拷贝构造函数，构造其副本。  
* 多数情况下不需要自己定义拷贝构造函数，编译器会提供缺省版本足以满足要求。但在某些特殊情况下，需要自行定义，以弥补缺省版本的不足。   
拷贝构造会降低应用程序的性能，设计时尽量避免，比如通过引用传递参数。
* 编译器会通过必要的优化策略，减少拷贝构造的机会，通过-fno-elide-constructors选项可以关闭此优化特性。
```c++
    class Point3D {
    public:
        Point3D(int x = 0, int y = 0, int z = 0) {
            _x = x;
            _y = y;
            _z = z;
        }
    
        // 拷贝构造函数
        // 如果不用以你用，会编译错误，若不用引用就会无限递归
        // 如果不用const（也不用右值引用，Point3D(Point3D&& that)，C++11中称为移动构造函数），那么返回匿名对象的地方，就会编译错误
        Point3D(const Point3D& that) {
            std::cout << "拷贝构造" << std::endl;
            // _x _y _z是私有的，为什么可以在that外面使用that._x这种形式访问呢？
            // 访控属性只约束类型，不约束对象。只要是同一个类的，都可以访问。
            _x = that._x;
            _y = that._y;
            _z = that._z;
        }
    
        void show() const {
            std::cout << "(" << _x << "," << _y << "," << _z << ")" << std::endl;
        }
    
    private:
        int _x;
        int _y;
        int _z;
    };
    
    // 传参发生拷贝构造
    void foo(Point3D p) {
        p.show();
    }
    
    // 返回值发生拷贝构造
    Point3D bar() {
        // 构造一个临时的匿名对象，它的作用域是bar函数作用域
        // 函数的返回值也是匿名对象，它的作用域在调用者（main）作用域
        // 从bar中的匿名对象到main中的匿名对象会发生拷贝
        // 一般会被编译器优化，直接在调用者函数栈构造该匿名对象。如果要看到该现象，加编译选项-fno-elide-constructors
        return Point3D(40, 50, 60);
    }
    
    // 通过打印地址，匿名对象是否为同一个
    Point3D hum() {
        Point3D p = Point3D(40, 50, 60);
        std::cout << "bar:" << &p << std::endl;
        return p;
    }

    Point3D p1(10, 20, 30);
    p1.show();

    Point3D p2 = p1;
    p2.show();

    foo(p2);
    bar();

    const Point3D& p = hum();
    std::cout << "main:" << &p << std::endl;
```
编译器给出构造函数：

|自定义构造函数|系统定义构造函数|
|:---:|:---:|
|无|缺省构造函数<br>缺省拷贝函数|
|非拷贝构造函数|缺省拷贝构造函数|
|拷贝构造函数|无|
## 3.初始化表（指导成员变量获得定义）
### （1）通过在类的构造函数中使用初始化表，知名该类的成员变量如何被初始化。
### （2）类类型的成员变量，要么在初始化表中显式初始化，要么通过相应类型的缺省构造函数初始化。
### （3）类的常量型和引用型成员变量必须在初始化表中显式初始化，不能在构造函数体中赋初值。
### （4）类的成员变量按其在类中被声明的顺序依次初始化，而与其在初始化表中的排列顺序无关。
* 初始化和赋值是两个步骤，编译器会先初始化（分配内存，普通变量不做处理，类类型变量调用相应的构造函数），再执行构造函数中的代码。
```c++
    class Student {
    public:
        // 初始化表
        Student(const std::string& name = "", int age = 80) : _name(name), _age(age) {
            // 编译器在执行构造函数之前会做初始化，实际上下面的写法是先初始化，再赋值
            // 初始化的代码我们看不见，编译器隐式的做
            // 如果在初始化的时候就给定给定初始值，那么就不用做赋值操作，因此更快了
            // _name = name;
            // _age = age;
        }
        void show() {
            std::cout<< _name << ", " << _age << std::endl;
        }
    
    private:
        std::string _name;
        int _age;
    };
    
    // 必须使用参数表的情况
    class A {
    public:
        A(int data) : _data(data) {}
        void show() {
            std::cout << "A::_data = " << _data << std::endl;
        }
    private:
        int _data;
    };
    
    class B {
    public:
        // 一缺到底：如果B不写构造函数，会调用缺省构造函数，B又会去调用A的缺省构造函数（但是A没有缺省构造函数）
        // 因此，B只能显式调用A的代参的构造函数
        B(int data) : _a(data) {
            // 初始化和赋值是两个操作，编译器首先会把_a初始化出来，再赋值
            // 初始化的时候就会调用A的缺省构造函数，A没有缺省构造函数，因此（初始化）报错
            // _a = A(data); // ERROR
        }
    
        void show() {
            _a.show();
        }
    
    private:
        A _a;
    };

    Student s1("岳不群", 59);
    Student s2("任我行");
    Student s3;
    s1.show();
    s2.show();
    s3.show();

    B b(1234);
    b.show();
```
* 类里的成员变量是什么时候获得定义的？  
一般局部变量声明和定义是同时的（如int a=10）；但是类中的成员变量，在构造函数执行的时候，才获得定义（分配内存并初始化），其他时候都是声明。 
* 如果成员变量是引用或带有常属性的，能在声明的时候初始化吗？  
不能，声明是不能做初始化的，定义才能做初始化。  
* 写在构造函数里面不行吗？  
不行，构造函数里面的代码不叫初始化，叫赋值。要先有对象才能赋值，因此不能写在构造函数里。那么写在哪里呢？只能是初始化表。
```c++
    int gx = 5678;
    
    class C{
    public:
        // C() {
        //    _i = 1000; // ERROR，常量不能赋值
        //    _r = gx; // 把gx赋值给_r的目标，并不是_r去引用gx
        // }
    
        C() : _i(1000), _r(gx) {}
        void show() {
            std::cout << "_i = " << _i << ", _r = " << _r << std::endl;
        }
    private:
        const int _i;
        int& _r;
    };

    C c;
    c.show();
```
* 初始化表不是执行语句，成员变量不会按照初始化表中先后顺序初始化，而是按照其的声明顺序初始化。
```c++
    class D {
    public:
        // 写法不好，初始化有依赖，有前提（有特殊需求除外）
        D(const std::string& str) : _str(str), _len(_str.length()) {}
        
        // 改进：不要依赖成员变量，用实参求长度
        // D(const std::string& str): _str(str), _len(str.length()) {}
   
        void show() {
            std::cout << "_str=" << _str << ", _len=" << _len << std::endl;
        }
    
    private:
        int _len;
        std::string _str;
    };

    D d("hello, world.");
    d.show(); // _str=hello, world., _len=-1102640736
```
* 成员变量是数组和结构的时候
```c++
    class E {
    public:
        E(int arr[], const Date& d) :
            _arr{ arr[0], arr[1], arr[2] },
            /* _date(d) 结构作为整体初始化 */
            _date{ d._year, d._mon, d._day } {}
    
        void show() {
            for(const int e : _arr) {
                std::cout << e << ' ';
            }
            std::cout << std::endl;
            std::cout << _date._year << "年" << _date._mon << "月" << _date._day << "日" << std::endl;
        }
    private:
        int _arr[3];
        Date _date;
    };
    
    int arr[3]{0,1,2};
    Date d{2020, 1 1};
    E e(arr, d);
    e.show();
```

