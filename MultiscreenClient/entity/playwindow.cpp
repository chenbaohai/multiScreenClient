#include "playwindow.h"
#include <QPainter>

PlayWindow::PlayWindow(QWidget *parent) :
    BaseWidget(parent)
{
}

PlayWindow::~PlayWindow()
{
}

//void PlayWindow::paintEvent(QPaintEvent *e)
//{
//    QPainter paint(this);
//    paint.setRenderHint(QPainter::Antialiasing,true);
//    QLinearGradient linearGradient(rect().width(),rect().height(),0,0);

//    linearGradient.setSpread(QGradient::RepeatSpread);
//    linearGradient.setColorAt(0.0, Qt::lightGray);
//    linearGradient.setColorAt(0.2, Qt::lightGray);
//    linearGradient.setColorAt(0.8, Qt::lightGray);
//    linearGradient.setColorAt(1.0, Qt::lightGray);
//    paint.setBrush(QBrush(linearGradient));
//    paint.drawRect(rect());
//}

void PlayWindow::enterEvent(QEvent *)
{
}
