#include "libraries.hpp"
#include "weed_subclasses.hpp"
#include "shop.hpp"
namespace Weed
{
Shop::Shop()
:weed_types(), m_weed_list()
{
    //need to map oils and flowers.
    //mapping from last upadte? keep a file on which where were we?
}

Shop::~Shop()
{
    //free the file?
}

void Shop::GetWeedType(std::string weed_type)
{
    auto weed_it = weed_types.find(weed_type);
    if (weed_types.end() == weed_it)
    {
        //errno?
    }
    std::cout<<"WeedType"<<std::endl;//for now 
    
}

void Shop::SetWeedType(std::string type, WeedType& weed_type)
{
    weed_types.insert(std::pair<std::string, WeedType&>(type, weed_type));
}
}