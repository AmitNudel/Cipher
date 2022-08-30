
#ifndef _USER_
#define _USER_

#include "libraries.hpp"

namespace Weed
{
class User
{
    friend class Worker;
    class Shop;
public:
    User(std::string first_name, std::string last_name, unsigned int id);
    User(const User& other);
    ~User() noexcept = default;
    
    User& operator=(const User& other);
    unsigned int GetUserId() const;
    std::string GetUserFirstName() const;
    std::string GetUserLastName() const;
    std::string GetUserFullName() const;

    void ShowAllWeedAvailable(std::string weed_type);
    void BuyWeed(std::string weed_type, std::string weed_dosage, std::string weed_kind, int amount, Shop& shop);
    // void CheckIfAvailabe(std::string weed_type, std::string weed_dosage, std::string weed_kind);
    // void ShowOnlyOils();
    // void ShowOnlyFlowers();
    // void ShowAmount(std::string weed_type, std::string weed_dosage, std::string weed_kind);

private:
    std::string first_name;
    std::string last_name;
    unsigned int id;
    //דרך לאחסן את הוויד שהיוזר קנה - maybe a file? oil/flower, T?, type
};


}

#endif //_USER_