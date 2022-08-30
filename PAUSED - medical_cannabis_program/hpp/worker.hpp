
#ifndef _WORKER_
#define _WORKER_

#include "libraries.hpp"
#include "user.hpp"

namespace Weed
{
class Worker
{
    class WeedType;
    class Shop;
public:
    Worker(std::string first_name, std::string last_name);
    Worker(const Worker& other);
    ~Worker() noexcept = default;
    Worker& operator=(const Worker& other);

    unsigned int GetUserID(const User& user) const;
    // unsigned int ChangeUserId(const User& user);
    // std::string GetUserFullName();
    unsigned int GenerateId();

    unsigned int GetWorkerId() const;
    std::string GetWorkerFirstName() const;
    std::string GetWorkerLastName() const;
    std::string GetWorkerFullName() const;

    void UpdateWeed(std::string weed_type, std::string weed_dosage, std::string weed_kind, int amount); 
    void AddNewWeed(std::string weed_type, std::string weed_dosage, std::string weed_kind, int amount);
    void RemoveWeed(std::string weed_type, std::string weed_dosage, std::string weed_kind);
    int WeedAmount(std::string weed_type, std::string weed_dosage, std::string weed_kind);
    bool IsWeedAvialable(std::string weed_type, std::string weed_dosage, std::string weed_kind);
    std::unordered_map<std::string, int>& WeedStockInit(Shop& shop);
    
private:
    std::string first_name;
    std::string last_name;
    unsigned int id; //does it need to be static?
};


}
#endif //_WORKER_