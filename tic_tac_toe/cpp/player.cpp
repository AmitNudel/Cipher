#include "libs.hpp"
#include "player.hpp"
#include "game_variables.hpp"

namespace TicTacToe
{

Player::Player()
:player_flag(0)
{

}

void Player::UpdatePlayerFlag(Flags& win_flag)
{
    GameVariables var;
    var.GetNoWinnerYet() == win_flag.GetFlag() ? (player_flag = (player_flag + 1) % var.GetArrLen()) : 0;
}

int Player::GetPlayerFlag()
{
    return player_flag;
}

}