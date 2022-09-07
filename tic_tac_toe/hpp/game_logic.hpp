
#ifndef __LOGIC__
#define __LOGIC__

#include "libs.hpp"
#include "flags.hpp"

namespace TicTacToe
{
class GameLogic
{
public:
    GameLogic();
    ~GameLogic() = default;
    GameLogic(const GameLogic& other) = delete;
    GameLogic& operator=(const GameLogic& other) = delete;

    std::string* SolidersInit();
    void StartGame();
    void EndGame();
    
private:
    void WinCheck(std::string* table, Flags& win_flag);
    void EndGameCheck(Flags& play_again_flag);
    const std::string *soliders;
    
};
}


#endif //__LOGIC__