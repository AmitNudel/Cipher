#include "libs.hpp"
#include "table.hpp"
#include "player.hpp"
#include "game_variables.hpp"

namespace TicTacToe
{
Table::Table()
:table(TableInit())
{
    
}

std::string* Table::TableInit()
{
    // Table table = new Table;?
    GameVariables var;

    for(int i = 0; i < var.GetLen(); i++)
    {
        for(int j = 0; j < var.GetLen(); j++)
        {
            table[i][j] = var.GetSpaceFiller();
        }
    }
    return table;
}

std::string* Table::GetTable()
{
    return table;
}

void Table::UpdateTable(int int_user_input, const std::string& soliders, Player& player)
{
    GameVariables var;
    table[int_user_input / var.GetLen()][int_user_input % var.GetLen()] = soliders[player.GetPlayerFlag()];
}

void Table::PrintTable()
{
    GameVariables var;
    system("clear");
    for(int i = 0; i < var.GetLen(); i++)
    {
        for(int j = 0; j < var.GetLen(); j++)
        {
            std::cout<<"%c"<<table[i][j]<<std::endl;
            if (j < var.GetLen() - 1)
            {
                std::cout<<"|"<<std::endl;
            }
        }
        std::cout<<"\n"<<std::endl;
        if (i < var.GetLen() - 1)
        {
            std::cout<<"-----\n"<<std::endl;
        }
    } 
    std::cout<<"\n"<<std::endl;

}

}