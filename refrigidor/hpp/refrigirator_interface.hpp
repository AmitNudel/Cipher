#include "door.hpp"
#include "light.hpp"

namespace Refrigirator
{
class RefrigiratorInterface
{
public:
    
    RefrigiratorInterface() = default;
    virtual ~RefrigiratorInterface () = default;
    RefrigiratorInterface(const RefrigiratorInterface& other) = delete;
    RefrigiratorInterface& operator=(const RefrigiratorInterface& other) = delete;
    
    virtual void OpenDoor() = 0;
    virtual void CloseDoor() = 0;

    virtual Door& GetDoor() = 0;
    virtual Light& GetLight() = 0;

    virtual void ChooseLightingSpeedOnOpeningDoor() = 0;   

};
}