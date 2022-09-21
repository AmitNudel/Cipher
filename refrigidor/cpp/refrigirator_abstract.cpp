#include <iostream>
#include "refrigirator_abstract.hpp"
#include "refrigirator_helpers.hpp"

namespace Refrigirator
{

RefrigiratorAbstract::RefrigiratorAbstract(Door& door, Light& light)
:door(door), light(light)
{
    
}
RefrigiratorAbstract::~RefrigiratorAbstract()
{
    std::cout<<"RefrigiratorAbstract say bye bye"<<std::endl;
}

void RefrigiratorAbstract::OpenDoor()
{
    if (true == door.IsDoorClosed())
    {
        door.SetDoorPosition(true);
    }
    else
    {
        std::cout<<"Door is already open"<<std::endl;
    }
}

void RefrigiratorAbstract::CloseDoor()
{
    if (false == door.IsDoorClosed())
    {
        door.SetDoorPosition(false);
    }
    else
    {
        std::cout<<"Door is already closed"<<std::endl;
    }
}

void RefrigiratorAbstract::ChooseLightingSpeedOnOpeningDoor()
{
    int user_prompt = UserPrompt();
    if (0 == user_prompt)
    {
        ManualLightSpeedChange();
    }
    else 
    {
        AutomaticLightSpeedChange();
    }
}

void RefrigiratorAbstract::OpenLight()
{
    light.LightTurnOn();
}

void RefrigiratorAbstract::CloseLight()
{
    light.LightTurnOff();
}

Door& RefrigiratorAbstract::GetDoor()
{
    return door;
}

Light& RefrigiratorAbstract::GetLight()
{
    return light;
}

}