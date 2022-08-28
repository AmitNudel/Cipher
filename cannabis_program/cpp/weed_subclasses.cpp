#include "libraries.hpp"

namespace Weed
{
WeedType::WeedType()
:weed_dosage()
{

}

// WeedDosage& WeedType::GetWantedDosage(std::string weed_dosage)
// {

// }

WeedDosage::WeedDosage()
:weed_kind()
{

}

void WeedDosage::PrintAllKinds()
{

}

// WeedKind& WeedDosage::GetKind(std::string weed_kind)
// {

// }

WeedKind::WeedKind()
:name_of_kind(), price(), amount()
{

}

int WeedKind::PrintData()
{
    return 1;
}

int WeedKind::GetAmount()
{
    return 1;
}

int WeedKind::GetPrice()
{
    return 1;
}
}