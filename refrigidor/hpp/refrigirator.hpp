
#ifndef _RefrigiratorMachine_
#define _RefrigiratorMachine_

#include "door.hpp"
#include "light.hpp"

namespace Refrigirator
{
class RefrigiratorMachine
{
public: 
    RefrigiratorMachine(Door& door, Light& light);
    ~RefrigiratorMachine();
    RefrigiratorMachine(const RefrigiratorMachine& other);
    RefrigiratorMachine& operator=(const RefrigiratorMachine& other);

    void OpenDoor();
    void CloseDoor();

    void GetDoor();
    void GetLight();

    void ChooseLightingSpeedOnOpeningDoor();

private:
    void OpenLight();
    void CloseLight();

    Door& door;
    Light& light;
        
};
}
#endif //_RefrigiratorMachine_
