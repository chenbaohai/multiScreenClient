#include "playerlayout.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

PlayerLayout::PlayerLayout(QWidget *parent) :
    LayoutWidget(parent)
{

}

PlayerLayout::~PlayerLayout()
{

}

void PlayerLayout::mousePressEvent(QMouseEvent *event)
{
    m_startPoint = event->pos();
    selectScreenWidget(m_startPoint);
    qDebug() << "PlayerLayout::mousePressEvent" << m_startPoint;
}

//void PlayerLayout::paintEvent(QPaintEvent *)
//{
//    if (m_curwidget)
//    {
//        qDebug() << m_curwidget << "m_curwidget PlayerLayout::paintEvent";
//        QPainter paint(this);
//        paint.setPen(QPen(QColor(255,0,0),2,Qt::SolidLine,Qt::RoundCap));
//        paint.drawRect(m_curwidget->x(),
//                         m_curwidget->y(),
//                         m_curwidget->width(),
//                         m_curwidget->height());
//    }
//}
