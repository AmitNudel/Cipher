#ifndef __FLAGS__
#define __FLAGS__

namespace TicTacToe
{
class Flags
{
public:
    Flags();
    ~Flags() = default;
    Flags(const Flags& other) = delete;
    Flags operator=(const Flags& other) = delete;

    int GetFlag();
    void SetFlag(int setting);

private:
    int flag;
};
}

#endif //__FLAGS__
