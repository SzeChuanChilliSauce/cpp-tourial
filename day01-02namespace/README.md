# Namespace 名字空间
## 为什么要有名字空间？名字空间的作用是什么？
* 避免产生名字冲突
* 将基于逻辑划分和基于物理划分独立开
# 写法
```
    namespace 名字空间名 {  
       名字空间成员1;  
       名字空间成员2;  
       ...  
    }
    namespace ns {
        int var = 0;
        void fun() { ... }
    }
```
# 名字空间合并
```
    namespace ns {  
       名字空间成员1;  
       名字空间成员2;  
    }
    namespace ns {
       名字空间成员3;  
    }
    
    逻辑上是一个名字，但是可以写在不同的文件中（类似其他高级语言的模块或包）
    a.cpp:
    namesapce ns {
        int var = 0;
        void fun() { ... }
    }
    
    b.cpp:
    namesapce ns {
        struct type { ... };
    }
```
# 使用名字空间中的名字
* 通过作用域限定操作符"::"
* 名字空间指令  
    using namespace 名字空间名;  
    using namespace std;  
    该条指令以后的代码中，对于所使用的名字空间中的名字可以直接引用，前提是没有冲突。
* 名字空间声明  
    using 名字空间名::成员名;    
    using ns::var;  
    using ns::fun;  
    using ns::type;  
    将指定名字空间中的特定成员引入当前作用域。  
### 注意  
名字空间指令：使得名字空间里的内容在当前作用域中可见。  
名字空间声明：是把声明的名称引入当前作用域，成为当前作用域中的名称。  
# 无名名字空间
C++会将不属于任何有名名字空间的名字通通放入无名名字空间中。对于无名名字空间中的名字，可以直接通过"::"访问。  
```c++
    int y = 7777;
    namespace nv {
        int y = 8888;
    
        void fun() {
            // 使用无名名字空间中的y
            std::cout << ::y << std::endl; // 7777
        }
    }
```
# 名字空间嵌套 
```c++
    namespace ns1 {
        int a = 1;
        namespace ns2 {
            int a = 2;
            namespace ns3 {
                int a = 3;
            }
        }        
    }
    
    std::cout << ns1::a << std::endl;
    std::cout << ns1::ns2::a << std::endl;
    std::cout << ns1::ns2::ns3::a << std::endl;
    
    // 取别名
    namespace ns123 = ns1::ns2::ns3;
    std::cout << ns123::a << std::endl;
```