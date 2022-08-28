#include "libraries.hpp"

namespace Weed
{
    User::User(std::string first_name, std::string last_name, unsigned int id)
:first_name(first_name), last_name(last_name), id(id)
{
    // if ID is not a num, execption? remrompting?
}

User::User(const User& other)
:first_name(other.first_name), last_name(other.last_name), id(other.id)
{
    // empty
}

User& User::operator=(const User& other)
{
    first_name = other.first_name;
    last_name = other.last_name;
    id = other.id;
    
    return *this; 
}
std::string User::GetUserFirstName() const
{
    return first_name;
}
std::string User::GetUserLastName() const
{
    return last_name;
}
std::string User::GetUserFullName() const
{
    std::string full_name(GetUserFirstName());
    full_name+=' ';
    full_name+= GetUserLastName();
    return full_name;
}
unsigned int User::GetUserId() const
{
    return id;
}


// std::string User::ShowAllWeedAvailable(std::string weed_type)
// {
//     while("oil" != weed_type && "flower" != weed_type)
//     {
//         std::cout<<"oil or flower?"<<std::endl;
//         std::cin>>weed_type;
//     }

//     // "oil" == weed_type ?  oils.PrintWeedTable() : flowers.PrintWeedTable();   
// }

// void User::BuyWeed(std::string weed_type, std::string weed_dosage, std::string weed_kind, int amount);
// {
//     if ("oil" == weed_type) //oils? oil?
//     {
//         auto oil_it = oils.weed_stock.find(weed_kind);
//         if (true == oils.IsWeedAvialable(weed_kind))
//         {
//             if (1 < oil_it->second)
//             {
//                 oils.weed_stock[weed_kind] -= 1;
//             }
//             else
//             {
//                 oils.weed_stock.erase(weed_kind);
//             }
//         }
        
//     }
//     else if ("flower" == weed_type) //flower? flowers?
//     {
//         auto flower_it = flowers.weed_stock.find(weed_kind);
//         if (true == flowers.IsWeedAvialable(weed_kind))
//         {
//             if (1 < flower_it->second)
//             {
//                 flowers.weed_stock[weed_kind] -= 1;
//             }
//             else
//             {
//                 flowers.weed_stock.erase(weed_kind);
//             }
//         }
//     }
// }

}