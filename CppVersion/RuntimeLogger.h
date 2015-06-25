#ifndef RUNTIMELOGGER_H
#define RUNTIMELOGGER_H

#include <QString>

#include "AssemblyInstructions.h"

#ifdef _LOG_
    #define LOGBYTE(value)  Logger.Log(QString(" : %1").arg(value)); \
                            Logger.Log(CpuStatusRegisters());

    #define LOGATOB(val1, val2) Logger.Log(QString(" : %1 => %2").arg(val1).arg(val2));
                                Logger.Log(CpuStatusRegisters());

    #define LOGGER_CLOSE Logger.Close();

    #define LOG_STATUSREGISTERS Logger.Log(CpuStatusRegisters());

    #define LOG(string) Logger.Log(string)
#else
    #define LOGBYTE(value)
    #define LOGATOB(val1, val2)
    #define LOGGER_CLOSE
    #define LOG_STATUSREGISTERS
    #define LOG(string)
#endif


namespace Hackathon
{
    class RuntimeLogger
	{
//		QString File { get; set; }
//		StreamWriter Writer { get; set; }
//		List<string> Messages { get; set; }
//		private string Line;
//		private object _sync = new object();
    public:
        bool Enabled;

        RuntimeLogger(QString file);

        void Log(Hackathon::AssemblyInstruction& instruction);

        void Close();

        void Log(ushort address);

        void Log(quint8 binary);

        void Log(QString instruction);

        void NewLine();

        void Log(QString format, quint8 instructionCode);

    private:
        void Flush();
    };
}

#endif
