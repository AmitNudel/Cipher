#include "libs.hpp"

#include "graphic_interface.hpp"
#include "input_interface.hpp"
#include "table.hpp"
#include "player.hpp"
#include "game_variables.hpp"

namespace TicTacToe
{
Graphics::Graphics()
:table(TableInit())
{

}


void Graphics::StartScreen()
{
    PositionInput start; 
    Player player;
    GameVariables var; 

    std::cout<<"\n"<<std::endl;
    std::cout<<"\tTic Tac Toe\n"<<std::endl;

    std::cout<<"\n"<<std::endl;
    std::cout<<"Choose your position, numbers between 1-9:\n"<<std::endl;

    std::cout<<"\n"<<std::endl;

    int k = 0;
    int j = 0;

    for(int i = 0; i < var.GetLen(); i++)
    {
        for(j = 0; j < var.GetLen(); j++)
        {
            printf("%i+1", k);
            ++k;
        }
        std::cout<<"\n"<<std::endl;
    }
    std::cout<<"\n"<<std::endl;

    start.GetUserInput(table->GetTable(), player); //hmm. might do some trouble?
}

void Graphics::PrintTable()
{
    table->PrintTable();
}

Table *Graphics::TableInit()
{
    Table *table = new Table;
    return table;
}
}