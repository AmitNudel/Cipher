#ifndef __GRAPHICS__
#define __GRAPHICS__

#include "libs.hpp"
#include "table.hpp"

namespace TicTacToe
{
class Graphics
{
public:
    Graphics();
    ~Graphics() = default;
    Graphics(const Graphics& other) = delete;
    Graphics& operator=(const Graphics& other) = delete; 

    Table* TableInit();
    void StartScreen();
    void PrintTable();

private:
    Table *table;
    //shared pointer
};
}

#endif //__GRAPHICS__