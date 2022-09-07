#include "light.hpp"

namespace Refrigirator
{
Light::Light()
:light_status(0)
{

}

Light::Light(const Light& other)
:light_status(other.light_status)
{

}

Light& Light::operator=(const Light& other)
{
    this->light_status = other.light_status;
    return *this;
}

void Light::LightTurnOn()
{
    light_status = 1;
}

void Light::LightTurnOff()
{
    light_status = 0;
}

}