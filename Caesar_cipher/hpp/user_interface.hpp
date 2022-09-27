#ifndef __User_interface__
#define __User_interface__

#include <string>

namespace Cipher
{
class User_interface
{
public:
    User_interface();
    ~User_interface() = default;
    User_interface(const User_interface& other) = delete;
    User_interface& operator=(const User_interface& other) = delete;

    void SetEncode(const std::string& encode);
    void SetDecode(std::string decode);

    std::string GetEncode();
    std::string GetDecode();

public:
    std::string m_encode;
    std::string m_decode;
};
}

#endif //__User_interface__