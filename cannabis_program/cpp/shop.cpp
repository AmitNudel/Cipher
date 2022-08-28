#include "libraries.hpp"

namespace Weed
{
Shop::Shop(FILE *weed_list)
:weed_types(), m_weed_list(weed_list)
{
    //need to map oils and flowers.

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
}