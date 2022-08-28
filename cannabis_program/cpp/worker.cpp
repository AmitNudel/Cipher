#include "libraries.hpp"

namespace Weed
{
    Worker::Worker(std::string first_name, std::string last_name)
:first_name(first_name), last_name(last_name), id(GenerateId())
{
    // empty
}

Worker::Worker(const Worker& other)
:first_name(other.first_name), last_name(other.last_name), id(other.id)
{
    // empty
}

Worker& Worker::operator=(const Worker& other)
{
    first_name = other.first_name;
    last_name = other.last_name;
    id = other.id;
    
    return *this; 
}

unsigned int Worker::GetUserID(const User& user) const
{
    return user.GetUserId();
}

unsigned int Worker::GenerateId()
{
    return rand() % 4294967295;
}

std::string Worker::GetWorkerFirstName() const
{
    return first_name;
}
std::string Worker::GetWorkerLastName() const
{
    return last_name;
}
std::string Worker::GetWorkerFullName() const
{
    std::string full_name(GetWorkerFirstName());
    full_name+=' ';
    full_name+= GetWorkerLastName();
    return full_name;
}
unsigned int Worker::GetWorkerId() const
{
    return id;
}

// void Worker::UpdateWeed(std::string weed_type, std::string weed_dosage, std::string weed_kind, int amount)
// {
//     // weed_stock[weed] = amount; //might add new one if not exists? - check
// }
// void Worker::AddNewWeed(std::string weed_type, std::string weed_dosage, std::string weed_kind, int amount)
// {
//     // std::pair<std::string, int> new_weed (weed ,amount);
//     // weed_stock.insert(new_weed);
// }

// void Worker::RemoveWeed(std::string weed_type, std::string weed_dosage, std::string weed_kind)
// {
//     // if (true == IsWeedAvialable(weed))
//     // {
//     //     weed_stock.erase(weed);
//     // }
// }
// int Worker::WeedAmount(std::string weed_type, std::string weed_dosage, std::string weed_kind)
// {
//     // std::unordered_map<std::string, int>::const_iterator it = weed_stock.find(kind);
//     // if ( it == weed_stock.end())
//     // {
//     //     std::cout << "not found"; //exception? errno?
//     //     return -1;
//     // }
//     // return it->second;  
// }
// bool Worker::IsWeedAvialable(std::string weed_type, std::string weed_dosage, std::string weed_kind)
// {
//     // if (weed_stock.end() == weed_stock.find(kind)) // but what if it's the one in the end?
//     // {
//     //     return false;
//     // }
//     // return true;
// }
std::unordered_map<std::string, int>& Worker::WeedStockInit(WeedType& stock)
{
   
    //implement from a file in the future
}
}