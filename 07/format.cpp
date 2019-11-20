#include <iostream>
#include <string>
#include <stdexcept>
namespace
{
    size_t index = 0;
    std::string result = "";
}

std::string format(const std::string& str)
{
    index = 0;
    if(str.find('{') || str.find('}'))
    {
        throw  std::invalid_argument("ERROR : wrong usage");
    }
    if(result.empty())
    {
        return str;
    }
    return str;
}

template<typename T>
std::string format(const std::string& str, T&& value)
{
    size_t pos;
    std::string place = "{" + index + "}";
    if( pos = str.find(place) != std::string::npos)
    {
        
    }
}

template<typename T, typename ...Args>
std::string format(const std::string& str, T&& value, Args&& ...args)
{

}

int main()
{

    auto z = format("{0} nigga {1} shit", 12, "dick");
    std::cout << z;

    return 0;
}