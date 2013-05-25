#include "rectangle.h"
#include "ui_rectangle.h"
#include <QPainter>
#include <QBitmap>

rectangle::rectangle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rectangle)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint|Qt::Tool);
    this->setGeometry(0,0,0,0);
}

rectangle::~rectangle()
{
    delete ui;
}

void rectangle::paintEvent(QPaintEvent *)
{
    QBitmap bmp (this->rect().width(), this->height());
    QPainter paint(&bmp);
    QPen pen(Qt::black);
    pen.setWidth(4);
    paint.setPen(pen);
    paint.setBrush(Qt::white);
    paint.drawRect(1,1,bmp.rect().width()-2, bmp.rect().height()-2);
    this->setMask(bmp);
    bmp.save("c:/1.bmp");
}
