#ifndef __GAME_COUNTER__
#define __GAME_COUNTER__

namespace TicTacToe
{
class Counter
{
public: 
    Counter();
    ~Counter() = default;
    Counter(const Counter& other) = delete;
    Counter operator=(const Counter& other) = delete;

    int GetCounter();
    void IncrementCounter();
    void DecrementCounter();

private:
    int counter;
};
}
#endif //__GAME_COUNTER__