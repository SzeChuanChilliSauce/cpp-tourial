# 一、异常
* 抛出对象：throw异常对象  
异常对象：基本类型的变量或类类型的对象。
```c++
    throw 100;  
    throw "内存分配失败";  
    throw MemoryError();  
```  
* 捕获异常  
```c++
    try {  
        // 可能引发异常的操作
    } catch(异常类型& 异常对象引用) {  
        // 对异常类型1的处理
    } catch(异常类型& 异常对象引用) { 
        // 对异常类型2的处理
    } catch(...) {
        // 对其他异常的处理
    } 
``````
* 异常流程  
（1）当代码执行到throw语句时，一方面会将所抛出的异常对象复制到系统安全区中，另一方面将流程执行到包含此throw语句最小最用域的右花括号处，并沿着
函数的调用路径，向上回溯，直到try块的右花括号处。然后根据异常对象的类型匹配一个适当的catch分支，执行其中的异常处理代码。  
（2）如果一个被抛出的异常，没有被任何代码捕获，将会被系统捕获，并终止进程，同时打印异常类型信息。  
（3）如果一个函数没有捕获它所引发的异常，那么该亦称将继续向上抛出。直到调用路径中的某个函数捕获类该异常。  
```c++
    class CalcException {
    public:
        CalcException(const std::string& msg, const std::string& file, const std::string& func, int no)
            : _msg(msg), _file(file), _func(func), _line_no(no) {}
    
        friend std::ostream& operator<<(std::ostream& out, const CalcException& rhs) {
            return out << rhs._msg << ":" << rhs._file << "," << rhs._func << "," << rhs._line_no;
        }
    
    private:
        std::string _msg;
        std::string _file;
        std::string _func;
        int _line_no;
    };
    
    void foo() {
        std::cout << "分配内存" << std::endl;
        void* ptr = malloc(1);
        if (!ptr) {
            throw 17;
        }
        std::cout << "分配内存成功" << std::endl;
        free(ptr);
    
        FILE* fp = fopen("none", "r");
        if (!fp) {
            throw std::string(strerror(errno));
        }
        fclose(fp);
    
        throw CalcException("calc_exception", __FILE__, __FUNCTION__ , __LINE__);
    }
    
    void bar() {
        std::cout << "调用foo之前" << std::endl;
        foo();
        throw 3.14;
        std::cout << "调用foo之后" << std::endl;
    }
    
    void hum() {
        try{
            std::cout << "调用bar之前" << std::endl;
            bar();
            std::cout << "调用bar之后" << std::endl;
        }
        catche(double& ex) {
            std::cout << ex << std::endl;
            throw;
        }
    }
    
    int main() {
        try {
            std::cout << "调用hum之前" << std::endl;
            hum();
            std::cout << "调用hum之后" << std::endl;
        }
        catch (int& ex) {
            std::cout << "出错了：" << ex << std::endl;
            return -1;
        }
        catch (std::string& ex) {
            std::cout << "出错了：" << ex << std::endl;
            return -1;
        }
        catch (CalcException& ex) {
            std::cout << "计算错误：" << ex << std::endl;
            return -1;
        }
        catch(...) {
            std::cout << "其他异常" << std::endl;
            return -1;
        }   
        return 0;
    }
```
* 异常说明  
（1）声明函数时，可以通过异常说明，声明函数所可能抛出的异常。该函数可以抛出异常说明以外的异常，但这些异常不能被其调用者捕获。  
```c++
    // 不抛出任何异常
    // void foo(int a) throw() {}
    
    // 可以抛出任何异常
    // void foo(int a) {}
    
    void foo(int a) throw(float, int, double, std::string) {
        switch (a) {
            case 1:
                throw 1;
                break;
            case 2:
                throw 3.14;
                break;
            case 3:
                throw std::string("Hello, World!");
                break;
            default:
                throw 3.14f;
        }
    }
    
    void bar() noexcept(false) {}
    
    int main(int argc, char* argv[]) {
        try {
            foo(atoi(argv[1]));
        }
        catch (int& ex) {
            std::cout << ex << std::endl;
        }
        catch (double& ex) {
            std::cout << ex << std::endl;
        }
        catch(std::string& ex) {
            std::cout << ex << std::endl;
        }
        catch (float& ex) {
            std::cout << ex << std::endl;
        }
        catch (...) {
            std::cout << "other: " << std::endl;
        }
    
        return 0;
    }
```
* 构造函数异常  
（1）在构造函数中可以抛出异常，表示在构造过程中出现的错误。  
（2）如果一个对象在构造过程中出现了异常，那么这个就被不完整构造。而一个不完整构造的对象，它的析构函数永远不会被执行。  
（3）所有在抛出异常之前分配的资源都应该在执行throw语句之前释放。
```c++
    class A {
    public:
        A(size_t size) : _pData(new int[size]) {
            FILE* fp = fopen("none", "r");
            if (!fp) {
                // throw之前释放资源
                if (_pData) {
                    std::cout << "释放内存" << std::endl;
                    delete [] _pData;
                }
                // 抛出异常
                throw -1;
            }
            fclose(fp);
        }
        ~A() {
            if (_pData) {
                std::cout << "释放内存" << std::endl;
                delete [] _pData;
            }
        }
    
    private:
        int* _pData;
    };
    
    int main() {
        try {
            A a(1024);
        }
        catch (int& ex) {
            std::cout << ex << std::endl;
        }
        return 0;
    }
```
* 析构函数异常  
永远不要在析构函数中抛出异常，而且还在防止在析构函数中再次抛出异常。
```c++
    A::~A() {
        try{
            foo();       
        }
        catch(...) {
            
        }   
    }
```