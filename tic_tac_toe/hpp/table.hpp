#ifndef __TABLE__
#define __TABLE__

#include "libs.hpp"
#include "player.hpp"

namespace TicTacToe
{
class Table
{
public:
    Table();
    ~Table() = default; //unless allocates for table
    Table(const Table& other) = delete;
    Table& operator=(const Table& other) = delete;

    std::string* TableInit();
    std::string* GetTable();
    void UpdateTable(int user_input, const std::string& soliders, Player& player);
    void PrintTable();
    
private:
    std::string *table;
    // char table[3][3];
};
}

#endif //__TABLE__