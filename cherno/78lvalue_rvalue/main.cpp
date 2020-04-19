#include <iostream>

int GetValue() { return 10; }

// 左值引用
int& GetValue2() {
    static int value = 10;
    return value;
}

// 普通变量可以接受左值和右值
void SetValue(int i) { }

// (左值)引用只能接受左值
void SetValue2(int& i) { }

// 常左值引用可以接受左值和右值
void SetValue3(const int& i)  { }

// 左值引用
void PrintName(std::string& name) { std::cout << "[lvalue] " << name << std::endl; }

// 常左值引用
void PrintName(const std::string& name) { std::cout << "[const lvalue] " << name << std::endl; }

// 右值引用
void PrintName(std::string&& name) { std::cout << "[rvalue] " << name << std::endl; };


int main() {
    // value - 左值
    // rvalue - 右值
    // 直观上: lvalue就是等号左边值, rvalue就是等号右边的值, 但是并不是所有的场景都适用
    // i - 变量,有空间,在内存中有位置(地址)
    // 10 - 字面量,没有空间,在内存中没有位置,即不能存放数据
    // 直观上: lvalue可以被赋值,rvalue不能被赋值
    int i = 10;
    // 10 = i; // 右值不能被赋值
    int a = i; // 将左值赋值给另外一个左值(i在等号右边,不能简单通过在等号的哪边来判断是否是左值活右值)

    // GetValue() 返回的是一个临时值(rvalue),存数到lvalue中
    i = GetValue();
    // GetValue() = 20; ERROR

    // 左值引用接受右值
    GetValue2() = 20;

    SetValue(i); // lvalue
    SetValue(10); // rvalue

    // 左值引用接受左值
    SetValue2(i); // OK
    // 左值引用不能接受右值
    // SetValue2(10); // ERROR
    // int& b = 10; // ERROR

    // 但是常左值引用就能接受右值
    const int& b = 10;
    /* 等价于如下
     * int temp = 10;
     * const int& b = temp;
     * 常左值引用接受左值和右值
     * */
    SetValue3(10);

    std::string firstName = "Dada";
    std::string lastName = "Chen";
    std::string fullName = firstName + lastName; // temporary - rvalue

    // lvalue
    PrintName(firstName);
    PrintName(lastName);
    PrintName(fullName);

    // rvalue
    // PrintName("data");
    // PrintName("chen");
    // PrintName(firstName+lastName);
    PrintName("Dada");
    PrintName("Chen");
    PrintName(firstName+lastName);

    // 所以我们有一种方法(左值引用)来区分lvalue,rvalue,临时值
    // 因为左值引用只能接受左值

    // 那么我们能不能写个只能接受右值的函数呢? 可以的
    // 需要使用右值引用 - &&
    PrintName(fullName);
    PrintName(firstName+lastName);
    // 函数重载后,右值会优先匹配右值引用
    // 如果没有右值引用,才会匹配常左值引用
    // 因此,我们就有一种方法(右值引用)来判断一个值是否为右值

    // 作用:
    //     1.右值引用在move语义中使用.
    //     2.做优化.如果我们知道某个变量(对象)是临时的,我们不必担心要必须确保它的生命周期,完整性以及拷贝它.
    //        我们只需简单地"偷取"它的资源到特定的对象,然后在其他地方使用,因为我们知道它是临时的,它不会存在很长时间.
    //

    return 0;
}
