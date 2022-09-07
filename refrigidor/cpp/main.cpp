
#include "refrigirator.hpp"
#include "door.hpp"
#include "light.hpp"

using namespace Refrigirator;

int main()
{
    Door door;
    Light light;

    RefrigiratorMachine user_ref(door, light);
    user_ref.OpenDoor();
    user_ref.ChooseLightingSpeedOnOpeningDoor();
    

}