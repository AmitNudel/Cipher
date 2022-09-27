#include "user_interface.hpp"

namespace Cipher
{
User_interface::User_interface()
:m_encode(), m_decode()
{
    
}

void User_interface::SetEncode(const std::string& encode)
{
    this->m_encode = encode;
}
void User_interface::SetDecode(std::string decode)
{
    this->m_decode = decode;
}

std::string User_interface::GetEncode()
{
    return m_encode;
}

std::string User_interface::GetDecode()
{
    return m_decode;
}

}