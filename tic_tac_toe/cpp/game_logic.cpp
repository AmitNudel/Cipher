#include "libs.hpp"

#include "game_logic.hpp"
#include "graphic_interface.hpp"
#include "input_interface.hpp"
#include "player.hpp"
#include "flags.hpp"
#include "game_variables.hpp"
#include "counter.hpp"

namespace TicTacToe
{
GameLogic::GameLogic()
:soliders(SolidersInit())
{

}

std::string* GameLogic::SolidersInit()
{
    std::string *soliders = new std::string{"X", "O"};
    return soliders;
}

void GameLogic::StartGame()
{
    Player player;
    Graphics graphic; 
    PositionInput user_position_input;
    Flags play_again_flag;
    Flags win_flag;
    GameVariables var;
    Counter overall_counter;

    if(0 == play_again_flag.GetFlag())
    {
        graphic.StartScreen();
        
    }
    else
    { 
        graphic.PrintTable();
    }

    while(var.GetNoWinnerYet() == win_flag.GetFlag() && overall_counter.GetCounter() != var.GetMaxLen())
    {
        // int result = user_position_input.GetUserInput(graphic.GetTable());
        // graphic.UpdateTable(result, soliders);
        // ++overall_count;
        // graphic.PrintTable();
        // std::cout<<"\n"<<std::endl;
        // graphic.PrintTable();
        // WinCheck(graphic.GetTable(), win_flag);
        //player.UpdatePlayerFlag();
        // overall_counter == MAX_LEN && NO_WINNER_YET == win_flag ? std::cout<<"\tTable Full!\n"<<std::endl :
        //                          std::cout<<"\tPlayer %d wins!\n"<< player_flag + 1<<std::endl;
        // EndGameCheck(play_again_flag);
    }
}

void GameLogic::WinCheck(std::string* table, Flags& win_flag)
{
    GameVariables var;

    for(int i = 0; i < var.GetLen(); ++i)
    {
        if (table[i][0] != var.GetSpaceFiller() && 
            table[i][0] == table[i][1] && table[i][0] == table[i][2])
        {
            win_flag.SetFlag(var.GetWin());
        }
        
        
        if (table[0][i] != var.GetSpaceFiller() && 
            table[0][i] == table[1][i] && table[0][i] == table[2][i])
        {
            win_flag.SetFlag(var.GetWin());
        }
    }
    /*axis*/
    if (table[0][0] != var.GetSpaceFiller() && 
        table[0][0] == table[1][1] && table[0][0] == table[2][2])
    {
        win_flag.SetFlag(var.GetWin());
    }
    
    if (table[0][2] != var.GetSpaceFiller() && 
        table[0][2] == table[1][1] && table[0][2] == table[2][0])
    {
        win_flag.SetFlag(var.GetWin());
    }

}

void GameLogic::EndGame()
{
    //end la game;
}

void GameLogic::EndGameCheck(Flags& play_again_flag)
{
    PlayAgain user_prompt;
    char *result = user_prompt.GetUserInput();
    if(*result == 'y' || *result == 'Y')
    {
        play_again_flag.SetFlag(1);
    }
    else
    {
        std::cout<<"\tGoodbye!\n"<<std::endl;
    }

    if (1 == play_again_flag.GetFlag())
    {
        StartGame();
    }
    else
    {
        EndGame();
    }
}

}