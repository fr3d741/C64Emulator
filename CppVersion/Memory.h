#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>
#include <QColor>
#include <QImage>

#include "Prg.h"
#include "Stack.h"

namespace Hackathon
{
    class Memory : public QObject
	{
        Q_OBJECT

        quint8 _memory[65536];

    public:
        MemStack Stack;

        Memory();

        void LoadProgram(Prg& program);

        void LoadProgram(Prg& program, quint16 startMemory, quint16 startProgram, quint16 length);

        quint8 GetByte(int address);

        void SetByte(quint8 address[], quint8 data);

        void SetByte(quint8 address, quint8 data);

        void SetByte(int address, quint8 data);
    signals:
        void signalSetChar(int x, int y, char ch, QColor color1, QColor color2);

        void signalSetChar(int x, int y, char ch, bool invert = false);

        void signalSetBackColor(int x, int y, QColor color);

        void signalSetForeColor(int x, int y, QColor foreColor);

        void signalSetClearColor(QColor foreColor);

    public slots:
        void slotSetMemory(ushort address, quint8 data);
        void slotSnapshot();

    private:
        void WriteConsole(int cim, quint8 data);

        void WriteConsole(int cim);

        void SetByteWithOffset(quint8 address[], quint8 offset, quint8 data);

        void SetMemory(quint8 data, int cim);
    };
}

#endif
