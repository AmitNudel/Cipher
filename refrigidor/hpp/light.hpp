#ifndef _LIGHT_
#define _LIGHT_

namespace Refrigirator
{
class Light
{
public:
    Light();
    ~Light() = default;
    Light(const Light& other);
    Light& operator=(const Light& other);    

    void LightTurnOn();
    void LightTurnOff();

private:
    int light_status;
};

}
#endif //_LIGHT_