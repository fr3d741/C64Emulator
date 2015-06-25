#include "Stack.h"

namespace Hackathon
{

MemStack::MemStack(quint8 stack[])
{
    _counter = 0;
    Pointer = 0xFF;
    this->stack = stack;
}

void MemStack::Push(quint8 data)
{
    stack[_pointer + Pointer] = data;
    Pointer--;
    _counter++;
}

quint8 MemStack::Pop()
{
    if (_counter == 0)
        throw new std::exception();

    --_counter;
    ++Pointer;
    return stack[_pointer + Pointer];
}

}
