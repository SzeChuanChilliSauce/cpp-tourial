# 一、纯虚函数、抽象类、纯抽象类
* 形如 virtual 返回类型 函数类型(形参表)[const]=0; 的虚函数称为纯虚函数。
* 至少包含一个纯虚函数的类就叫抽象类，抽象类不能实例化为对象。
* 如果一个抽象类的子类没有覆盖其基类中全部抽象函数，那么该子类也是抽象函数。
* 除了构造、析构、静态成员函数以外的全部成员函数都为纯虚函数的抽象类就叫做纯抽象类，亦称接口类。
```c++
    // 抽象类：有纯虚函数的类
    class Shape {
    public:
        Shape(int x, int y) : _x(x), _y(y) {}
        virtual void draw() const = 0;
    
    protected:
        int _x;
        int _y;
    };
    
    class Triangle : public Shape{
    public:
        void foo() {}
    };
    
    
    int main() {
        // 抽象类不能实例化
        // Shape s;
        // Triangle g;
        return 0;
    }
```
# 二、虚函数应用
* 降低耦合
```c++
    class Employee {
    public:
        Employee(const std::string& name="", int no=0, int age=0) : _name(name), _no(no), _age(age) {};
        std::string _name;
        int _no;
        int _age;
    };
    
    class Dao {
    public:
        virtual void insert(const Employee& emp) const = 0;
    };
    
    class OracleDao : public Dao {
    public:
        void insert(const Employee& emp) const {
            std::cout <<"向oracle数据库插入记录" << std::endl;
        }
    };
    
    class SQLServerDao : public Dao {
    public:
        void insert(const Employee& emp) const {
            std::cout <<"向SQLServer数据库插入记录" << std::endl;
        }
    };
    
    void business(const Dao& dao) {
        Employee emp;
        dao.insert(emp);
    }
    
    int main() {
        business(OracleDao());
        business(SQLServerDao());
        return 0;
    }
```
* 职责分离
```c++
    class Text {};
    class Rect {};
    class Image {};
    
    class Parser {
    public:
        void parse(const char* filename) {
            Text text;
            showText(text);
            Rect rect;
            showRect(rect);
            Image image;
            showImage(image);
        }
    
    private:
        virtual void showText(const Text&)   = 0;
        virtual void showRect(const Rect&)   = 0;
        virtual void showImage(const Image&) = 0;
    };
    
    class RenderForWindows :  public Parser {
    private:
        void showText(const Text& text)    override { std::cout << "显示windows文本" << std::endl; }
        void showRect(const Rect& rect)    override { std::cout << "显示windows矩形" << std::endl; }
        void showImage(const Image& image) override { std::cout << "显示windows图片" << std::endl; }
    };
    
    class RenderForMac : public Parser {
    private:
        void showText(const Text& text)    override { std::cout << "显示mac文本" << std::endl; }
        void showRect(const Rect& rect)    override { std::cout << "显示mac矩形" << std::endl; }
        void showImage(const Image& image) override { std::cout << "显示mac图片" << std::endl; }
    };
    
    int main() {
        RenderForWindows render;
        render.parse("xxx.pdf");
    
        return 0;
    }    
```
# 三、虚函数表和动态绑定
* 对于包含虚函数的类，编译器会为其生成一张虚函数表，即存放每个虚函数地址的函数指针数组，简称虚表（vtbl），每个虚函数对应一个虚函数表的索引号。
* 当编译器看到通过指针或引用调用虚函数时，并不急于生成有关函数的调用指令，相反它会用一段代码代替该调用语句，这段代码在运行时执行，完成如下操作：  
（1）确定调用者指针或引用的目标对象，并从中获取到虚表指针。  
（2）根据所调用函数的索引号从虚表中提取相应的函数地址。  
（3）根据函数地址调用该函数。  
这个过程因为是运行时完成的，所以成为动态绑定。  
```c++
    // 虚表（存放虚函数地址的数组）里面的函数指针类型
    // 由于虚函数的函数原型可能不全一样，但又放到一个数组中，因此可以（随意定义）暂是认为它们的原型是一致的（本质就是一个地址）
    typedef void(*VFUNC)(void*, double, char);
    // 虚表指针：对象中指向虚表的指针
    typedef VFUNC* VPTR;
    
    // 调用的时候就要转换成具体的虚函数类型
    typedef void(*COMMON)(void*);
    typedef int(*COMPUTE)(void*, int);
    
    class A {
    public:
        A(int data) : _data(data) {}
    
        virtual void foo() {
            std::cout << "A::foo:" << _data << std::endl;
        }
        virtual void bar() {
            std::cout << "A::bar:" << _data << std::endl;
        }
        virtual int compute(int delta) {
            std::cout << "A::compute" << std::endl;
            return _data + delta;
        };
    
    protected:
        int _data;
    };
    
    class B : public A {
    public:
        B(int data) : A(data) {}
    
        void foo() override {
            std::cout << "B::foo:" << _data << std::endl;
        }
        int compute(int delta) override {
            std::cout << "B::compute" << std::endl;
            return _data + 2*delta;
        }
    };
    
    int main() {
        // 静态绑定
        A a(100);
        a.foo();
        a.bar();
        B b(200);
        b.foo();
        b.bar();
    
        // 动态绑定
        A& r = b;
        r.foo();
        r.bar();
    
        std::cout << "--------------------------------" << std::endl;
        VPTR vptr = *(VPTR*)&a;
        std::cout << (void*)vptr[0] << " " << (void*)vptr[1] << " " << (void*)vptr[2] << std::endl;
        ((COMMON*)vptr)[0](&a);
        ((COMMON*)vptr)[1](&a);
        std::cout << ((COMPUTE*)vptr)[2](&a, 100) << std::endl;
    
        std::cout << "--------------------------------" << std::endl;
        vptr = *(VPTR*)&b;
        std::cout << (void*)vptr[0] << " " << (void*)vptr[1] << std::endl;
        ((COMMON*)vptr)[0](&b);
        ((COMMON*)vptr)[1](&b);
        std::cout << ((COMPUTE*)vptr)[2](&b, 100) << std::endl;
    
        return 0;
    }
```
* 动态绑定对性能的影响。  
（1）虚函数表会增加内存空间的开销。    
（2）虚函数调用的时间开销会大于普通函数。  
（3）虚函数不能内联。  
建议只有在确实需要多态性的场合才使用虚函数，否则尽量避免使用虚函数。
# 四、运行时类型信息（RTTI）
* 动态类型转化（dynamic_cast）  
动态类型转换应用在具有多态继承关系的父子类的指针或引用之间。在运行期间检查转换源的目标对象的类型与转换目的的类型是否一致，如果一直则返回
实际对象的指针或引用，否则返回空指针或抛出异常。
```c++
    class A{
    public:
        virtual void foo(){}
    };
    
    class B : public A {};
    class C : public B {};
    class D {};
    
    int main() {
        B b;
        A* pa = &b;
        std::cout << "pa=" << pa << std::endl;
    
        // pa实际指向B类对象，转换成功
        B* pb = dynamic_cast<B*>(pa);
        std::cout << "pb=" << pb << std::endl;
    
        // pa并不是指向C类对象，转换失败，安全
        C* pc = dynamic_cast<C*>(pa);
        std::cout << "pc=" << pc << std::endl; // 0
        if (pc == nullptr) {
            std::cout << "转换失败" << std::endl;
        }
    
        try {
            A& ra = b;
            C& rc = dynamic_cast<C&>(ra);
        } catch (std::bad_cast& ex) {
            std::cout << "转换失败:" << ex.what() << std::endl;
        }
    
        // pa并不是指向D类对象，转换失败，安全
        D* pd = dynamic_cast<D*>(pa);
        std::cout << "pd=" << pd << std::endl; // 0
        if (pd == nullptr) {
            std::cout << "转换失败" << std::endl;
        }
    
        // B是A的子类，转换成功
        pb = static_cast<B*>(pa);
        std::cout << "pb=" << pb << std::endl;
        // C是A的间接子类，转换成功，危险
        pc = static_cast<C*>(pa);
        std::cout << "pc=" << pc << std::endl;
        // D与A没有亲缘关系，转换失败，安全
        // pd = static_cast<D*>(pa);
        // std::cout << "pd=" << pd << std::endl;
    
        // 编译期、运行期都不检查，永远成功，危险
        pb = reinterpret_cast<B*>(pa);
        std::cout << "pb=" << pb << std::endl;
        pc = reinterpret_cast<C*>(pa);
        std::cout << "pc=" << pc << std::endl;
        pd = reinterpret_cast<D*>(pa);
        std::cout << "pd=" << pd << std::endl;
        return 0;
    }
```
* typeid操作符  
在运行期间动态获取对象的类型信息。
```c++
    class X {};
    class XYZ {};
    class A { virtual void foo() {} };
    class B : public A {};
    
    void bar(A* pa) {
        //if (!strcmp(typeid(*pa).name(), typeid(A).name())) {
        if (typeid(*pa) == typeid(A)) {
            std::cout << "传入的是A对象" << std::endl;
        } else if (typeid(*pa) == typeid(B)) {
            std::cout << "传入的是B对象" << std::endl;
        } else {
            std::cout << "未知类型" << std::endl;
        }
    }
    
    int main() {
        std::cout << typeid(char).name() << std::endl;
        std::cout << typeid(unsigned char).name() << std::endl;
        std::cout << typeid(short).name() << std::endl;
        std::cout << typeid(unsigned short ).name() << std::endl;
        std::cout << typeid(int).name() << std::endl;
        std::cout << typeid(unsigned int).name() << std::endl;
        std::cout << typeid(long).name() << std::endl;
        std::cout << typeid(unsigned long).name() << std::endl;
        std::cout << typeid(long long).name() << std::endl;
        std::cout << typeid(unsigned long long).name() << std::endl;
        std::cout << typeid(float).name() << std::endl;
        std::cout << typeid(double).name() << std::endl;
        std::cout << typeid(long double).name() << std::endl;
        std::cout << typeid(int*****).name() << std::endl;
        std::cout << typeid(const char*).name() << std::endl;
        std::cout << typeid(char const*).name() << std::endl;
        std::cout << typeid(char* const).name() << std::endl;
        std::cout << typeid(float[10]).name() << std::endl;
        std::cout << typeid(char[20]).name() << std::endl;
        std::cout << typeid(float[10][15]).name() << std::endl;
        std::cout << typeid(int*(*)(int*)).name() << std::endl;
        std::cout << typeid(int*(*[10])(int*)).name() << std::endl;
        std::cout << typeid(X).name() << std::endl;
        std::cout << typeid(XYZ).name() << std::endl;
    
        B b;
        A* pa = &b;
        std::cout << typeid(*pa).name() << std::endl;
        A a;
        bar(&a);
        bar(&b);
    
        return 0;
    }
```
# 五、虚析构函数
如果将基类的析构函数声明为虚函数，那么子类的析构函数也是虚函数，而且对基类版本形成覆盖。这时delete一个指向子类对象的基类指针，实际被执行
的是子类的析构函数。该函数在释放完成子类特有的资源后，会自动调用基类的析构函数，完成对基类资源的释放，最终释放掉所有的资源，没有内存泄漏。
```c++
    class A {
    public:
        A() {
            std::cout << "A构造" << std::endl;
        }
        virtual ~A() {
            std::cout << "A析构" << std::endl;
        }
    };
    
    class B : public A {
    public:
        B() {
            std::cout << "B构造" << std::endl;
        }
        ~B() {
            std::cout << "B析构" << std::endl;
        }
    };
    
    int main() {
        // B* p = new B;
        A* p = new B;
        delete p;
        return 0;
    }
```
# 六、虚与非虚
* 可以被声明为虚函数的函数  
普通成员函数  
成员函数形式的操作符函数  
析构函数
* 不能被声明为虚函数的函数  
静态成员函数（虚函数在虚表，虚表在对象中，静态成员函数没有this）  
全局函数形式的操作符函数  
构造函数