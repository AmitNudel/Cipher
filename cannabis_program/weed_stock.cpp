
#include "libraries.hpp"

namespace Weed
{

WeedStock::WeedStock()
{
    
}

std::string WeedStock::BrowseAvialabeWeed(std::string weed_type)
{
    while("oil" != weed_type && "flower" != weed_type)
    {
        std::cout<<"oil or flower?"<<std::endl;
        std::cin>>weed_type;
    }

    "oil" == weed_type ?  oils.PrintWeedTable() : flowers.PrintWeedTable();   
}

std::string WeedStock::BuyWeed(std::string weed_type, std::string weed_kind, int amount)
{
    if ("oil" == weed_type) //oils? oil?
    {
        auto oil_it = oils.weed_stock.find(weed_kind);
        if (true == oils.IsWeedAvialable(weed_kind))
        {
            if (1 < oil_it->second)
            {
                oils.weed_stock[weed_kind] -= 1;
            }
            else
            {
                oils.weed_stock.erase(weed_kind);
            }
        }
        
    }
    else if ("flower" == weed_type) //flower? flowers?
    {
        auto flower_it = flowers.weed_stock.find(weed_kind);
        if (true == flowers.IsWeedAvialable(weed_kind))
        {
            if (1 < flower_it->second)
            {
                flowers.weed_stock[weed_kind] -= 1;
            }
            else
            {
                flowers.weed_stock.erase(weed_kind);
            }
        }
    }
}
}