#ifndef FASTCONSOLE_H
#define FASTCONSOLE_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QColor>
#include <QFontMetrics>

namespace Hackathon
{
    class FastConsole : public QWidget
    {
        Q_OBJECT

        short width_;
        short height_;
        char* buffer_;
        QColor* _backColorBuffer;
        QColor* _frontColorBuffer;
        bool _dirty;
        bool _regularUpdate;
        QImage _offscreen;
        QColor _clearColor;
    public:
        FastConsole(short width, short height);

        virtual ~FastConsole();

        void setCustomFont(QFont font);

    public slots:
        void SetChar(int x, int y, char ch, QColor back, QColor front);

        void SetChar(int x, int y, char ch);

        void SetBackColor(int x, int y, QColor color);

        void SetForeColor(int x, int y, QColor foreColor);

        void slotSetClearColor(QColor color);

        short Width(){return width_;}

        short Height(){return height_;}

    private slots:
        void slotUpdate();

    protected:
        void paintEvent(QPaintEvent* e);

    private:
        int charW(QFontMetrics& fm);
        int charH(QFontMetrics& fm);

        int fmW(QFontMetrics& fm);
        int fmH(QFontMetrics& fm);

        void generateOffscreen();

    };
}

#endif
