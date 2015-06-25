#include "RuntimeLogger.h"

namespace Hackathon
{

RuntimeLogger::RuntimeLogger(QString file)
{
//			Enabled = true;
//			File = file;
//			Writer = new StreamWriter(File) {AutoFlush = true};
//			Messages = new List<string>();

//			var th = new Thread(Flush);
//			th.Start();
}

void RuntimeLogger::Log(Hackathon::AssemblyInstruction&)
{
//			if (Enabled)
//				Line += string.Format("[{0}:{1}]", instruction.InstructionType, instruction.AddressingMode);
}

void RuntimeLogger::Close()
{
//			if (Enabled)
//			{
//			}
//			Writer.Close();
}

void RuntimeLogger::Log(ushort)
{
//			if (Enabled)
//				Line += string.Format("0x{0:X4}", address);
}

void RuntimeLogger::Log(quint8)
{
//			if (Enabled)
//				Line += " : " + Convert.ToString(binary, 2).PadLeft(8, '0');
}

void RuntimeLogger::Log(QString)
{
//			if (Enabled)
//				Line += instruction;
}

void RuntimeLogger::NewLine()
{
//			if (!Enabled)
//				return;

//			Messages.Add(Line);
//			Line = "";
}

void RuntimeLogger::Log(QString, quint8)
{
//			if (Enabled)
//				Line += string.Format(format, instructionCode);
}

void RuntimeLogger::Flush()
{
//			var flush = false;
//			for (;;)
//			{
//				lock (_sync)
//				{
//					if (100000 < Messages.Count)
//					{
//						foreach (var message in Messages)
//							Writer.WriteLine(message);

//						Messages.Clear();
//						flush = true;
//					}
//				}


//				if (flush)
//				{
//					flush = false;
//					Writer.Flush();
//				}

//				Thread.Sleep(500);
//			}
}

}

