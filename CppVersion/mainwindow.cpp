#include <cassert>
#include <QDebug>
#include <QHBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QFontDialog>

#include "mainwindow.h"
#include "Prg.h"
#include "Emulator.h"
#include "FastConsole.h"
#include "KeyboardWatcher.h"
#include "menuwrapper.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,_recentFiles()
    ,_ui(new Ui::MainWindow())
    ,_console(0)
    ,_emulator(new Hackathon::Emulator())
    ,_program(0)
{
    _ui->setupUi(this);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QWidget* widget = _ui->containerWidget;
    QHBoxLayout* layout = new QHBoxLayout();
    widget->setLayout(layout);

    _console = new Hackathon::FastConsole(40, 25);
    layout->addWidget(_console);

    Hackathon::KeyboardWatcher* watcher = new Hackathon::KeyboardWatcher();
    watcher->setParent(this);
    _console->installEventFilter(watcher);
    connect(&_emulator->Memory(), SIGNAL(signalSetClearColor(QColor)),                  _console, SLOT(slotSetClearColor(QColor)), Qt::QueuedConnection);
    connect(&_emulator->Memory(), SIGNAL(signalSetChar(int,int,char,QColor,QColor)),    _console, SLOT(SetChar(int,int,char,QColor,QColor)), Qt::QueuedConnection);
    connect(this, SIGNAL(signalSetMemory(ushort,quint8)),                   &_emulator->Memory(), SLOT(slotSetMemory(ushort,quint8)), Qt::QueuedConnection);
    connect(watcher, SIGNAL(signalKeyPressed(int)),     _emulator, SLOT(KeyPressed(int)), Qt::QueuedConnection);
    connect(this, SIGNAL(RunEmulator()),                _emulator, SLOT(Run()), Qt::QueuedConnection);

    LoadRecentFiles();
}

MainWindow::~MainWindow()
{
    delete _ui;
    SaveRecentFiles();
}

void MainWindow::LoadRecentFiles()
{
    QFile file("recent.txt");
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen())
        return;

    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        QString line = stream.readLine();
        _ui->menuLoad->addAction(line, this, SLOT(slotRecentTriggered()));
        _recentFiles.push_back(line);
    }

    QFile fileCode("recentFiles.txt");
    fileCode.open(QIODevice::ReadOnly);
    if (!fileCode.isOpen())
        return;

    QTextStream streamCode(&fileCode);
    while(!streamCode.atEnd())
    {
        QString line = streamCode.readLine();
        _ui->menuRecent_files->addAction(line, this, SLOT(slotRecentCodeTriggered()));
        _recentCodeFiles.push_back(line);
    }

}

void MainWindow::SaveRecentFiles()
{
    QFile file("recent.txt");
    file.open(QIODevice::WriteOnly);
    if (!file.isOpen())
        return;

    QTextStream stream(&file);
    while(!_recentFiles.isEmpty())
        stream << _recentFiles.takeFirst() << "\n";

    QFile file2("recentFiles.txt");
    file2.open(QIODevice::WriteOnly);
    if (!file2.isOpen())
        return;

    QTextStream stream2(&file2);
    while(!_recentCodeFiles.isEmpty())
        stream2 << _recentCodeFiles.takeFirst() << "\n";
}

void MainWindow::slotRecentTriggered()
{
    QAction* sndr = reinterpret_cast<QAction*>(sender());
    LoadROM(sndr->text());
}

void MainWindow::slotRecentCodeTriggered()
{
    QAction* sndr = reinterpret_cast<QAction*>(sender());
    LoadCode(sndr->text());
}

void MainWindow::LoadROM(QString filename)
{
    _program = new Hackathon::Prg();
    _program->Open(filename);
    _program->StartAddress = 0xFCE2;

    _emulator->SetStartAddress(0xFCE2);
    _emulator->Memory().LoadProgram(*_program, 0xA000, 0, 8192);
    _emulator->Memory().LoadProgram(*_program, 0xE000, 8192, 8192);
}

void MainWindow::LoadCode(QString filename)
{
    _program = new Hackathon::Prg(filename);
    _emulator->Memory().LoadProgram(*_program);
    _emulator->SetStartAddress(_program->StartAddress);
    _emulator->start();
}

void MainWindow::slotLoad()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select the C64 ROM");
    if (filename.isEmpty() || filename.isNull())
        return;

    if (!_recentFiles.contains(filename))
        _recentFiles.push_front(filename);

    LoadROM(filename);
}

void MainWindow::on_actionStart_triggered()
{
    _emulator->start();
}


void MainWindow::on_actionLoad_2_triggered()
{
    slotLoad();
}

void MainWindow::on_actionChange_triggered()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok, _console->font(), this, "Select a font", QFontDialog::MonospacedFonts);
    if (ok)
    {
        _console->setCustomFont(f);
    }
}

void MainWindow::on_actionLoadCode_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select the byte code to run");
    if (filename.isEmpty() || filename.isNull())
        return;

    if (!_recentCodeFiles.contains(filename))
        _recentCodeFiles.push_front(filename);

    LoadCode(filename);
}

void MainWindow::UpdateMemoryLabel(ushort address)
{
    quint8 byte = _emulator->Memory().GetByte(address);
    auto s = QString("0x%1").arg(QString(QString(byte).toLatin1().toHex()));
    _ui->hexValue->setText(s);
    _ui->hexValue->setEnabled(true);
}

ushort MainWindow::GetAddress(bool *ok)
{
    return (ushort)_ui->hexBox->text().toInt(ok, 16);
}

bool MainWindow::DisableMemoryEdit()
{
    _ui->hexValue->setText("ERR");
    _ui->hexValue->setEnabled(false);

return true;
}

void MainWindow::on_hexBox_editingFinished()
{
    bool ok = false;
    ushort address = GetAddress(&ok);

    if (!ok)
        DisableMemoryEdit();
    else
        UpdateMemoryLabel(address);
}

void MainWindow::on_hexValue_returnPressed()
{
    bool ok = false;
    ushort address = GetAddress(&ok);
    if (!ok && DisableMemoryEdit())
        return;

    QString hexValue = _ui->hexValue->text();
    quint8 value = (quint8)hexValue.toUInt(&ok, 16);
    if (!ok)
        UpdateMemoryLabel(address);
    else
        emit signalSetMemory(address,value);
}

void MainWindow::on_hexBox_valueChanged(const QString &arg1)
{
    bool ok = false;
    ushort address = GetAddress(&ok);
    if (!ok)
        DisableMemoryEdit();
    else
        UpdateMemoryLabel(address);
}
