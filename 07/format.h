#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

template <typename T>
std::string to_str(T&& obj) 
{
    std::ostringstream os;
    os << std::forward<T>(obj);

    return os.str();
}

template <typename... Args>
std::string format(const std::string& str, Args&&... args) 
{
    std::vector<std::string> arguments = {to_str(std::forward<Args>(args))...};
    //arguments.emplacels_back(to_str(std::forward<Args>(args))...);

    std::istringstream is(str);
    //not to skip space sybmols
    is >> std::noskipws;

    std::string formatted;

    char c;
    while(is >> c) 
    {
        if(c != '{') 
        {
            if(c == '}') 
            {
                throw std::runtime_error("ERROR : '{' bracket  is missing");
            }

            formatted += c;
        }
        else 
        {
            size_t arg_index;

            is >> arg_index;
            if(arg_index > arguments.size() - 1 || !is.good() )
            {
                throw std::runtime_error("ERROR : wrong argument");
            } 

            formatted += arguments[arg_index];

            is >> c;
            if(c != '}')
            {
                throw std::runtime_error("ERROR : '}' bracket  is missing");
            } 
        }
    }

    return formatted;
} 