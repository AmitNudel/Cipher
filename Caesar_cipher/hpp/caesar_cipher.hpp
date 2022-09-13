#ifndef __Caesar__
#define __Caesar__

#include "translator.hpp"

namespace Cipher
{
class Caesar : Translator<std::string,const std::string&, int>
{
public:
    Caesar(int def_key = 1);
    ~Caesar();
    //uncopyable

    void SetKey(int shift);
    int GetKey() const;

    std::string Encode(const std::string& str, int arg);
    std::string Decode(const std::string& str, int arg);

private:
    int current_key; 
};
}
#endif //__Caesar__