#ifndef MENUWRAPPER_H
#define MENUWRAPPER_H

#include <QObject>

class MenuWrapper : public QObject
{
    Q_OBJECT
public:
    virtual bool eventFilter(QObject *, QEvent *);

signals:
    void signalTriggered();

public slots:
};

#endif // MENUWRAPPER_H
