# 一、多重继承
## 1.一个子类从多个基类中派生。
```c++
    class Phone {
    public:
        Phone(const std::string& no) : _no(no) { }
        void call(const std::string no) const {
            std::cout << _no << "打电话给" << no << std::endl;
        }
        int foo(int x, int y) const {
            return x+y;
        }
        int ma;
    private:
        std::string _no;
    };
    
    class Player {
    public:
        Player(const std::string& media) : _media(media) {}
        void play(const std::string& clip) const {
            std::cout << _media << "播放器播放" << clip << std::endl;
        }
        int foo(int x, int y, int z) const {
            return x + y + z;
        }
        typedef int ma;
    private:
        std::string _media;
    };
    
    class Computer {
    public:
        Computer(const std::string& os) : _os(os) {}
        void run(const std::string& app) const {
            std::cout << "在"  << _os << "系统上运行" << app << std::endl;
        }
        void ma() {}
    private:
        std::string _os;
    };
    
    // 内存布局按继承顺序由低到高排列
    class SmartPhone : public Phone, public Player, public Computer {
    public:
        SmartPhone(const std::string& no, const std::string& media, const std::string& os) 
            : Phone(no), Player(media), Computer(os) {}
        // 引入同一作用域形成重载
        // using Phone::foo;
        // using Player::foo;
        int ma;
    private:
    };
    
    int main() {
        SmartPhone sp("13910010072", "MP3", "windows");
        sp.call("01062332018");
        sp.play("小苹果");
        sp.run("LOL");
    
        Phone* phone = &sp;
        Player* player = &sp;
        Computer* computer = &sp;
        // 完成隐式类型转换时，做了偏移
        std::cout << &sp << " " << phone << " " << player << " " << computer << std::endl;
        phone->call("01062332018");
        player->play("小苹果");
        computer->run("LOL");
    
        SmartPhone* psp = static_cast<SmartPhone*>(player);
        std::cout << psp << std::endl;
        psp = static_cast<SmartPhone*>(computer);
        std::cout << psp << std::endl;
    
        // 子类隐藏基类，多个基类之间不是隐藏关系
        sp.Phone::ma = 20;
        SmartPhone::Player::ma i;
        sp.Computer::ma();
        sp.ma = 10;
    
        sp.Phone::foo(100, 200);
        sp.Player::foo(100, 200, 300);
    
        return 0;
    }
```
## 2.钻石（菱形）继承
* 一个子类继承自多个基类，而这些基类又源自共同的祖先（公共基类），这样的继承的结构称为钻石继承。
* 派生多个中间子类的公共基类子对象，在继承自多个中间子类的汇聚子类对象中，存在多个实例。
* 通过汇聚子类中，或通过汇聚子类对象，访问公共基类的成员，会因为继承路径的不同而导致不一致。这种现象称为钻石继承问题。
```c++
    class A {
    public:
        A(int data) : _data(data) {}
    protected:
        int _data;
    };
    
    // 虚继承
    class B : virtual public A {
    public:
        B(int data) : A(data) {}
        void set(int data) {
            _data = data;
        }
    };
    
    class C : virtual public A {
    public:
        C(int data) : A(data) {}
        int get() const {
            return _data;
        }
    };
    
    class D : public B, public C {
    public:
        // 最终子类需要负责公共基类的初始化，如果指明A的构造方式，A将按缺省构造的方式
        // B、C的构造函数参数可以随意传，真正构造A是在调用A的构造函数时
        // 但是B、C的构造函数不能省，因为B、C中没有缺省构造函数
        D(int data) : B(-9), C(23), A(data) {}
    };
    
    int main() {
        D d(1000);
        std::cout << d.get() << std::endl; // 1000
        d.set(2000);
        std::cout << d.get() << std::endl; // 1000
        std::cout << sizeof(D) << std::endl;
        return 0;
    }
```
## 3.虚继承
* 通过虚继承可以保证公共基类子对象在汇聚子类对象中，仅存一份实例，且为多个中间子类对象所共享。
* 为了表示虚继承，需要在继承中使用virtual关键字。
* 一般而言，子类的构造函数不能指定间接基类的构造方式，但是一旦这个间接基类被声明为虚基类，它的所有子类无论是直接子类还是间接子类都必须显式地指明该公共基类子对相的构造方式，否则系统将按照缺省方式构造该子对像。


