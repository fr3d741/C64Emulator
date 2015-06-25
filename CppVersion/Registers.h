#ifndef REGISTERS_H
#define REGISTERS_H

#include <QObject>

namespace Hackathon
{
    struct Registers
	{
        quint8 IndexX;
        quint8 IndexY;
        quint8 Accumulator;
        quint16 ProgramCounter;

        //Status registers
        bool ZeroFlag;
        bool NegativeFlag;
        bool CarryFlag;
        bool OverflowFlag;
        bool DecimalFlag;
        bool InterruptFlag;
        bool BrkCommand;
    };
}

#endif
