#include <iostream>

#include "helpers.hpp"

namespace Cipher
{

const short LOWER_CASE = 97;
const short UPPDER_CASE = 65;
const short LETTERS = 26
;
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
            result += char(int(str[i] + key - LOWER_CASE) % LETTERS + LOWER_CASE);
        }
        else
        {
            result += char(int(str[i]+ key - UPPDER_CASE) % LETTERS + UPPDER_CASE);
        }
    }
    return result;
}

}