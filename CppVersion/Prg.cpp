#include "Prg.h"

namespace Hackathon
{

Prg::Prg()
{

}

Prg::Prg(QString fileName)
{
    QFile file(fileName);
    _size = file.size();
    _byteCode = new quint8[_size];
    memset((void*)_byteCode, 0, _size);

    quint8 byte1, byte2;
    file.open(QIODevice::ReadOnly);

    QDataStream stream(&file);

    stream >> byte1;
    stream >> byte2;
    ReadBytes(stream, 0);

    auto s = QString("%1%2").arg(QString(QString(byte2).toLatin1().toHex())).arg(QString(QString(byte1).toLatin1().toHex()));
    bool ok;
    StartAddress = (ushort)s.toInt(&ok, 16);

    file.close();
}


Prg::~Prg()
{
    delete[] _byteCode;
}

void Prg::Open(QString fileName)
{
    QFile file(fileName);
    _size = file.size();
    _byteCode = new quint8[_size];
    memset((void*)_byteCode, 0, _size);

    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);

    ReadBytes(stream, 0);

    file.close();
}

void Prg::ReadBytes(QDataStream& stream, int index)
{
    while(!stream.atEnd())
    {
         stream >> _byteCode[index++];
    }
}

}
