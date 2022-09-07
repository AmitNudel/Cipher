#ifndef __INPUT__
#define __INPUT__

#include "libs.hpp"
#include "player.hpp"

namespace TicTacToe
{
class Input
{
public:

    Input() = default;
    virtual ~Input();
    Input(const Input& other) = delete;
    Input& operator=(const Input& other) = delete;

    virtual int GetUserInput(std::string* table, Player& player);
    virtual char* GetUserInput();
};

class PositionInput : Input
{
public:
    int GetUserInput(std::string* table, Player& player);
};



class PlayAgain : Input
{
public:
    char *GetUserInput();
};
}

#endif //__INPUT__