#include "C64CharConverter.h"

#include <QString>
#include <QStringList>

namespace Hackathon
{

QMap<quint8, char> C64CharConverter::byteToChar;

void C64CharConverter::ParseString()
{
    QString codes = "\n\
  @| |  0\n\
  A|a|  1\n\
  B|b|  2\n\
  I|i|  9\n\
  J|j| 10\n\
  K|k| 11\n\
  L|l| 12\n\
  M|m| 13\n\
  N|n| 14\n\
  O|o| 15\n\
  P|p| 16\n\
  Q|q| 17\n\
  R|r| 18\n\
  S|s| 19\n\
  T|t| 20\n\
  U|u| 21\n\
  V|v| 22\n\
  W|w| 23\n\
  X|x| 24\n\
  Y|y| 25\n\
  Z|z| 26\n\
  [| | 27\n\
   | | 28\n\
  ]| | 29\n\
  ^| | 30\n\
   | | 31\n\
SPACE| | 32\n\
  !| | 33\n\
 \"\"| | 34\n\
  #| | 35\n\
  $| | 36\n\
   | | 93\n\
   | | 94\n\
   | | 95\n\
SPACE| | 96\n\
   | | 97\n\
   | | 98\n\
   | | 99\n\
   | |100\n\
   | |101\n\
   | |102\n\
   | |103\n\
   | |104\n\
  C|c|  3\n\
  D|d|  4\n\
  E|e|  5\n\
  %| | 37\n\
  &| | 38\n\
  '| | 39\n\
  (| | 40\n\
  )| | 41\n\
  *| | 42\n\
  +| | 43\n\
  ,| | 44\n\
  -| | 45\n\
  .| | 46\n\
  /| | 47\n\
  0| | 48\n\
  1| | 49\n\
  2| | 50\n\
  3| | 51\n\
  4| | 52\n\
  5| | 53\n\
  6| | 54\n\
  7| | 55\n\
  8| | 56\n\
  9| | 57\n\
  :| | 58\n\
  ;| | 59\n\
  <| | 60\n\
  =| | 61\n\
  >| | 62\n\
  ?| | 63\n\
   | | 64\n\
   | |105\n\
   | |106\n\
   | |107\n\
   | |108\n\
   | |109\n\
   | |110\n\
   | |111\n\
   | |112\n\
   | |113\n\
   | |114\n\
   | |115\n\
   | |116\n\
  F|f|  6\n\
  G|g|  7\n\
  H|h|  8\n\
   |A| 65\n\
   |B| 66\n\
   |C| 67\n\
   |D| 68\n\
   |E| 69\n\
   |F| 70\n\
   |G| 71\n\
   |H| 72\n\
   |I| 73\n\
   |J| 74\n\
   |K| 75\n\
   |L| 76\n\
   |M| 77\n\
   |N| 78\n\
   |O| 79\n\
   |P| 80\n\
   |Q| 81\n\
   |R| 82\n\
   |S| 83\n\
   |T| 84\n\
   |U| 85\n\
   |V| 86\n\
   |W| 87\n\
   |X| 88\n\
   |Y| 89\n\
   |Z| 90\n\
   | | 91\n\
   | | 92\n\
   | |117\n\
   | |118\n\
   | |119\n\
   | |120\n\
   | |121\n\
   | |122\n\
   | |123\n\
   | |124\n\
   | |125\n\
   | |126\n\
   | |127";

    QStringList lines = codes.split('\n');
    foreach (auto line, lines)
    {
        QStringList parts = line.split('|');
        if (parts.length() < 3)
            continue;
        QString p1 = parts[0].trimmed().replace("SPACE", " ");
        QString p3 = parts[2].trimmed();

        byteToChar.insert((quint8)p3.toInt(), p1.isEmpty() || p1.isNull() ? '*' : p1[0].toLatin1());
    }
}

char C64CharConverter::ConvertToAscii(quint8 value)
{
    if (byteToChar.isEmpty())
        ParseString();

    value = (quint8)(value & 127);
    return byteToChar[value];
}

}

