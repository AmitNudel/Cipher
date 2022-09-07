
#ifndef __GAME_VARIABLES__
#define __GAME_VARIABLES__

namespace TicTacToe
{
class GameVariables
{
public:
    GameVariables();
    ~GameVariables() = default;
    GameVariables(const GameVariables& other) = delete;
    GameVariables operator=(const GameVariables& other) = delete;
    bool operator==(int num);

    int GetArrLen();
    int GetLen();
    int GetSpaceFiller();
    int GetNoWinnerYet();
    int GetMaxLen();
    int GetWin();

private:
    const int ARR_LEN = 2;
    const int LEN = 3;
    const int SPACE_FILLER = '~';
    const int NO_WINNER_YET = 0;
    const int MAX_LEN = 9;
    const int WIN = 1;
};

}
#endif //__GAME_VARIABLES__
