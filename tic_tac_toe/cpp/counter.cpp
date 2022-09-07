#include "counter.hpp"

namespace TicTacToe
{
Counter::Counter()
:counter(0)
{

}

int Counter::GetCounter()
{
    return counter;
}

void Counter::IncrementCounter()
{
    ++counter;
}

void Counter::DecrementCounter()
{
    --counter;
}
}