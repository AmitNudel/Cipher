
#ifndef _RefrigiratorAbstract_
#define _RefrigiratorAbstract_

#include "door.hpp"
#include "light.hpp"
#include "refrigirator_interface.hpp"

namespace Refrigirator
{
class RefrigiratorAbstract : RefrigiratorInterface
{
public: 
    RefrigiratorAbstract(Door& door, Light& light);
    ~RefrigiratorAbstract();
    // Uncopyable

    void OpenDoor();
    void CloseDoor();

    Door& GetDoor();
    Light& GetLight();

    void ChooseLightingSpeedOnOpeningDoor();

private:
    void OpenLight();
    void CloseLight();

    Door& door;
    Light& light;
        
};
}
#endif //_RefrigiratorAbstract_
