#include <cassert>
#include <QDebug>

#include "Emulator.h"
#include "KeyboardWatcher.h"
#include "utils.h"

namespace Hackathon
{

Memory& Emulator::Memory()
{
    return _memory;
}

Emulator::Emulator()
    :QThread()
    ,_actions()
    ,_memory()
    ,_registers()
    ,Logger("execution.log")
    ,Break(false)
    ,ExecutionCounter(0)
{
    _actions[AssemblyInstructionType::ADC] = &Hackathon::Emulator::ADC;
    _actions[AssemblyInstructionType::AND] = &Hackathon::Emulator::AND;
    _actions[AssemblyInstructionType::ASL] = &Hackathon::Emulator::ASL;

    _actions[AssemblyInstructionType::BCC] = &Hackathon::Emulator::BCC;
    _actions[AssemblyInstructionType::BCS] = &Hackathon::Emulator::BCS;
    _actions[AssemblyInstructionType::BEQ] = &Hackathon::Emulator::BEQ;
    _actions[AssemblyInstructionType::BIT] = &Hackathon::Emulator::BIT;
    _actions[AssemblyInstructionType::BMI] = &Hackathon::Emulator::BMI;
    _actions[AssemblyInstructionType::BNE] = &Hackathon::Emulator::BNE;
    _actions[AssemblyInstructionType::BPL] = &Hackathon::Emulator::BPL;
    _actions[AssemblyInstructionType::BRK] = &Hackathon::Emulator::BRK;
    _actions[AssemblyInstructionType::BVC] = &Hackathon::Emulator::BVC;
    _actions[AssemblyInstructionType::BVS] = &Hackathon::Emulator::BVS;

    _actions[AssemblyInstructionType::CLC] = &Hackathon::Emulator::CLC;
    _actions[AssemblyInstructionType::CLD] = &Hackathon::Emulator::CLD;
    _actions[AssemblyInstructionType::CLI] = &Hackathon::Emulator::CLI;
    _actions[AssemblyInstructionType::CLV] = &Hackathon::Emulator::CLV;
    _actions[AssemblyInstructionType::CMP] = &Hackathon::Emulator::CMP;
    _actions[AssemblyInstructionType::CPX] = &Hackathon::Emulator::CPX;
    _actions[AssemblyInstructionType::CPY] = &Hackathon::Emulator::CPY;

    _actions[AssemblyInstructionType::DEC] = &Hackathon::Emulator::DEC;
    _actions[AssemblyInstructionType::DEY] = &Hackathon::Emulator::DEY;
    _actions[AssemblyInstructionType::DEX] = &Hackathon::Emulator::DEX;

    _actions[AssemblyInstructionType::EOR] = &Hackathon::Emulator::EOR;

    _actions[AssemblyInstructionType::INC] = &Hackathon::Emulator::INC;
    _actions[AssemblyInstructionType::INX] = &Hackathon::Emulator::INX;
    _actions[AssemblyInstructionType::INY] = &Hackathon::Emulator::INY;


    _actions[AssemblyInstructionType::JSR] = &Hackathon::Emulator::JSR;
    _actions[AssemblyInstructionType::JMP] = &Hackathon::Emulator::JMP;

    _actions[AssemblyInstructionType::LDA] = &Hackathon::Emulator::LDA;
    _actions[AssemblyInstructionType::LDX] = &Hackathon::Emulator::LDX;
    _actions[AssemblyInstructionType::LDY] = &Hackathon::Emulator::LDY;
    _actions[AssemblyInstructionType::LSR] = &Hackathon::Emulator::LSR;

    _actions[AssemblyInstructionType::NOP] = &Hackathon::Emulator::NOP;

    _actions[AssemblyInstructionType::ORA] = &Hackathon::Emulator::ORA;

    _actions[AssemblyInstructionType::PHA] = &Hackathon::Emulator::PHA;
    _actions[AssemblyInstructionType::PHP] = &Hackathon::Emulator::PHP;
    _actions[AssemblyInstructionType::PLP] = &Hackathon::Emulator::PLP;
    _actions[AssemblyInstructionType::PLA] = &Hackathon::Emulator::PLA;

    _actions[AssemblyInstructionType::ROL] = &Hackathon::Emulator::ROL;
    _actions[AssemblyInstructionType::ROR] = &Hackathon::Emulator::ROR;
    _actions[AssemblyInstructionType::RTS] = &Hackathon::Emulator::RTS;
    _actions[AssemblyInstructionType::RTI] = &Hackathon::Emulator::RTI;

    _actions[AssemblyInstructionType::SBC] = &Hackathon::Emulator::SBC;
    _actions[AssemblyInstructionType::SEC] = &Hackathon::Emulator::SEC;
    _actions[AssemblyInstructionType::SED] = &Hackathon::Emulator::SED;
    _actions[AssemblyInstructionType::SEI] = &Hackathon::Emulator::SEI;
    _actions[AssemblyInstructionType::STA] = &Hackathon::Emulator::STA;
    _actions[AssemblyInstructionType::STX] = &Hackathon::Emulator::STX;
    _actions[AssemblyInstructionType::STY] = &Hackathon::Emulator::STY;


    _actions[AssemblyInstructionType::TAX] = &Hackathon::Emulator::TAX;
    _actions[AssemblyInstructionType::TAY] = &Hackathon::Emulator::TAY;
    _actions[AssemblyInstructionType::TSX] = &Hackathon::Emulator::TSX;
    _actions[AssemblyInstructionType::TXA] = &Hackathon::Emulator::TXA;
    _actions[AssemblyInstructionType::TXS] = &Hackathon::Emulator::TXS;
    _actions[AssemblyInstructionType::TYA] = &Hackathon::Emulator::TYA;
}

void Emulator::SetStartAddress(quint16 address)
{
    _registers.ProgramCounter = address;
}

ushort Emulator::AddressTransform(std::auto_ptr<quint8> auto_address, AddressingMode mode)
{
    quint8* address = auto_address.get();
    switch (mode)
    {
        case AddressingMode::Implied:
            throw new std::exception();
        case AddressingMode::IndexedIndirectX:
            {
                auto zeroAddress = address[0] + _registers.IndexX;
                quint8 resultAddress[] = { _memory.GetByte(zeroAddress), _memory.GetByte(++zeroAddress) };
                return Utils::ConvertToInt(resultAddress);
            }
        case AddressingMode::IndirectIndexedY:
            {
                auto zeroPageValue1 = _memory.GetByte(address[0]) + _registers.IndexY;
                auto zeroPageValue2 = _memory.GetByte(address[0] + 1);
                if (255 < zeroPageValue1)
                {
                    zeroPageValue1 = zeroPageValue1 & 0xFF;
                    ++zeroPageValue2;
                }

                quint8 resultAddress[] = { (quint8)zeroPageValue1, zeroPageValue2 };
                return Utils::ConvertToInt(resultAddress);
            }
        case AddressingMode::Indirect:
            {
                auto localAddress = Utils::ConvertToInt(address);
                quint8 resultAddress[] = { _memory.GetByte(localAddress), _memory.GetByte(++localAddress) };
                return Utils::ConvertToInt(resultAddress);
            }
        case AddressingMode::Absolute:
            return Utils::ConvertToInt(address);
        case AddressingMode::AbsoluteX:
            return (ushort)(Utils::ConvertToInt(address) + _registers.IndexX);
        case AddressingMode::AbsoluteY:
            return (ushort)(Utils::ConvertToInt(address) + _registers.IndexY);
        case AddressingMode::Immediate:
            return address[0];
        case AddressingMode::ZeroPage:
            return Utils::ConvertToInt(address[0]);
        case AddressingMode::ZeroPageX:
            return (ushort)(Utils::ConvertToInt(address[0]) + _registers.IndexX);
        case AddressingMode::ZeroPageY:
            return (ushort)(Utils::ConvertToInt(address[0]) + _registers.IndexY);
        case AddressingMode::Accumulator:
            return 0;
        case AddressingMode::Relative:
        default:
            throw new std::exception("mode");
    }


}

void Emulator::KeyPressed(int key)
{
    //KeyboardWatcher* sndr = dynamic_cast<KeyboardWatcher*>(sender());
    //assert(sndr);

    auto num = _memory.GetByte(0xC6);
    if (num == 10)
    {
        //Console.Beep();
        printf("\a");
        qDebug() << "Keyboard buffer is full";
        return;
    }

    _memory.SetByte(0x0277 + num, (quint8)key);
    _memory.SetByte(0xC6, ++num);
}

void Emulator::run()
{
    Run();
}

void Emulator::Run(Prg* program, bool skipLoad)
{
    //auto watcher = new KeyboardWatcher();
    //watcher.KeyPressed += KeyPressed;

    ExecutionCounter = 0;
    //Logger.Enabled = false;

    Break = false;
    _registers.ProgramCounter = program->StartAddress;

    if (skipLoad == false)
        _memory.LoadProgram(*program);

    while (Break == false)
    {
        Execute();
    }
    LOGGER_CLOSE
}

void Emulator::Run()
{
    ExecutionCounter = 0;

    Break = false;

    while (Break == false)
    {
        Execute();
    }
    LOGGER_CLOSE
}

void Emulator::BranchOnCondition(AddressingMode mode, bool conditionExpression)
{
    //Only used by branching commands
    auto arg1 = GetArguments(mode);
    auto variable = (quint16)arg1.get()[0];
    if (128 < variable) variable = (ushort)(variable - 255);
    else variable += 1;

    if (conditionExpression)
        _registers.ProgramCounter += variable;
    else
        IncrementCounter();

    LOG_STATUSREGISTERS
}

void Emulator::Compare(quint8 left, AddressingMode mode)
{
    auto arg1 = AddressTransform(GetArguments(mode), mode);
    quint8 data;

    if (mode == AddressingMode::Immediate)
        data = (quint8)arg1;
    else
        data = _memory.GetByte(arg1);

    _registers.ZeroFlag		= left == data;
    _registers.NegativeFlag = left < data;
    _registers.CarryFlag	= data <= left;

    LOG(QString(" : %1 <=> %2").arg(QString(QString(left).toLatin1().toHex())).arg(QString(QString(data).toLatin1().toHex())));
    LOG_STATUSREGISTERS
}

std::auto_ptr<quint8> Emulator::GetArguments(AddressingMode mode)
{
    switch (mode)
    {
        case AddressingMode::Immediate:
        case AddressingMode::ZeroPage:
        case AddressingMode::ZeroPageX:
        case AddressingMode::ZeroPageY:
        case AddressingMode::Accumulator:
        case AddressingMode::Relative:
        case AddressingMode::Implied:
        case AddressingMode::IndexedIndirectX:
        case AddressingMode::IndirectIndexedY:
            return std::auto_ptr<quint8>(new quint8[2] { _memory.GetByte(++_registers.ProgramCounter) });
        case AddressingMode::Indirect:
        case AddressingMode::Absolute:
        case AddressingMode::AbsoluteX:
        case AddressingMode::AbsoluteY:
            return std::auto_ptr<quint8>(new quint8[2] { _memory.GetByte(++_registers.ProgramCounter), _memory.GetByte(++_registers.ProgramCounter) });
        default:
            throw new std::exception("mode");
    }
}

void Emulator::IncrementCounter()
{
    _registers.ProgramCounter++;
}

void Emulator::Interrupt()
{
    if (_registers.InterruptFlag)
        return;

    auto low = (quint8)_registers.ProgramCounter;
    auto high = (quint8)(_registers.ProgramCounter >> 8);
    _memory.Stack.Push(low);
    _memory.Stack.Push(high);


    quint8 cpuStatus = 0;
    cpuStatus = (quint8)(cpuStatus | (_registers.NegativeFlag ? 0x80 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.OverflowFlag ? 0x40 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.BrkCommand ? 0x10 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.DecimalFlag ? 0x08 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.InterruptFlag ? 0x04 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.ZeroFlag ? 0x02 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.CarryFlag ? 0x01 : 0x00));
    _memory.Stack.Push(cpuStatus);

    _registers.ProgramCounter = 0xFF48;
}

void Emulator::SetZeroNegative(quint8 data)
{
    _registers.ZeroFlag = data == 0;
    _registers.NegativeFlag = 0 < (data & 0x80);
}

quint8 Emulator::CpuStatusRegisters()
{
    quint8 cpuStatus = 0x0;
    cpuStatus = (quint8)(cpuStatus | (_registers.NegativeFlag ? 0x80 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.OverflowFlag ? 0x40 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.BrkCommand ? 0x10 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.DecimalFlag ? 0x08 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.InterruptFlag ? 0x04 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.ZeroFlag ? 0x02 : 0x00));
    cpuStatus = (quint8)(cpuStatus | (_registers.CarryFlag ? 0x01 : 0x00));
    return cpuStatus;
}

void Emulator::Execute()
{
    auto tmp = _registers.ProgramCounter;
    auto instructionCode = _memory.GetByte(_registers.ProgramCounter);
    auto instruction = AssemblyInstructions::GetInstruction(instructionCode);

    Logger.Log(tmp);
    Logger.Log(" : {0:X2} : ", instructionCode);
    Logger.Log(instruction);

    func ptr = _actions[instruction.InstructionType()];
    (this->*ptr)(instruction.AddressingMode());
    Logger.NewLine();
    if (ExecutionCounter == 10000)
    {
        ExecutionCounter = 0;
        Interrupt();
    }
    ExecutionCounter++;
    //msleep(35);
}

void Emulator::ADC(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    quint8 value;
    if (mode == AddressingMode::Immediate)
        value = (quint8)address;
    else
        value = _memory.GetByte(address);

    auto oldA = _registers.Accumulator;
    auto result = _registers.Accumulator + value + (_registers.CarryFlag ? 1 : 0);

    _registers.CarryFlag = 255 < result;
    _registers.Accumulator = (quint8)result;
    _registers.OverflowFlag = (_registers.Accumulator & 0x80) != (oldA & 0x80);

    SetZeroNegative(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::AND(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    if (mode == AddressingMode::Immediate)
        _registers.Accumulator = (quint8)(_registers.Accumulator & address);
    else
        _registers.Accumulator = (quint8)(_registers.Accumulator & _memory.GetByte(address));

    SetZeroNegative(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::ASL(AddressingMode mode)
{
    if (mode == AddressingMode::Accumulator)
    {
        _registers.Accumulator = ASL(_registers.Accumulator);
    }
    else
    {
        auto address = AddressTransform(GetArguments(mode), mode);
        auto value = _memory.GetByte(address);
        value = ASL(value);
        _memory.SetByte(address, value);
    }
    IncrementCounter();

    LOG_STATUSREGISTERS
}

quint8 Emulator::ASL(quint8 value)
{
    _registers.CarryFlag = 0 < (value & 0x80);
    value = (quint8) (value << 1);
    SetZeroNegative(value);

    LOG(QString(" : %1").arg(value));
    return value;
}

void Emulator::BCC(AddressingMode obj)
{
    BranchOnCondition(obj, _registers.CarryFlag == false);
}

void Emulator::BCS(AddressingMode mode)
{
    BranchOnCondition(mode, _registers.CarryFlag);
}

void Emulator::BEQ(AddressingMode mode)
{
    BranchOnCondition(mode, _registers.ZeroFlag);
}

void Emulator::BIT(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    auto value = _memory.GetByte(address);
    _registers.OverflowFlag = 0 < (value & 0x40);
    _registers.NegativeFlag = 0 < (value & 0x80);
    _registers.ZeroFlag = (value & _registers.Accumulator) == 0;
    IncrementCounter();

    LOG_STATUSREGISTERS
}

void Emulator::BMI(AddressingMode obj)
{
    BranchOnCondition(obj, _registers.NegativeFlag);
}

void Emulator::BNE(AddressingMode mode)
{
    BranchOnCondition(mode, _registers.ZeroFlag == false);
}

void Emulator::BPL(AddressingMode mode)
{
    BranchOnCondition(mode, _registers.NegativeFlag == false);
}

void Emulator::BRK(AddressingMode)
{
    Break = true;
}

void Emulator::BVC(AddressingMode mode)
{
    BranchOnCondition(mode, _registers.OverflowFlag == false);
}

void Emulator::BVS(AddressingMode obj)
{
    BranchOnCondition(obj, _registers.OverflowFlag);
}

void Emulator::CLC(AddressingMode)
{
    _registers.CarryFlag = false;
    IncrementCounter();
}

void Emulator::CLD(AddressingMode)
{
    _registers.DecimalFlag = false;
    IncrementCounter();
}

void Emulator::CLI(AddressingMode)
{
    _registers.InterruptFlag = false;
    IncrementCounter();
}

void Emulator::CLV(AddressingMode)
{
    _registers.OverflowFlag = false;
    IncrementCounter();
}

void Emulator::CMP(AddressingMode mode)
{
    Compare(_registers.Accumulator, mode);
    IncrementCounter();
}

void Emulator::CPX(AddressingMode mode)
{
    Compare(_registers.IndexX, mode);
    IncrementCounter();
}

void Emulator::CPY(AddressingMode mode)
{
    Compare(_registers.IndexY, mode);
    IncrementCounter();
}

void Emulator::DEC(AddressingMode obj)
{
    auto address = AddressTransform(GetArguments(obj), obj);
    auto value = _memory.GetByte(address);
    value--;
    _memory.SetByte(address, value);
    SetZeroNegative(value);
    IncrementCounter();

    LOGBYTE(value);
}

void Emulator::DEX(AddressingMode)
{
    _registers.IndexX--;
    SetZeroNegative(_registers.IndexX);
    IncrementCounter();

    LOGBYTE(_registers.IndexX);
}

void Emulator::DEY(AddressingMode)
{
    _registers.IndexY--;
    SetZeroNegative(_registers.IndexY);
    IncrementCounter();

    LOGBYTE(_registers.IndexY);
}

void Emulator::EOR(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    quint8 data;
    if (mode == AddressingMode::Immediate)
        data = (quint8)address;
    else
        data = _memory.GetByte(address);

    _registers.Accumulator = (quint8)(_registers.Accumulator ^ data);
    SetZeroNegative(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::INC(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    auto value = _memory.GetByte(address);
    ++value;
    _memory.SetByte(address, value);

    SetZeroNegative(value);
    IncrementCounter();

    LOGBYTE(value);
}

void Emulator::INX(AddressingMode)
{
    _registers.IndexX++;
    SetZeroNegative(_registers.IndexX);
    IncrementCounter();

    LOGBYTE(_registers.IndexX);
}

void Emulator::INY(AddressingMode)
{
    _registers.IndexY++;
    SetZeroNegative(_registers.IndexY);
    IncrementCounter();

    LOGBYTE(_registers.IndexY);
}

void Emulator::JMP(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    _registers.ProgramCounter = address;
}

void Emulator::JSR(AddressingMode mode)
{
    std::auto_ptr<quint8> address = GetArguments(mode);
    auto cim = Utils::ConvertToInt(address);

    auto low = (quint8)_registers.ProgramCounter;
    auto high = (quint8)(_registers.ProgramCounter >> 8);
    _memory.Stack.Push(high);
    _memory.Stack.Push(low);
    _registers.ProgramCounter = cim;
}

void Emulator::LDA(AddressingMode mode)
{
    auto data = AddressTransform(GetArguments(mode), mode);
    if (mode == AddressingMode::Immediate)
        _registers.Accumulator = (quint8)data;
    else
        _registers.Accumulator = _memory.GetByte(data);

    SetZeroNegative(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::LDX(AddressingMode mode)
{
    auto data = AddressTransform(GetArguments(mode), mode);
    if (mode == AddressingMode::Immediate)
        _registers.IndexX = (quint8)data;
    else
        _registers.IndexX = _memory.GetByte(data);

    SetZeroNegative(_registers.IndexX);
    IncrementCounter();

    LOGBYTE(_registers.IndexX);
}

void Emulator::LDY(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    if (mode == AddressingMode::Immediate)
        _registers.IndexY = (quint8)address;
    else
        _registers.IndexY = _memory.GetByte(address);

    SetZeroNegative(_registers.IndexY);
    IncrementCounter();

    LOGBYTE(_registers.IndexY);
}

void Emulator::LSR(AddressingMode mode)
{
    if (mode == AddressingMode::Accumulator)
    {
        _registers.Accumulator = LSR(_registers.Accumulator);
    }
    else
    {
        auto address = AddressTransform(GetArguments(mode), mode);
        auto value = _memory.GetByte(address);
        value = LSR(value);
        _memory.SetByte(address, value);
    }
    _registers.NegativeFlag = false;

    IncrementCounter();

    LOG_STATUSREGISTERS
}

quint8 Emulator::LSR(quint8 value)
{
    _registers.CarryFlag = 0 < (value & 0x01);
    value = (quint8) (value >> 1);
    SetZeroNegative(value);

    LOG(QString(" : %1").arg(value));
    return value;
}

void Emulator::NOP(AddressingMode)
{
    IncrementCounter();
}

void Emulator::ORA(AddressingMode obj)
{
    auto address = AddressTransform(GetArguments(obj), obj);
    quint8 data;
    if (obj == AddressingMode::Immediate)
        data = (quint8)address;
    else
        data = _memory.GetByte(address);

    _registers.Accumulator = (quint8)(_registers.Accumulator | data);

    SetZeroNegative(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::PHA(AddressingMode)
{
    _memory.Stack.Push(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::PHP(AddressingMode)
{
    quint8 cpuStatus = CpuStatusRegisters();

    _memory.Stack.Push(cpuStatus);
    IncrementCounter();

    LOG_STATUSREGISTERS
}

void Emulator::PLA(AddressingMode)
{
    _registers.Accumulator = _memory.Stack.Pop();
    //Needs to check. Doesn't appear in any documentation
    SetZeroNegative(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::PLP(AddressingMode)
{
    auto status = _memory.Stack.Pop();
    _registers.NegativeFlag = 0 < (status & 0x80);
    _registers.OverflowFlag = 0 < (status & 0x40);
    _registers.BrkCommand = 0 < (status & 0x10);
    _registers.DecimalFlag = 0 < (status & 0x08);
    _registers.InterruptFlag = 0 < (status & 0x04);
    _registers.ZeroFlag = 0 < (status & 0x02);
    _registers.CarryFlag = 0 < (status & 0x01);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::ROL(AddressingMode mode)
{
    if (mode == AddressingMode::Accumulator)
        _registers.Accumulator = ROL(_registers.Accumulator);
    else
    {
        auto address = AddressTransform(GetArguments(mode), mode);
        auto value = _memory.GetByte(address);

        value = ROL(value);
        _memory.SetByte(address, value);
    }
    IncrementCounter();
}

quint8 Emulator::ROL(quint8 value)
{
    auto carryBit = 0 < (value & 0x80);
    value = (quint8) ((quint8) (value << 1) | (_registers.CarryFlag ? 0x01 : 0x00));
    _registers.CarryFlag = carryBit;

    SetZeroNegative(value);
    LOGBYTE(value);
    return value;
}

void Emulator::ROR(AddressingMode mode)
{
    if (mode == AddressingMode::Accumulator)
        _registers.Accumulator = ROR(_registers.Accumulator);
    else
    {
        auto address = AddressTransform(GetArguments(mode), mode);
        auto value = _memory.GetByte(address);

        value = ROR(value);
        _memory.SetByte(address, value);
    }
    IncrementCounter();
}

quint8 Emulator::ROR(quint8 value)
{
    auto carryBit = 0 < (value & 0x01);
    value = (quint8) ((quint8) (value >> 1) | (_registers.CarryFlag ? 0x80 : 0x00));
    _registers.CarryFlag = carryBit;

    SetZeroNegative(value);
    LOGBYTE(value);
    return value;
}

void Emulator::RTI(AddressingMode)
{
    auto status = _memory.Stack.Pop();
    _registers.NegativeFlag = 0 < (status & 0x80);
    _registers.OverflowFlag = 0 < (status & 0x40);
    _registers.BrkCommand = 0 < (status & 0x10);
    _registers.DecimalFlag = 0 < (status & 0x08);
    _registers.InterruptFlag = 0 < (status & 0x04);
    _registers.ZeroFlag = 0 < (status & 0x02);
    _registers.CarryFlag = 0 < (status & 0x01);

    auto high = _memory.Stack.Pop();
    auto low = _memory.Stack.Pop();

    auto address = (high << 8) | low;
    _registers.ProgramCounter = (ushort)address;
}

void Emulator::RTS(AddressingMode)
{
    auto low = _memory.Stack.Pop();
    auto high = _memory.Stack.Pop();
    auto address = (high << 8) | low;
    _registers.ProgramCounter = (ushort)(address + 1);
}

void Emulator::SBC(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    quint8 data;
    _registers.OverflowFlag = false;

    if (mode == AddressingMode::Immediate)
        data = (quint8)address;
    else
        data = _memory.GetByte(address);

    auto oldA = _registers.Accumulator;
    auto value = (_registers.Accumulator - data - (_registers.CarryFlag ? 0 : 1));
    _registers.OverflowFlag = (_registers.Accumulator & 0x80) != (oldA & 0x80); ;

    _registers.CarryFlag = 0 <= value;

    _registers.Accumulator = (quint8)value;

    SetZeroNegative(_registers.Accumulator);

    IncrementCounter();

    LOGATOB(oldA, _registers.Accumulator);
}

void Emulator::SEC(AddressingMode)
{
    _registers.CarryFlag = true;
    IncrementCounter();
}

void Emulator::SED(AddressingMode)
{
    _registers.DecimalFlag = true;
    IncrementCounter();
}

void Emulator::SEI(AddressingMode)
{
    _registers.InterruptFlag = true;
    IncrementCounter();
}

void Emulator::STA(AddressingMode mode)
{
    //No flags set
    auto address = AddressTransform(GetArguments(mode), mode);
    _memory.SetByte(address, _registers.Accumulator);
    IncrementCounter();

    LOGATOB(_registers.Accumulator, address);
}

void Emulator::STX(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    _memory.SetByte(address, _registers.IndexX);
    IncrementCounter();

    LOGATOB(_registers.IndexX, address);
}

void Emulator::STY(AddressingMode mode)
{
    auto address = AddressTransform(GetArguments(mode), mode);
    _memory.SetByte(address, _registers.IndexY);
    IncrementCounter();

    LOGATOB(_registers.IndexY, address);
}

void Emulator::TAX(AddressingMode)
{
    _registers.IndexX = _registers.Accumulator;
    SetZeroNegative(_registers.IndexX);
    IncrementCounter();

    LOGBYTE(_registers.IndexX);
}

void Emulator::TAY(AddressingMode)
{
    _registers.IndexY = _registers.Accumulator;
    SetZeroNegative(_registers.IndexY);
    IncrementCounter();

    LOGBYTE(_registers.IndexY);
}

void Emulator::TSX(AddressingMode)
{
    _registers.IndexX = _memory.Stack.Pointer;
    SetZeroNegative(_registers.IndexX);
    IncrementCounter();

    LOGBYTE(_registers.IndexX);
}

void Emulator::TXA(AddressingMode)
{
    _registers.Accumulator = _registers.IndexX;
    SetZeroNegative(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

void Emulator::TXS(AddressingMode)
{
    _memory.Stack.Pointer = _registers.IndexX;
    IncrementCounter();

    LOGBYTE(_memory.Stack.Pointer);
}

void Emulator::TYA(AddressingMode)
{
    _registers.Accumulator = _registers.IndexY;
    SetZeroNegative(_registers.Accumulator);
    IncrementCounter();

    LOGBYTE(_registers.Accumulator);
}

}
