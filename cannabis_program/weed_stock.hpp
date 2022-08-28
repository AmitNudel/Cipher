
#ifndef _WEED_STOCK_
#define _WEED_STOCK_

#include "libraries.hpp"

namespace Weed
{

class WeedStock
{
public:    
    WeedStock();
    ~WeedStock() noexcept = default;
    WeedStock(const WeedStock& other) = delete;
    WeedStock& operator=(const WeedStock& other) = delete;

// private:
//     //vector
//     WeedInventory& oils;
//     WeedInventory& flowers;
};


}

#endif //_WEED_STOCK_
