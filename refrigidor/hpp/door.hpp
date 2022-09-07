#ifndef _DOOR_
#define _DOOR_

#include <string>

namespace Refrigirator
{
class Door
{
public: 
    Door();
    ~Door() = default;
    Door(const Door& other);
    Door& operator=(const Door& other);

    bool IsDoorOpen();
    bool IsDoorClosed();
    void SetDoorPosition(const bool& desicion);

private:
    bool door_status;
    std::string door_color;
    // std::string knob_color;
};
}
#endif //_DOOR_