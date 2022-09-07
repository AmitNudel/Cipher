#include "door.hpp"

namespace Refrigirator
{

std::string defualt_color = "Purple";

Door::Door()
:door_status(false), door_color(defualt_color)
{

}

Door::Door(const Door& other)
:door_status(other.door_status), door_color(other.door_color)
{
    
}

Door& Door::operator=(const Door& other)
{
    this->door_status = other.door_status;
    this->door_color = other.door_color;
    return *this;
}

bool Door::IsDoorOpen()
{
    return door_status == true ? true : false;
    
}

bool Door::IsDoorClosed()
{
    return IsDoorOpen() == false ? true : false;
    
} 

void Door::SetDoorPosition(const bool& desicion)
{
    door_status = desicion;
}
} 

