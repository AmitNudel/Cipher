
#include "libraries.hpp"

#include <fstream>

#include "user.hpp" //
#include "worker.hpp" //
#include "shop.hpp"
#include "weed_subclasses.hpp"

using namespace Weed;

void BasicCheck()
{
    Worker first_try("Clayde", "Meow");
    std::cout<<first_try.GetWorkerId()<<std::endl;
    std::cout<<first_try.GetWorkerFullName()<<std::endl;

    Worker second_try("Bonnie", "Meow");
    std::cout<<second_try.GetWorkerId()<<std::endl;
    std::cout<<second_try.GetWorkerFullName()<<std::endl;

    User first_user("Sisi", "pooki", 666);
    std::cout<<first_user.GetUserFullName()<<std::endl;
    std::cout<<first_user.GetUserId()<<std::endl;

    std::cout<<first_try.GetUserID(first_user)<<std::endl;
    
}

void WorkerCheck()
{
    Worker first_try("Dima", "String");
    Shop dispancery;

    WeedType oils;
    // oils.GetWantedDosage("T20");
    // dispancery.SetWeedType("oils", oils);
}

void UserCheck()
{
    User first_user("Amit", "Nudel", 666);
}

void ReadFromTable()
{
    std::ifstream oil_table_f;
    std::string oil_table(" ");

    oil_table_f.open("/home/myth/Desktop/my_projects/cannabis_program/stock/oils_stock_30.8.22.ods");
    if (!oil_table_f)
    {
        return;
    }
    do
    {
        oil_table_f>>oil_table;
        std::cout<<oil_table<<std::endl;
    }
    while(!oil_table_f.eof());
    
}

int main()
{
    BasicCheck();
    WorkerCheck();
    ReadFromTable();

}