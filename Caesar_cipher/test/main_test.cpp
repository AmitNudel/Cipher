#include <iostream>

#include "caesar_cipher.hpp"
#include "user_interface.hpp"

using namespace Cipher;

void BasicTest()
{
    // Translator<std::string, std::string, int>* caesar = new Caesar;
    Caesar caesar;
    User_interface User_interface;
    caesar.SetKey(25);
    std::string str = "meow";
    User_interface.SetEncode(caesar.Encode(str, 1));
    std::cout<<User_interface.GetEncode()<<std::endl;

    str = "ldnv";
    User_interface.SetDecode(caesar.Decode(str, 1));
    std::cout<<User_interface.GetDecode()<<std::endl;
}

int main()
{
    BasicTest();
}