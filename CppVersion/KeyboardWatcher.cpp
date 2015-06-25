#include <QEvent>
#include <QKeyEvent>

#include "KeyboardWatcher.h"
#include "C64CharConverter.h"

namespace Hackathon {

//#include <QObject>

//namespace Hackathon
//{
//    class KeyboardWatcher : public QObject
//	{
////		private object _sync = new object();

////		public event EventHandler KeyPressed;
////		public ConsoleKeyInfo LastConsoleKeyInfo { get; private set; }

////		protected virtual void OnKeyPressed()
////		{
////			var handler = KeyPressed;
////			if (handler != null) handler(this, EventArgs.Empty);
////		}

////		public KeyboardWatcher()
////		{
////			var th = new Thread(WatcherOnTheWall);
////			th.Start();
////		}

////		private void WatcherOnTheWall()
////		{
////			for (; ; )
////			{
////				lock (_sync)
////				{
////					if (Console.KeyAvailable)
////					{
////						LastConsoleKeyInfo = Console.ReadKey(true);
////						OnKeyPressed();
////					}
////				}

////				Thread.Sleep(50);
////			}

////		}
//    };
//}


bool KeyboardWatcher::eventFilter(QObject *, QEvent *e)
{
    int t = e->type();
    if (t == QEvent::KeyPress)
    {
        QKeyEvent* event = reinterpret_cast<QKeyEvent*>(e);
        QString txt = event->text();
        if (txt.isEmpty() || txt.isNull())
            return false;

        _lastKeyPressed = txt.toUpper().toLatin1().at(0);
        emit signalKeyPressed(_lastKeyPressed);
    }

    return false;
}

int KeyboardWatcher::LastKeyPressed()
{
    return _lastKeyPressed;
}

} //Hackathon
