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

    std::string formatted;

    for(size_t i = 0; i < str.size(); ++i)
    {
        if(str[i] != '{') 
        {
            if(str[i] == '}') 
            {
                throw std::runtime_error("ERROR : '{' bracket  is missing");
            }

            formatted += str[i];
        }
        else 
        {
            std::string tmp;

            while(str[++i] != '}' && i < str.size())
            {
                if(!isdigit(str[i]))
                {
                    throw std::runtime_error("ERROR : wrong argument");
                }

                tmp +=str[i];
            }

            size_t arg_index = stoi(tmp);
            if(arg_index > arguments.size() - 1)
            {
                throw std::runtime_error("ERROR : wrong argument");
            } 

            formatted += arguments[arg_index];

            if(str[i] != '}')
            {
                throw std::runtime_error("ERROR : '}' bracket  is missing");
            } 
        }
    }

    return formatted;
} 