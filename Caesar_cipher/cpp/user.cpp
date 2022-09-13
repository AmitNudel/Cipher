#include "user.hpp"

namespace Cipher
{
User::User()
:m_encode(), m_decode()
{
    
}

void User::SetEncode(const std::string& encode)
{
    this->m_encode = encode;
}
void User::SetDecode(std::string decode)
{
    this->m_decode = decode;
}

std::string User::GetEncode()
{
    return m_encode;
}

std::string User::GetDecode()
{
    return m_decode;
}

}