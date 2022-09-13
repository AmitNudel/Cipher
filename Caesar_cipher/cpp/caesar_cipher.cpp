#include "caesar_cipher.hpp"
#include "helpers.hpp"

namespace Cipher
{

const int NUM_ALPHABET = 26;

Caesar::Caesar(int def_key)
:current_key(def_key)
{
}
Caesar::~Caesar()
{
}
void Caesar::SetKey(int shift)
{
    current_key = shift;
}

int Caesar::GetKey() const
{
    return current_key;
}

std::string Caesar::Encode(const std::string& str, int arg)
{
    return Cipher(str, arg, GetKey());
}

std::string Caesar::Decode(const std::string& str, int arg)
{
    return Cipher(str, arg, NUM_ALPHABET - GetKey());
}

}
