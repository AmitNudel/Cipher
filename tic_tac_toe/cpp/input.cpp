#include "libs.hpp"
#include "input_interface.hpp"
#include "player.hpp"
#include "game_variables.hpp"

namespace TicTacToe
{

int PositionInput::GetUserInput(std::string* table, Player& player)//const?
{
    GameVariables var;

    char *end_ptr = NULL;
    char c_user_input[10] = {'\0'};
    long int_user_input;
    
    do
    {
        printf("Player %d:", player.GetPlayerFlag() + 1);
        fgets(c_user_input, sizeof(c_user_input), stdin);
        int_user_input = strtol(c_user_input, &end_ptr, 10);
    }
    while(*end_ptr != '\n' ||0 > int_user_input || 8 < int_user_input ||
            var.GetSpaceFiller() != table[int_user_input/ var.GetLen()][int_user_input % var.GetLen()]);

    return int_user_input;
}

char *PlayAgain::GetUserInput()
{
    // char end_answer[10] = {'\0'};
    char *end_answer = new char[10]{'\0'};
    do
    {
        std::cout<<"Do you want to play again?\n"<<std::endl;
        fgets(end_answer, sizeof(end_answer), stdin);
    }
    while('y' != *end_answer  && 'n' != *end_answer 
          && 'Y' != *end_answer && 'N' != *end_answer);
    return end_answer;
}
}