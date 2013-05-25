#include "screen.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Screen::Screen(QWidget *parent) :
   m_isMerged(false),
   BaseWidget(parent)
{

}

Screen::~Screen()
{

}

BaseWidget *Screen::clone()
{
    Screen * temp = new Screen;
    return temp;
}

bool Screen::isMerged()
{
    return m_isMerged;
}

void Screen::setIsMerge(bool is)
{
    m_isMerged = is;
}

QList<Screen *> *Screen::getMergeList()
{
    return &m_mergeList;
}

void Screen::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing,true);
    QLinearGradient linearGradient(rect().width(),rect().height(),0,0);
    linearGradient.setSpread(QGradient::RepeatSpread);

    if (m_paintFlag)
    {
        linearGradient.setSpread(QGradient::RepeatSpread);
        linearGradient.setColorAt(0.0, QColor(168, 240, 255));
        linearGradient.setColorAt(0.2, QColor(168, 240, 255));
        linearGradient.setColorAt(0.8, QColor(168, 240, 255));
        linearGradient.setColorAt(1.0, QColor(168, 240, 255));
    }
    else
    {
        linearGradient.setSpread(QGradient::RepeatSpread); //

        linearGradient.setColorAt(0.0, QColor(237, 252, 255));
        linearGradient.setColorAt(0.2, QColor(237, 252, 255));
        linearGradient.setColorAt(0.8, QColor(237, 252, 255));
        linearGradient.setColorAt(1.0, QColor(237, 252, 255));
//        linearGradient.setColorAt(0.0, Qt::lightGray);
//        linearGradient.setColorAt(0.2, Qt::lightGray);
//        linearGradient.setColorAt(0.8, Qt::lightGray);
//        linearGradient.setColorAt(1.0, Qt::lightGray);
    }

    paint.setBrush(QBrush(linearGradient));
    paint.drawRect(rect());
}

void Screen::mouseDoubleClickEvent(QMouseEvent * e)
{
    qDebug() << "Screen::mouseDoubleClickEvent";
    if(!m_isMerged)
        return;
    foreach(Screen* temp,m_mergeList)
    {
        temp->setUseflag(true);
    }
    m_mergeList.clear();
    emit changeSpanSignal(this);
}
