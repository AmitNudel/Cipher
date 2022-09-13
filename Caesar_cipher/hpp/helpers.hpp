#ifndef __Helpers__
#define __Helpers__

#include <string>

namespace Cipher
{
    
bool IsAllLetters(std::string str);
void GetUserPrompt(std::string str);
std::string Cipher(const std::string& str, int arg, int key);

}
#endif //__Helpers__