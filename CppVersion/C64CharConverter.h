#ifndef C64CHARCONVERTER_H
#define C64CHARCONVERTER_H

#include <QMap>

namespace Hackathon
{
    /// <summary>
    /// Converts C64 screen character codes to ASCII.
    /// </summary>
    class C64CharConverter
    {
        static QMap<quint8, char> byteToChar;

        static void ParseString();

    public:
        static char ConvertToAscii(quint8 value);
    };
}

#endif
