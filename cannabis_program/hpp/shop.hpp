#ifndef _USER_SIDE_
#define _USER_SIDE_

#include "libraries.hpp"
class WeedType;

namespace Weed
{
class Shop
{
    friend class User;
    friend class Worker;
public:
    Shop(FILE *weed_list);
    ~Shop();
    Shop(const Shop& other) = delete;
    Shop& operator=(const Shop& other) = delete;

    //should return the type that is passed to the user's buy list
    void GetWeedType(std::string weed_type);
private:
    std::unordered_map<std::string, WeedType&> weed_types; //static?
    // long money_in_cashier; where should I put it?
    FILE *m_weed_list;
};
}
#endif //_USER_SIDE_