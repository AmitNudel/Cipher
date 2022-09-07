#include "game_variables.hpp"

namespace TicTacToe
{
GameVariables::GameVariables()
:ARR_LEN(2), LEN(3), SPACE_FILLER('~'), NO_WINNER_YET(0),
MAX_LEN(9), WIN(1)
{

}

int GameVariables::GetArrLen()
{
    return ARR_LEN;
}

int GameVariables::GetLen()
{
    return LEN;
}

int GameVariables::GetSpaceFiller()
{
    return SPACE_FILLER;
}

int GameVariables::GetNoWinnerYet()
{
    return NO_WINNER_YET;
}

int GameVariables::GetMaxLen()
{
    return MAX_LEN;
}

int GameVariables::GetWin()
{
    return WIN;
}
bool GameVariables::operator==(int num)
{
    return *this == num;
}
}