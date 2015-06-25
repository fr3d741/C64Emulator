#include <QPainter>
#include <QFontMetrics>
#include <QFont>
#include <QTimer>

#include "FastConsole.h"


namespace Hackathon
{

FastConsole::FastConsole(short width, short height)
    :QWidget()
    ,width_(width)
    ,height_(height)
    ,_dirty(false)
    ,_regularUpdate(false)
    ,_clearColor(Qt::black)
{
    QFont font;
    font.setFamily("Fixedsys");
    font.setPixelSize(12);
    font.setStyleHint(QFont::Monospace);
    setFont(font);
    QFontMetrics fm = fontMetrics();
    int w = charW(fm);
    int h = charH(fm);
    setFixedWidth(w);
    setFixedHeight(h);
    setFocusPolicy(Qt::StrongFocus);

    _offscreen = QImage(w, h, QImage::Format_ARGB32);

    buffer_ = new char[width * height];
    _backColorBuffer = new QColor[width * height];
    _frontColorBuffer = new QColor[width * height];

    QTimer* timer = new QTimer(this);
    timer->setInterval(40);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), SLOT(slotUpdate()));
    timer->start();
}

FastConsole::~FastConsole()
{
    delete[] buffer_;
}

void FastConsole::setCustomFont(QFont font)
{
    setFont(font);

    QFontMetrics fm(font);
    int w = charW(fm);
    int h = charH(fm);
    setFixedWidth(w);
    setFixedHeight(h);
    setFocusPolicy(Qt::StrongFocus);

    _offscreen = QImage(w, h, QImage::Format_ARGB32);
    _dirty = true;
    update();
}

void FastConsole::SetChar(int x, int y, char ch, QColor back, QColor front)
{
    buffer_[x + width_ * y] = ch;
    _backColorBuffer[x + width_ * y] = back;
    _frontColorBuffer[x + width_ * y] = front;
    _dirty = true;
    update();

}

void FastConsole::SetChar(int x, int y, char ch)
{
    buffer_[x + width_ * y] = ch;
    _dirty = true;
    update();
}

void FastConsole::SetBackColor(int x, int y, QColor color)
{
    _backColorBuffer[x + width_ * y] = color;
    _dirty = true;
    update();
}

void FastConsole::SetForeColor(int x, int y, QColor foreColor)
{
    _frontColorBuffer[x + width_ * y] = foreColor;
    _dirty = true;
    update();
}

void FastConsole::slotSetClearColor(QColor color)
{
    _clearColor = color;
    _dirty = true;
    update();
}

void FastConsole::slotUpdate()
{
    _regularUpdate = true;
    update();
}

void FastConsole::paintEvent(QPaintEvent*)
{
    if (!_regularUpdate)
        return;

    _regularUpdate = false;

    if (_dirty)
    {
        QPainter painter(this);
        generateOffscreen();
        painter.drawImage(rect(),_offscreen);
    }
}

int FastConsole::charW(QFontMetrics &fm)
{
    return fmW(fm) * width_;
}

int FastConsole::charH(QFontMetrics &fm)
{
    return fmH(fm) * height_;
}

int FastConsole::fmW(QFontMetrics &fm)
{
    return fm.averageCharWidth();
}

int FastConsole::fmH(QFontMetrics &fm)
{
    return fm.height();
}

void FastConsole::generateOffscreen()
{
    QPainter painter(&_offscreen);
    QFontMetrics fm = fontMetrics();
    int w = fmW(fm);
    int h = fmH(fm);
    _offscreen.fill(_clearColor);

    QTextOption option;
    option.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    int yc = h;
    for (short i = 0; i < height_; ++i, yc+=h)
    {
        int y = i * width_;
        int xc = 0;
        for (short j = 0; j < width_; ++j, xc+=w)
        {
            char c = buffer_[y + j];
            QBrush brush(_backColorBuffer[y + j]);
            QPen pen(_frontColorBuffer[y + j]);
            painter.setBackground(brush);
            painter.setPen(pen);
            QRect r(xc, yc - h, w, h);
            //painter.drawText(xc, yc, QString("%1").arg(c));
            painter.drawText(r, QString("%1").arg(c), option);
        }
    }
}

}
