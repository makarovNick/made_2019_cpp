#include "vector.h"

#include <iostream>
#include <string>
int main()
{
    vector<int> ls(256);
    std::cout<<"size : " << ls.size() << std::endl << "capacity : " << ls.capacity() << std::endl;
    ls.resize(32);
    std::cout<<"size : " << ls.size() << std::endl << "capacity : " << ls.capacity() << std::endl;
    for(size_t i = 0; i < 29; i++)
    {
        ls.pop_back();
    }
    std::cout<<"size : " << ls.size() << std::endl << "capacity : " << ls.capacity() << std::endl;


    
    return 0;
}