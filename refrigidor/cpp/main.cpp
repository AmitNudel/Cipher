
#include "refrigirator_abstract.hpp"
#include "door.hpp"
#include "light.hpp"

using namespace Refrigirator;

int main()
{
    Door door;
    Light light;

    RefrigiratorAbstract user_ref(door, light);
    user_ref.OpenDoor();
    user_ref.ChooseLightingSpeedOnOpeningDoor();
    

}