# 动态内存分配
## 1.C中动态内存分配函数在C++中可以继续使用。
```c++
    #include <cstdlib>
    void* malloc(size_t size);
    void* calloc(size_t nmemb, size_t size);
    void* relloc(void* ptr, size_t size);
    void free(void* ptr);
```
## 2.new/delete操作符
### （1）动态分配/释放单个变量
### （2）动态分配/释放数组变量
### （3）动态分配/释放高维数组
### （4）new在分配内存失败的情况时，不是返回空指针，而是抛出bad_alloc异常
### （5）new(地址) 类型[大小]
```c++
    // 分配单个变量           
    int* p = new int; // 用0初始化
    std::cout << *p << std::endl;
    *p = 1234;
    std::cout << *p << std::endl;
    p = new int(5678); // 指定初始值
    std::cout << *p << std::endl;
    delete p;

    // 分配数组
    int* pa = new int[5]{10, 20, 30, 40, 50}; // 初始化表
    for (int i = 0; i < 5; i++) {
        std::cout << pa[i]<< std::endl;
    }
    delete[] pa;

    // 分配高维数组
    // C++11
    // auto prow = new int[3][4];
    int(*prow)[4] = new int[3][4];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            prow[i][j] = (i+1)*10+(j+1);
        }
    }
    delete[] prow;

    int(*ppage)[4][5] = new int[3][4][5];
    // int(*ppage)[4][5] = (int(*)[4][5])malloc(3*4*5);
    delete[] ppage;

    // 抛出异常 std::bad_alloc
    try{
        p = new int[0xFFFFFFFF];
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
        perror("new");
    }

    // 定位分配
    char* pool = new char[1024];            // 分配内存池
    int* pn = new(pool) int(123);           // 再分一个int的内存
    char* ps = new(pool+4) char[15];        // 再分15个char的内存
    strcpy(ps, "Hello, World!");
    double* pd = new(pool+19) double(3.14); // 再分一个double的内存
    std::cout << *pn << ' ' << ps << ' '  << *pd << std::endl;
    delete[] pool;
```
