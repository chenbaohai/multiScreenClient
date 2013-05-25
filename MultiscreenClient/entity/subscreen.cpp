#include "subscreen.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPainter>
#include <QBitmap>
#include <QAction>
#include <QMenu>
#include <QDebug>

SubScreen::SubScreen(QWidget *parent) :
    Screen(parent)
{
    m_vector= NULL;

}

SubScreen::~SubScreen()
{

}

void SubScreen::setDisplayid(const QString &id)
{
    m_displayId = id;
    update();
}

BaseWidget *SubScreen::clone()
{
    SubScreen * temp = new SubScreen;
    return temp;
}

void SubScreen::cancelDisPlayid()
{
    m_displayId ="0";
    update();
}

void SubScreen::paintEvent(QPaintEvent *e)
{  
    if(m_displayId=="0")
    {
        Screen::paintEvent(e);
        return;
    }
    Screen::paintEvent(e);
    QLinearGradient linearGradient(rect().width(),rect().height(),0,0);


//    if (m_paintFlag)
//    {
//        linearGradient.setSpread(QGradient::RepeatSpread);
//        linearGradient.setColorAt(0.0, QColor(168, 240, 255));
//        linearGradient.setColorAt(0.2, QColor(168, 240, 255));
//        linearGradient.setColorAt(0.8, QColor(168, 240, 255));
//        linearGradient.setColorAt(1.0, QColor(168, 240, 255));
//    }
//    else
//    {
//        linearGradient.setSpread(QGradient::RepeatSpread);
//        linearGradient.setColorAt(0.0, QColor(237, 252, 255));
//        linearGradient.setColorAt(0.2, QColor(237, 252, 255));
//        linearGradient.setColorAt(0.8, QColor(237, 252, 255));
//        linearGradient.setColorAt(1.0, QColor(237, 252, 255));
////        linearGradient.setColorAt(0.0, Qt::lightGray);
////        linearGradient.setColorAt(0.2, Qt::lightGray);
////        linearGradient.setColorAt(0.8, Qt::lightGray);
////        linearGradient.setColorAt(1.0, Qt::lightGray);
//    }
    QPainter paint(this);
    QFont font("Comic Sans MS",50,QFont::Bold);
    font.setCapitalization(QFont::SmallCaps);
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);

    paint.setRenderHint(QPainter::TextAntialiasing);
    paint.setFont(font);
//    paint.fillRect(rect(),QBrush(linearGradient));
    paint.drawText(rect(),Qt::AlignCenter,m_displayId);
//    paint.drawRect(rect());
}

void SubScreen::mouseDoubleClickEvent(QMouseEvent *e)
{
    Screen::mouseDoubleClickEvent(e);
}


