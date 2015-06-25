#include <QEvent>

#include "menuwrapper.h"

bool MenuWrapper::eventFilter(QObject *, QEvent *e)
{
    if (e->type() == QEvent::KeyRelease)
    {
        emit signalTriggered();
    }

return false;
}
