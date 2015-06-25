#ifndef STACK_H
#define STACK_H

#include <QObject>

namespace Hackathon
{
    class MemStack
	{
        quint8* stack;
        const ushort _pointer = 0x0100;
        ushort _counter;

    public:
        quint8 Pointer;

        MemStack(quint8 stack[]);

        void Push(quint8 data);

        quint8 Pop();
    };
}

#endif
