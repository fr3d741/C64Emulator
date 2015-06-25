#ifndef C64COLORCONVERTER_H
#define C64COLORCONVERTER_H

#include <QColor>

namespace Hackathon
{
    /// <summary>
    /// Converts C64 color values to ConsoleColor.
    /// </summary>
    class C64ColorConverter
    {
    public:
        static QColor ByteToColor(quint8 value)
        {
            value = (quint8)(value & 15);
            switch (value)
            {
                case 0:
                    return Qt::black;
                case 1:
                    return Qt::white;
                case 2:
                    return Qt::darkRed;
                case 3:
                    return Qt::cyan;
                case 4:
                    return Qt::magenta;
                case 5:
                    return Qt::darkGreen;
                case 6:
                    return Qt::darkBlue;
                case 7:
                    return Qt::yellow;
                case 8:
                    return Qt::darkYellow;
                case 9:
                    return Qt::darkMagenta;
                case 10:
                    return Qt::red;
                case 11:
                    return Qt::darkGray;
                case 12:
                    return Qt::gray;
                case 13:
                    return Qt::green;
                case 14:
                    return Qt::blue;
                case 15:
                    return Qt::darkCyan;
                default:
                    throw new std::exception();
            }
        }

    };
}

#endif
