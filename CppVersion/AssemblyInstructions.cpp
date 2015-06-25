#include "AssemblyInstructions.h"

namespace Hackathon
{
QVector<AssemblyInstruction> AssemblyInstructions::Codes;

AssemblyInstruction AssemblyInstructions::GetInstruction(quint8 code)
{
    if (Codes.isEmpty())
        InitCodes();

    return Codes[code];
}


void AssemblyInstructions::InitCodes()
{
    //Codes.reserve(0xFF);
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BRK, AddressingMode::Implied));  // 00 - BRK
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ORA, AddressingMode::IndexedIndirectX));   // 01 - ORA - (Indirect,X)
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 02 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 03 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 04 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ORA, AddressingMode::ZeroPage));   // 05 - ORA - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ASL, AddressingMode::ZeroPage));   // 06 - ASL - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 07 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::PHP, AddressingMode::Implied));   // 08 - PHP
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ORA, AddressingMode::Immediate));   // 09 - ORA - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ASL, AddressingMode::Accumulator));   // 0A - ASL - Accumulator
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 0B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 0C - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ORA, AddressingMode::Absolute));   // 0D - ORA - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ASL, AddressingMode::Absolute));   // 0E - ASL - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 0F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BPL, AddressingMode::Relative));   // 10 - BPL
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ORA, AddressingMode::IndirectIndexedY));  //11 - ORA - (Indirect),Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 12 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 13 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 14 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ORA, AddressingMode::ZeroPageX));   //15 - ORA - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ASL, AddressingMode::ZeroPageX));   //16 - ASL - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 17 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CLC, AddressingMode::Implied));   //18 - CLC
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ORA, AddressingMode::AbsoluteY));   //19 - ORA - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 1A - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 1B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 1C - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ORA, AddressingMode::AbsoluteX));   //1D - ORA - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ASL, AddressingMode::AbsoluteX));   //1E - ASL - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 1F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::JSR, AddressingMode::Absolute));   //20 - JSR
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::AND, AddressingMode::IndexedIndirectX));   //21 - AND - (Indirect,X)
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 22 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 23 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BIT, AddressingMode::ZeroPage));   // 24 - BIT - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::AND, AddressingMode::ZeroPage));   //25 - AND - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROL, AddressingMode::ZeroPage));   //26 - ROL - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 27 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::PLP, AddressingMode::Implied));   // 28 - PLP
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::AND, AddressingMode::Immediate));   //29 - AND - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROL, AddressingMode::Accumulator));   //2A - ROL - Accumulator
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 2B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BIT, AddressingMode::Absolute));   //2C - BIT - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::AND, AddressingMode::Absolute));   //2D - AND - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROL, AddressingMode::Absolute));   //2E - ROL - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 2F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BMI, AddressingMode::Relative));   //30 - BMI
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::AND, AddressingMode::IndirectIndexedY));   //31 - AND - (Indirect),Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 32 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 33 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 34 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::AND, AddressingMode::ZeroPageX));   // 35 - AND - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROL, AddressingMode::ZeroPageX));   //36 - ROL - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 37 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SEC, AddressingMode::Implied));   //38 - SEC
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::AND, AddressingMode::AbsoluteY));   //39 - AND - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 3A - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 3B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 3C - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::AND, AddressingMode::AbsoluteX));   //3D - AND - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROL, AddressingMode::AbsoluteX));   //3E - ROL - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 3F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::RTI, AddressingMode::Implied));   //40 - RTI
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::EOR, AddressingMode::IndexedIndirectX));  //41 - EOR - (Indirect,X)
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 42 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 43 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 44 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::EOR, AddressingMode::ZeroPage));   //45 - EOR - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LSR, AddressingMode::ZeroPage));   //46 - LSR - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 47 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::PHA, AddressingMode::Implied));   //48 - PHA
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::EOR, AddressingMode::Immediate));   //49 - EOR - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LSR, AddressingMode::Accumulator));   //4A - LSR - Accumulator
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 4B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::JMP, AddressingMode::Absolute));   //4C - JMP - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::EOR, AddressingMode::Absolute));   //4D - EOR - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LSR, AddressingMode::Absolute));   //4E - LSR - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 4F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BVC, AddressingMode::Relative));   //50 - BVC
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::EOR, AddressingMode::IndirectIndexedY));  //51 - EOR - (Indirect),Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 52 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 53 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 54 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::EOR, AddressingMode::ZeroPageX));   //55 - EOR - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LSR, AddressingMode::ZeroPageX));   //56 - LSR - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 57 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CLI, AddressingMode::Implied));   //58 - CLI
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::EOR, AddressingMode::AbsoluteY));   //59 - EOR - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 5A - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 5B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 5C - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::EOR, AddressingMode::AbsoluteX));   //50 - EOR - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LSR, AddressingMode::AbsoluteX));   //5E - LSR - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 5F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::RTS, AddressingMode::Implied));   //60 - RTS
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ADC, AddressingMode::IndexedIndirectX));   //61 - ADC - (Indirect,X)
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 62 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 63 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 64 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ADC, AddressingMode::ZeroPage));   //65 - ADC - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROR, AddressingMode::ZeroPage));   //66 - ROR - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 67 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::PLA, AddressingMode::Implied));   //68 - PLA
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ADC, AddressingMode::Immediate));   //69 - ADC - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROR, AddressingMode::Accumulator));   //6A - ROR - Accumulator
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 6B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::JMP, AddressingMode::Indirect));    //6C - JMP - Indirect
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ADC, AddressingMode::Absolute));   //6D - ADC - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROR, AddressingMode::Absolute));   //6E - ROR - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 6F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BVS, AddressingMode::Relative));   //70 - BVS
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ADC, AddressingMode::IndirectIndexedY));   //71 - ADC - (Indirect),Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 72 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 73 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 74 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ADC, AddressingMode::ZeroPageX));   //75 - ADC - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROR, AddressingMode::ZeroPageX));   //76 - ROR - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 77 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SEI, AddressingMode::Implied));   //78 - SEI
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ADC, AddressingMode::AbsoluteY));   //79 - ADC - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 7A - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 7B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 7C - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ADC, AddressingMode::AbsoluteX));   //7D - ADC - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::ROR, AddressingMode::AbsoluteX));   //7E - ROR - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 7F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 80 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STA, AddressingMode::IndexedIndirectX));//81 - STA - (Indirect,X)
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 82 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 83 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STY, AddressingMode::ZeroPage));   //84 - STY - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STA, AddressingMode::ZeroPage));   //85 - STA - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STX, AddressingMode::ZeroPage));   //86 - STX - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 87 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::DEY, AddressingMode::Implied));   //88 - DEY
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 89 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::TXA, AddressingMode::Implied));   //8A - TXA
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 8B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STY, AddressingMode::Absolute));   //8C - STY - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STA, AddressingMode::Absolute));   //8D - STA - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STX, AddressingMode::Absolute));   //8E - STX - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 8F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BCC, AddressingMode::Relative));   //90 - BCC
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STA, AddressingMode::IndirectIndexedY));//91 - STA - (Indirect),Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 92 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 93 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STY, AddressingMode::ZeroPageX));   //94 - STY - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STA, AddressingMode::ZeroPageX));   //95 - STA - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STX, AddressingMode::ZeroPageY));   //96 - STX - Zero Page,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 97 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::TYA, AddressingMode::Implied));   //98 - TYA
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STA, AddressingMode::AbsoluteY));   //99 - STA - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::TXS, AddressingMode::Implied));   //9A - TXS
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 9B - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 9C - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::STA, AddressingMode::AbsoluteX));   //90 - STA - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 9E - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // 9F - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDY, AddressingMode::Immediate));   //A0 - LDY - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDA, AddressingMode::IndexedIndirectX));   //A1 - LDA - (Indirect,X)
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDX, AddressingMode::Immediate));   //A2 - LDX - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // A3 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDY, AddressingMode::ZeroPage));   //A4 - LDY - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDA, AddressingMode::ZeroPage));   //A5 - LDA - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDX, AddressingMode::ZeroPage));   //A6 - LDX - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // A7 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::TAY, AddressingMode::Implied));   //A8 - TAY
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDA, AddressingMode::Immediate));   //A9 - LDA - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::TAX, AddressingMode::Implied));   //AA - TAX
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // AB - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDY, AddressingMode::Absolute));   //AC - LDY - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDA, AddressingMode::Absolute));   //AD - LDA - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDX, AddressingMode::Absolute));   //AE - LDX - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // AF - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BCS, AddressingMode::Relative));   //B0 - BCS
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDA, AddressingMode::IndirectIndexedY));   //B1 - LDA - (Indirect),Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // B2 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // B3 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDY, AddressingMode::ZeroPageX));   //B4 - LDY - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDA, AddressingMode::ZeroPageX));   //B5 - LDA - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDX, AddressingMode::ZeroPageY));   //B6 - LDX - Zero Page,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // B7 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CLV, AddressingMode::Implied));   //B8 - CLV
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDA, AddressingMode::AbsoluteY));   //B9 - LDA - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::TSX, AddressingMode::Implied));   //BA - TSX
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // BB - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDY, AddressingMode::AbsoluteX));   //BC - LDY - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDA, AddressingMode::AbsoluteX));   //BD - LDA - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::LDX, AddressingMode::AbsoluteY));   //BE - LDX - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // BF - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CPY, AddressingMode::Immediate));   //C0 - Cpy - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CMP, AddressingMode::IndexedIndirectX)); //C1 - CMP - (Indirect,X)
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // C2 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // C3 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CPY, AddressingMode::ZeroPage));   // C4 - CPY - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CMP, AddressingMode::ZeroPage));   // C5 - CMP - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::DEC, AddressingMode::ZeroPage));   // C6 - DEC - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // C7 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::INY, AddressingMode::Implied));   // C8 - INY
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CMP, AddressingMode::Immediate));   // C9 - CMP - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::DEX, AddressingMode::Implied));   // CA - DEX
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // CB - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CPY, AddressingMode::Absolute));   // CC - CPY - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CMP, AddressingMode::Absolute));   // CD - CMP - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::DEC, AddressingMode::Absolute));   // CE - DEC - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // CF - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BNE, AddressingMode::Relative));   // D0 - BNE
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CMP, AddressingMode::IndirectIndexedY)); //D1 - CMP   (Indirect@,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // D2 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // D3 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // D4 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CMP, AddressingMode::ZeroPageX));   // D5 - CMP - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::DEC, AddressingMode::ZeroPageX));   // D6 - DEC - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // D7 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CLD, AddressingMode::Implied));   //D8 - CLD
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CMP, AddressingMode::AbsoluteY));   //D9 - CMP - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // DA - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // DB - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // DC - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CMP, AddressingMode::AbsoluteX));   //DD - CMP - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::DEC, AddressingMode::AbsoluteX));   //DE - DEC - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // DF - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CPX, AddressingMode::Immediate));   //E0 - CPX - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SBC, AddressingMode::IndexedIndirectX));   //E1 - SBC - (Indirect,X)
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // E2 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // E3 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CPX, AddressingMode::ZeroPage));   //E4 - CPX - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SBC, AddressingMode::ZeroPage));   //E5 - SBC - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::INC, AddressingMode::ZeroPage));   //E6 - INC - Zero Page
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // E7 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::INX, AddressingMode::Implied));   // E8 - INX
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SBC, AddressingMode::Immediate));   // E9 - SBC - Immediate
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::NOP, AddressingMode::Implied));   // EA - NOP
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // EB - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::CPX, AddressingMode::Absolute));   //EC - CPX - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SBC, AddressingMode::Absolute));   //ED - SBC - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::INC, AddressingMode::Absolute));   //EE - INC - Absolute
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // EF - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::BEQ, AddressingMode::Relative));   //F0 - BEQ
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SBC, AddressingMode::IndirectIndexedY));   //F1 - SBC - (Indirect),Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // F2 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // F3 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // F4 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SBC, AddressingMode::ZeroPageX));   //F5 - SBC - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::INC, AddressingMode::ZeroPageX));   // F6 - INC - Zero Page,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // F7 - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SED, AddressingMode::Implied));   //F8 - SED
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SBC, AddressingMode::AbsoluteY));   // F9 - SBC - Absolute,Y
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // FA - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // FB - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // FC - Future Expansion
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::SBC, AddressingMode::AbsoluteX));   //FD - SBC - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::INC, AddressingMode::AbsoluteX));   // FE - INC - Absolute,X
    Codes.push_back(AssemblyInstruction(AssemblyInstructionType::UNDEF, AddressingMode::Implied));   // FF - Future Expansion
}

}
