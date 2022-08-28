// #include "libraries.hpp"

// namespace Weed
// {
// WeedInventory::WeedInventory(FILE *weed_list)
// :weed_stock() //don't forget to try with a file
// {
//     m_weed_list = weed_list;
//     weed_stock = WeedStockInit();
// }
// std::string WeedInventory::PrintWeedTable()
// {
//     //is it ok?
//     for(auto& map : weed_stock)
//     {
//         std::cout<<map.first << ":" << map.second <<std::endl;
//     }
// }

// WeedInventory::WeedInventory(const WeedInventory& other)
// {
//     this->m_weed_list = other.m_weed_list;
// }

// WeedInventory::~WeedInventory()
// {
//     //fclose if needed? weed_list?
// }

// void WeedInventory::UpdateWeed(std::string& weed, int amount)
// {
//     weed_stock[weed] = amount; //might add new one if not exists? - check
// }
// void WeedInventory::AddNewWeed(std::string& weed, int amount)
// {
//     std::pair<std::string, int> new_weed (weed ,amount);
//     weed_stock.insert(new_weed);
// }

// void WeedInventory::RemoveWeed(std::string& weed)
// {
//     if (true == IsWeedAvialable(weed))
//     {
//         weed_stock.erase(weed);
//     }
// }
// int WeedInventory::WeedAmount(std::string& kind)
// {
//     std::unordered_map<std::string, int>::const_iterator it = weed_stock.find(kind);
//     if ( it == weed_stock.end())
//     {
//         std::cout << "not found"; //exception? errno?
//         return -1;
//     }
//     return it->second;  
// }
// bool WeedInventory::IsWeedAvialable(std::string& kind)
// {
//     if (weed_stock.end() == weed_stock.find(kind)) // but what if it's the one in the end?
//     {
//         return false;
//     }
//     return true;
// }
// std::unordered_map<std::string, int> WeedInventory::WeedStockInit()
// {
//     weed_stock["Lemon haze"] = 3;
//     weed_stock["Tzunami"] = 5;
//     weed_stock["alias Yarden: rm -r"] = 10;
//     //implement from a file in the future
// }

// }