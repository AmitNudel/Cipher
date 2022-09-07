#include "flags.hpp"

namespace TicTacToe
{
Flags::Flags()
:flag(0)
{

}

int Flags::GetFlag()
{
    return flag;
}

void Flags::SetFlag(int setting)
{
    flag = setting;
}

}