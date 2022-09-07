#ifndef _WEED_SUBCLASSES_
#define _WEED_SUBCLASSES_

#include "libraries.hpp"

namespace Weed
{

class WeedType;
class WeedDosage;
class WeedKind;

class WeedType
{

public:    
    WeedType();
    // virtual ~WeedType() = 0;
    ~WeedType() = default; 
    WeedType(const WeedType& other) = delete;
    WeedType& operator=(const WeedType& other); //imp

    //what do I need to be able to do here?
    WeedDosage *GetWantedDosage(std::string weed_dosage);
private: 
    std::unordered_map<std::string, WeedDosage&> weed_dosage;
};

class WeedDosage
{
   
public:
    WeedDosage();
    // virtual ~WeedDosage() = 0;
    ~WeedDosage() = default;
    WeedDosage(const WeedDosage& other) = delete;
    WeedDosage& operator=(const WeedDosage& other); //imp

    void PrintAllKinds();
    WeedKind *GetKind(std::string weed_kind);

private:
    std::unordered_map<std::string, WeedKind&> weed_kind;
};

class WeedKind
{

public:
    WeedKind();
    virtual ~WeedKind() = 0;
    WeedKind(const WeedKind& other) = delete;
    WeedKind& operator=(const WeedKind& other) = delete;

    int PrintData();
    int GetAmount();
    int GetPrice();
    
private:
    std::string name_of_kind;
    int price;
    int amount;
};

}
#endif //_WEED_SUBCLASSES_