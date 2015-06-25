#include <cassert>

#include "Memory.h"
#include "utils.h"
#include "C64CharConverter.h"
#include "C64ColorConverter.h"

//Most probably this won't change at all
#define CONSOLE_WIDTH 40

namespace Hackathon
{

Memory::Memory()
    :Stack(_memory)
{
    memset((void*)_memory, 0, 0x10000);
}

void Memory::LoadProgram(Prg& program)
{
    for(int i = 0; i < program.size(); ++i)
    {
        _memory[program.StartAddress + i] = program.ByteCode()[i];
    }
}

void Memory::LoadProgram(Prg& program, quint16 startMemory, quint16 startProgram, quint16 length)
{
    for (int i = 0; i < length; ++i)
    {
        _memory[startMemory + i] = program.ByteCode()[startProgram + i];
    }
}


quint8 Memory::GetByte(int address)
{
    if (address == 0xDD00)
        return (quint8) (_memory[address] | 0x80);

    return _memory[address];
}

void Memory::SetByte(quint8 address[], quint8 data)
{
    auto cim = Utils::ConvertToInt(address);
    SetMemory(data, cim);
}

void Memory::SetByte(quint8 address, quint8 data)
{
    auto cim = Utils::ConvertToInt(address);
    SetMemory(data, cim);
}

void Memory::SetByte(int address, quint8 data)
{
    SetMemory(data, address);
}

void Memory::slotSetMemory(ushort address, quint8 data)
{
    SetMemory(data, (int)address);
}

void Memory::slotSnapshot()
{
    QImage img(_memory, 256, 256, QImage::Format_Indexed8);
    img.setColor(0, qRgb(0,0,0));
}

void Memory::WriteConsole(int cim, quint8 data)
{
    cim -= 0x400;

    int y = cim / CONSOLE_WIDTH;
    int x = cim % CONSOLE_WIDTH;

    emit signalSetChar(x, y, C64CharConverter::ConvertToAscii(data),
                             C64ColorConverter::ByteToColor(_memory[0xD021]),
                             C64ColorConverter::ByteToColor(_memory[0xD800 + cim]));

}

void Memory::WriteConsole(int cim)
{
    cim -= 0xD800;

    int y = cim / CONSOLE_WIDTH;
    int x = cim % CONSOLE_WIDTH;

    emit signalSetChar(x, y, C64CharConverter::ConvertToAscii(_memory[0x0400 + cim]),
                             C64ColorConverter::ByteToColor(_memory[0xD021]),
                             C64ColorConverter::ByteToColor(_memory[0xD800 + cim]));
}

void Memory::SetByteWithOffset(quint8 address[], quint8 offset, quint8 data)
{
    auto s = Utils::ConvertToInt(address);
    auto o = offset;
    auto cim = s + o;
    SetMemory(data, cim);
}

void Memory::SetMemory(quint8 data, int cim)
{
    if ((0xA000 <= cim && cim < 0xC000) || (0xE000 <= cim && cim < 0x10000))
    {
        return;
    }

    _memory[cim] = data;

    if (0x400 <= cim && cim < 0x7E8)
    {
        WriteConsole(cim, data);
    }
    else if (cim == 0xD021)
    {
        emit signalSetClearColor(C64ColorConverter::ByteToColor(_memory[0xD021]));
    }
    else if (0xD800 <= cim && cim < 0xDBE8)
    {
        WriteConsole(cim);
    }
}

}
