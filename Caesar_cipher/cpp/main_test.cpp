#include <iostream>

#include "caesar_cipher.hpp"
#include "user.hpp"

using namespace Cipher;

void BasicTest()
{
    // Translator<std::string, std::string, int>* caesar = new Caesar;
    Caesar caesar;
    User user;
    caesar.SetKey(25);
    std::string str = "meow";
    user.SetEncode(caesar.Encode(str, 1));
    std::cout<<user.GetEncode()<<std::endl;

    str = "ldnv";
    user.SetDecode(caesar.Decode(str, 1));
    std::cout<<user.GetDecode()<<std::endl;
}

int main()
{
    BasicTest();
}