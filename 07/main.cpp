#include "format.h"

#include <iostream>

int main()
{
    std::string name = "Mark";
    unsigned yo = 18;
    std::string sex = "male";

    auto kek = format("hello, girls, my name is {0}, i'm {1} years old, and im {2}!!!"
                    , name
                    , yo
                    , sex 
                    );

    std::cout<<kek;

    return 0;
}
