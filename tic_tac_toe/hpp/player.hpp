#ifndef __PLAYER__
#define __PLAYER__

#include "libs.hpp"
#include "flags.hpp"

namespace TicTacToe
{

class Player : Flags //how to handle this case?
{
public:
    Player();
    ~Player() = default;
    Player(const Player& other) = delete;
    Player& operator=(const Player& other) = delete;
    
    void UpdatePlayerFlag(Flags& win_flag);
    int GetPlayerFlag();

private:
    int player_flag;
    // const int WIN;
    // const int NO_WINNER_YET;
};

}
#endif //__PLAYER__