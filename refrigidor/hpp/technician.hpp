
#include "refrigirator.hpp"

namespace Refrigirator
{
class Technician
{
    Technician();
    ~Technician();
    Technician(const Technician& other);
    Technician& operator=(const Technician& other);

    void FixRefrigirator(Refrigirator& refrigirator);
    

};
}