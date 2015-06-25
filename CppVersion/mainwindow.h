#ifndef MAINWINDOW_H
#define MAINWINDOW_H

namespace Ui {
   class MainWindow;
} // namespace Ui

namespace Hackathon{
    class Emulator;
    class Prg;
    class FastConsole;
}


#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QStringList _recentFiles;
    QStringList _recentCodeFiles;
    Ui::MainWindow* _ui;
    Hackathon::FastConsole* _console;
    Hackathon::Emulator* _emulator;
    Hackathon::Prg* _program;
public:
    explicit MainWindow(QWidget *parent = 0);

    virtual ~MainWindow();

signals:
    void RunEmulator();
    void signalSetMemory(ushort, quint8);

public slots:

private slots:
    void slotRecentTriggered();
    void slotRecentCodeTriggered();
    void slotLoad();
    void on_actionStart_triggered();
    void on_actionLoad_2_triggered();

    void on_actionChange_triggered();

    void on_actionLoadCode_triggered();

    void on_hexBox_editingFinished();

    void on_hexValue_returnPressed();

    void on_hexBox_valueChanged(const QString &arg1);

private:
    void LoadRecentFiles();
    void SaveRecentFiles();
    void LoadROM(QString filename);
    void LoadCode(QString filename);

    void UpdateMemoryLabel(ushort address);
    ushort GetAddress(bool* ok);
    bool DisableMemoryEdit();
};

#endif // MAINWINDOW_H
