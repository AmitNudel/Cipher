#ifndef __USER__
#define __USER__

#include <string>

namespace Cipher
{
class User
{
public:
    User();
    ~User() = default;
    User(const User& other) = delete;
    User& operator=(const User& other) = delete;

    void SetEncode(const std::string& encode);
    void SetDecode(std::string decode);

    std::string GetEncode();
    std::string GetDecode();

public:
    std::string m_encode;
    std::string m_decode;
};
}

#endif //__USER__