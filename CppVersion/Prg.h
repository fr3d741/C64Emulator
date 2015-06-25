#ifndef PRG_H
#define PRG_H

#include <QObject>
#include <QString>
#include <QDataStream>
#include <QFile>

namespace Hackathon
{
    class Prg : public QObject
	{
        quint8* _byteCode;
        int _size;
    public:
        ushort StartAddress;

    public:
        Prg();

        Prg(QString fileName);

        ~Prg();

        void Open(QString fileName);

        void ReadBytes(QDataStream& stream, int index);

        quint8* ByteCode(){return _byteCode;}

        int size(){return _size;}

    };
}

#endif
