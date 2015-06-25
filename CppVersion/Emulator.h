#ifndef EMULATOR_H
#define EMULATOR_H

#include <QObject>
#include <QMap>
#include <QThread>

#include "Prg.h"
#include "Memory.h"
#include "Registers.h"
#include "RuntimeLogger.h"
#include "AssemblyInstructions.h"

namespace Hackathon
{
    class Emulator : public QThread
	{
        Q_OBJECT

        typedef void (Emulator::*func)(AddressingMode);

        QMap<AssemblyInstructionType, func> _actions;
        Memory _memory;
        Registers _registers;
        RuntimeLogger Logger;
        bool Break;
        int ExecutionCounter;

    public:
        Memory& Memory();

        Emulator();

        void SetStartAddress(quint16 address);

    public slots:
        void Run();
        void Run(Prg* program, bool skipLoad = false);
        void KeyPressed(int key);

    private slots:

    private:
        virtual void run();

        quint16 AddressTransform(std::auto_ptr<quint8> address, AddressingMode mode);

        void BranchOnCondition(AddressingMode mode, bool conditionExpression);

        void Compare(quint8 left, AddressingMode mode);

        std::auto_ptr<quint8> GetArguments(AddressingMode mode);

        void IncrementCounter();

        void Interrupt();

        void SetZeroNegative(quint8 data);

        quint8 CpuStatusRegisters();

        void Execute();

        void ADC(AddressingMode mode);

        void AND(AddressingMode mode);

        void ASL(AddressingMode mode);

        quint8 ASL(quint8 value);

        void BCC(AddressingMode obj);

        void BCS(AddressingMode mode);

        void BEQ(AddressingMode mode);

        void BIT(AddressingMode mode);

        void BMI(AddressingMode obj);

        void BNE(AddressingMode mode);

        void BPL(AddressingMode mode);

        void BRK(AddressingMode mode);

        void BVC(AddressingMode mode);

        void BVS(AddressingMode obj);

        void CLC(AddressingMode obj);

        void CLD(AddressingMode obj);

        void CLI(AddressingMode obj);

        void CLV(AddressingMode obj);

        void CMP(AddressingMode mode);

        void CPX(AddressingMode mode);

        void CPY(AddressingMode mode);

        void DEC(AddressingMode obj);

        void DEX(AddressingMode obj);

        void DEY(AddressingMode mode);

        void EOR(AddressingMode mode);

        void INC(AddressingMode mode);

        void INX(AddressingMode arg2);

        void INY(AddressingMode arg2);

        void JMP(AddressingMode mode);

        void JSR(AddressingMode mode);

        void LDA(AddressingMode mode);

        void LDX(AddressingMode mode);

        void LDY(AddressingMode mode);

        void LSR(AddressingMode mode);

        quint8 LSR(quint8 value);

        void NOP(AddressingMode obj);

        void ORA(AddressingMode obj);

        void PHA(AddressingMode obj);

        void PHP(AddressingMode obj);

        void PLA(AddressingMode obj);

        void PLP(AddressingMode obj);

        void ROL(AddressingMode mode);

        quint8 ROL(quint8 value);

        void ROR(AddressingMode mode);

        quint8 ROR(quint8 value);

        void RTI(AddressingMode obj);

        void RTS(AddressingMode mode);

        void SBC(AddressingMode mode);

        void SEC(AddressingMode obj);

        void SED(AddressingMode obj);

        void SEI(AddressingMode obj);
		
        void STA(AddressingMode mode);

        void STX(AddressingMode mode);

        void STY(AddressingMode mode);

        void TAX(AddressingMode obj);

        void TAY(AddressingMode arg2);

        void TSX(AddressingMode obj);

        void TXA(AddressingMode obj);

        void TXS(AddressingMode obj);
		
        void TYA(AddressingMode arg2);

    };
}

#endif
