#ifndef _USER_SIDE_
#define _USER_SIDE_

#include "libraries.hpp"
#include "weed_subclasses.hpp"

namespace Weed
{
class Shop
{
    friend class User;
    friend class Worker;
public:
    Shop();
    ~Shop();
    Shop(const Shop& other) = delete;
    Shop& operator=(const Shop& other) = delete;

    //should return the type that is passed to the user's buy list
    void GetWeedType(std::string weed_type);
    void SetWeedType(std::string type, WeedType& weed_type); //only the worker - how?
private:
    std::unordered_map<std::string, WeedType&> weed_types; //static?
    // long money_in_cashier; where should I put it?
    FILE *m_weed_list;
};
}
#endif //_USER_SIDE_