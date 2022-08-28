
#include "libraries.hpp"

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
    Shop dispancery(NULL);
    dispancery.GetWeedType("oil");

}

void UserCheck()
{
    User first_user("Amit", "Nudel", 666);
}
int main()
{
   BasicCheck();
   WorkerCheck();
}