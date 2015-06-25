#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils
{
public:
    static quint16 ConvertToInt(quint8 address[])
    {
        bool ok;
        auto s = QString("%1%2").arg(QString(QString(address[1]).toLatin1().toHex())).arg(QString(QString(address[0]).toLatin1().toHex()));
        //auto s = String.Format("{0:X2}{1:X2}", address[1], address[0]);
        auto cim = s.toUInt(&ok, 16);
        return cim;
    }

    static quint16 ConvertToInt(quint8 address)
    {
    //    auto s = String.Format("{0:X2}", address);
    //    auto cim = Convert.ToUInt16(s, 16);
        bool ok;
        auto s = QString("%1").arg(QString(QString(address).toLatin1().toHex()));
        auto cim = s.toUInt(&ok, 16);
        return cim;
    }

    static quint16 ConvertToInt(std::auto_ptr<quint8> address)
    {
        return ConvertToInt(address.get());
    }
};
#endif // UTILS_H
