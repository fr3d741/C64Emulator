#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //var program = new Prg(args[0]);
    //var emu = new Emulator();
    //emu.Run(program);
//    auto program = new Prg();
//    program.Open(argv[0]);
//    program.StartAddress = 0xFCE2;

//    auto emu = new Emulator();
//    emu.Memory.LoadProgram(program, 0xA000, 0, 8192);
//    emu.Memory.LoadProgram(program, 0xE000, 8192, 8192);
//    emu.Run(program, true);


    return a.exec();
}
