#ifndef KEYBOARDWATCHER_H
#define KEYBOARDWATCHER_H

#include <QObject>

namespace Hackathon
{
    class KeyboardWatcher : public QObject
	{
        Q_OBJECT
        int _lastKeyPressed;
    public:
        virtual bool eventFilter(QObject *, QEvent *);

        int LastKeyPressed();

    signals:
        void signalKeyPressed(int);

    public slots:
    };
}

#endif
