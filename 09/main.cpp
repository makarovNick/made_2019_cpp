#include "threadpool.h"

#include <iostream>

struct A
{
    void operator()()
    {
        std::cout<<"HI again";
    }
};

int hi()
{
    return 3;
}

int main()
{   
    ThreadPool pool(10);
    auto kek = [](int a, int b){ std::cout<< a+b;};
    auto hihihi = [](){for (size_t i = 0; i < 20; i++)std::cout<<"HI"<<std::endl;};
    auto generate = [](const char*a,int){return;};

    //A a;
    // auto z = pool.exec(kek,1,2);
    // z.get();
    // z = pool.exec(hihihi);
    // z.get();s
    // z = pool.exec(generate, "yeeeeah", 1); 
    // z.get();
    auto a = pool.exec([](){return 2;});
    std::cout<< a.get();
    return 0;
}
