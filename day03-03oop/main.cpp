#include"student.h"

class Student {
public:
    // 初始化表
    Student(const std::string& name = "", int age = 80) : _name(name), _age(age) {
        // 编译器在执行构造函数之前会做初始化，实际上下面的写法是先初始化，再赋值
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

int gx;
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

class D {
public:
    D(const std::string& str) : _str(str), _len(_str.length()) {}

    void show() {
        std::cout << "_str=" << _str << ", _len=" << _len << std::endl;
    }

private:
    int _len;
    std::string _str;
};

struct Date {
    int _year;
    int _mon;
    int _day;
};

class E {
public:
    E(int arr[], const Date& d) :
        _arr{ arr[0], arr[1], arr[2] },
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

int main() {
//    Student s1("岳不群", 59);
//    Student s2("任我行");
//    Student s3;
//    s1.show();
//    s2.show();
//    s3.show();
//
//    B b(1234);
//    b.show();
//
//    C c;
//    c.show();

//    D d("hello, world.");
//    d.show();

    int arr[3]{0,1,2};
    Date d{2020, 4, 19};
    E e(arr, d);
    e.show();

    return 0;
}
