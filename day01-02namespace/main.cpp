#include <iostream>
#include "ns1.cpp"
#include "ns2.cpp"

// int var = 9999;

int main() {
    // 作用域限定符
    std::cout << ns::var << std::endl;
    ns::fun();
    struct ns::type t{ 100, "cdd" };
    std::cout << t.x << ' ' << t.y << std::endl;

    // 名字空间指令
    using namespace ns;
    var++;
    std::cout << var << std::endl;
    fun();

    // 名字空间声明
    using nu::x;
    using nu::fun;
    std::cout << x << std::endl;
    fun();

    // 无名名字空间
    nv::fun();

    // 名字空间嵌套
    std::cout << ns1::a << std::endl;
    std::cout << ns1::ns2::a << std::endl;
    std::cout << ns1::ns2::ns3::a << std::endl;
    // 取别名
    namespace ns123 = ns1::ns2::ns3;
    std::cout << ns123::a << std::endl;

    return 0;
}


