#include <iostream>
#include "refrigirator.hpp"
#include "refrigirator_helpers.hpp"

namespace Refrigirator
{

RefrigiratorMachine::RefrigiratorMachine(Door& door, Light& light)
:door(door), light(light)
{
    
}
RefrigiratorMachine::~RefrigiratorMachine()
{
    std::cout<<"RefrigiratorMachine say bye bye"<<std::endl;
}
RefrigiratorMachine::RefrigiratorMachine(const RefrigiratorMachine& other)
:door(other.door), light(other.light)
{

}
RefrigiratorMachine& RefrigiratorMachine::operator=(const RefrigiratorMachine& other)
{
    this->door = other.door;
    this->light = other.light;
    return *this;
}

void RefrigiratorMachine::OpenDoor()
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

void RefrigiratorMachine::CloseDoor()
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

void RefrigiratorMachine::ChooseLightingSpeedOnOpeningDoor()
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

void RefrigiratorMachine::OpenLight()
{
    light.LightTurnOn();
}

void RefrigiratorMachine::CloseLight()
{
    light.LightTurnOff();
}

}