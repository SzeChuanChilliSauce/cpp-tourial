# 一、类型的决定性
通过一个指针或引用访问类的成员，编译器只是根据指针或引用的类型决定是否可以访问该成员，而与此指针或引用的实际目标对象无关。
# 二、虚函数与多态
如果将基类中的某个成员函数声明为虚函数（在其返回值前面加上virtual），那么其子类中的同型函数也就是虚函数（无论其是否带有virtual关键字），
而且与基类版本形成覆盖关系。这时通过一个指向子类对象的基类指针或引用子类对象的基类引用，调用该虚函数，实际被执行的将是子类中的覆盖版本，
而非基类的原始版本。这种现象谓之多态。
```c++
    class Shape {
    public:
        Shape(int x, int y) : _x(x), _y(y) {}
        // 虚函数
        virtual void draw() const {
            std::cout << "图形(" << _x << "," << _y << ")" << std::endl;
        }
    protected:
        int _x;
        int _y;
    };
    
    class Rect : public Shape {
    public:
        Rect(int x, int y, int w, int h) : Shape(x, y), _width(w), _height(h) {}
        void draw() const {
            std::cout << "矩形(" << _x << "," << _y << ","<< _width << "," << _height  <<")" << std::endl;
        }
    private:
        int _width;
        int _height;
    };
    
    class Circle : public Shape {
    public:
        Circle(int x, int y, int r) : Shape(x, y), _radius(r) {}
        void draw() const {
            std::cout << "圆形(" << _x << "," << _y << ","<< _radius <<")" << std::endl;
        }
    private:
        int _radius;
    };
    
    void render(Shape* shapes[]) {
        for(int i = 0; shapes[i]; i++) {
            shapes[i]->draw();
        }
    }
    
    int main() {
        Shape* shapes[128]{};
        shapes[0] = new Rect(1,2,3,4);
        shapes[1] = new Circle(5,6,7);
        shapes[2] = new Circle(8,9,10);
        shapes[3] = new Rect(11,12,13,14);
        shapes[4] = new Rect(15,16,17,18);
        render(shapes);
        
        return 0;
    }    
```
# 三、重载、隐藏、覆盖
重载必须在用一个作用域。  
覆盖必须是同型的虚函数。  
如果不是重载也不是覆盖，而且函数名还一样，那就是隐藏。
# 四、有效覆盖的前提条件
* 只有类的非静态成员函数才能被声明为虚函数，全局函数和类的静态成员函数都不能是虚函数。
* 只有在基类中被声明为虚函数的成员函数才能在子类中覆盖。
```c++
    // 只有非静态成员函数才能被声明为虚函数
    // virtual void foo() {}
    
    class A {
    public:
        // 只有非静态成员函数才能被声明为虚函数
        // virtual static void foo(){}
        void foo() {
            std::cout << "A::foo" << std::endl;
        }
    };
    
    class B : public A {
    public:
        // 隐藏A::foo
        virtual void foo() {
            std::cout << "B::foo" << std::endl;
        }
    };
    
    class C : public B {
    public:
        // 覆盖B::foo
        void foo() {
            std::cout << "C::foo" << std::endl;
        }
    };
    
    class D : public C {
    public:
        // 覆盖C::foo
        void foo() {
            std::cout << "D::foo" << std::endl;
        }
    };
    
    int main() {
        B b;
        A& rb= b;
        rb.foo();
    
        C c;
        B& rc = c;
        rc.foo();
    
        D d;
        C& rd = d;
        rd.foo();
    
        return 0;
    }
```
* 虚函数在子类中的覆盖版本必须和该函数的基类版本拥有完全相同的签名（函数名、形参表、常属性）要严格一致。
```c++
    class E {
    public:
        virtual void foo() {}
    };
    
    class F : public E {
    public:
        // 函数名不一致
        virtual void bar() {}
        // 形参表不一致
        virtual void foo(int x) {}
        // 常属性不一致
        virtual void foo() const {}
        // 覆盖
        void foo() {}
    };
```
* 如果基类中虚函数的返回类型为基本类型或类类型的对象，那么子类的覆盖版本必须返回相同的类型。
* 如果基类中的函数返回类类型的指针或引用，那么该函数在子类中的覆盖版本可以返回其基类版本返回类型的公有子类的指针或引用——类型协变。
```c++
    class X {};
    class Y : public X {};
    class Z {};
    
    class G {
    public:
        virtual void foo() {}
        virtual int bar() {}
        virtual X hum() {}
        virtual X* fun() {}
    };
    
    class H : public G {
    public:
        // int foo() {}
        void foo() {}
        // long bar() {}
        int bar() {}
        // Y hum() {}
        X hum() {}
        // Z* fun() {}
        Y* fun() {}
    };
```
* 子类中的覆盖版本不能比基类版本说明抛出更多的异常。
* 无论基类中的虚函数位于该类的公有、私有、保护部分，该函数在子类中的覆盖版本都可以在任何访控区域。
```c++
    class I {
    public:
        virtual void foo() {
            std::cout << "I::foo" << std::endl;
        }
    };
    
    class J : public I {
    private:
        // 覆盖I::foo
        void foo() {
            std::cout << "J::foo" << std::endl;
        }
    };
    
    int main() {
        J j;
        // j.foo();
        I& rj = j;
        rj.foo();
        return 0;
    }
```
```c++
    class Base {
        virtual void foo();       // 1
        virtual void foo() const; // 2 
    };

    class Derived : public Base {
        virtual void foo();       // 3
        virtual char foo() const; // 4
    };

    1和2，重载
    3和4，重载
    3隐藏2，覆盖1
    4隐藏1，试图覆盖2时报错 
```
# 五、多态的条件
* 多态性除了需要在子类和基类间形成有效的虚函数覆盖以外，还必须通过基类的指针或引用访问该函数。   
* 当基类的构造函数被子类的构造函数调用时，子类对象尚不能说是子类类型，它只表现出基类类型的外观和行为。这时调用虚函数，只能被绑定到基类版本，
没有多态性。  
* 当基类的析构函数被子类的析构函数调用时，子类对象已不在是子类类型，它只表现出基类类型的外观和行为。这时调用虚函数，只能被绑定到基类版本，
没有多态性。
```c++
    class A {
    public:
        A() {
            // this此时是指向基类对象的指针，子类特有的部分还没构造出来
            // this->foo();
            foo(); // A::foo
        }
    
        ~A() {
            // 先析构子类，此时子类特有的部分已经没有了
            // this->foo();
            foo(); // A::foo
        }
    
        virtual void foo() {
            std::cout << "A::foo" << std::endl;
        }
    
        void bar() {
            // this是指向子类的基类指针
            // this->foo();
            foo(); // B::foo
        }
    };
    
    class B : public A {
    public:
        void foo() {
            std::cout << "B::foo" << std::endl;
        }
    };
    
    int main() {
        B b;
        // A a = b;
        A& a = b;
        a.foo();
        b.bar();
    
        return 0;
    }
```