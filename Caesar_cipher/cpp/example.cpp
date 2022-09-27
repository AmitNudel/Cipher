#include <iostream>

#include "user_interface.hpp"
#include "caesar_cipher.hpp"


using namespace Cipher;


int main()
{
    
    User_interface user;
    Caesar caesar;

    std::string user_answer;
    std::string user_word; 
    int key = 0;

    
    std::cout<<"Set wanted key: ";
    std::cin>>key;

    caesar.SetKey(key);
    
    std::cout<<"Do you with to encode or decode a word?"<<std::endl;
    std::cin>>user_answer;

    std::cout<<"Enter the word -"<<std::endl;
    std::cin>>user_word;

    system("clear");

    if ("encode" == user_answer)
    {
        user.SetEncode(caesar.Encode(user_word, 0));
        std::cout<<user.GetEncode()<<std::endl;
    }
    else if ("decode" == user_answer)
    {
        user.SetDecode(caesar.Decode(user_word, 0));
        std::cout<<user.GetDecode()<<std::endl;
    }
}