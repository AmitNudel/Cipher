#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#include <string>

namespace Cipher
{
template <typename OUTPUT,typename INPUT, typename ...Args>
class Translator
{
public:
    Translator() = default;
    virtual ~Translator() = 0;

    virtual OUTPUT Encode(INPUT, Args...) = 0;
    virtual OUTPUT Decode(INPUT, Args...) = 0;
};

template <typename OUTPUT,typename INPUT, typename ...Args>
Translator<OUTPUT, INPUT, Args...>::Translator::~Translator() 
{

}
}
#endif //__TRANSLATOR__