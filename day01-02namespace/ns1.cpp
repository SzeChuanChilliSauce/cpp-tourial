//
// Created by chensq on 4/8/20.
//

#include <iostream>


namespace ns {
    int var = 0;

    void fun() {
        std::cout << "ns::fun()" << std::endl;
    }
}

namespace ns1 {
    int a = 1;
    namespace ns2 {
        int a = 2;
        namespace ns3 {
            int a = 3;
        }
    }
}