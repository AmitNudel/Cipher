#include <iostream>
#include "helpers.hpp"

namespace Cipher
{
bool IsAllLetters(std::string str)
{
    for(long unsigned int i = 0; i < str.size(); ++i)
    {
        if (0 == isalpha(str[i]))
        {
            return false;
        }
    }
    return true;
}

void GetUserPrompt(std::string str)
{
    while(false == IsAllLetters(str))
    {
        std::cout<<"Use letters only"<<std::endl;
        std::cin>>str; //? will it work with prompting the str?
    }
}

std::string Cipher(const std::string& str, int arg, int key)
{
    static_cast<void>(arg);
    GetUserPrompt(str);
    std::string result;
    
    for(long unsigned int i = 0; i < str.size(); ++i)
    {
        if (islower(str[i]))
        {
            result += char(int(str[i] + key - 97) % 26 + 97);
        }
        else
        {
            result += char(int(str[i]+ key -65) % 26 + 65);
        }
    }
    return result;
}
}