#include "previewwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

PreviewWindow::PreviewWindow(QWidget *parent) :
    PlayWindow(parent),
    m_flag(false),
    m_previewFlag(false)
{
    m_closeAction = new QAction(this);
    m_closeAllAction = new QAction(this);
    m_contextMenu = new QMenu();
    m_closeAction->setText("关闭预览");
    m_closeAllAction->setText("关闭所有预览");
    m_contextMenu->addAction(m_closeAction);
    m_contextMenu->addAction(m_closeAllAction);
    connect(m_closeAction, SIGNAL(triggered()), this, SIGNAL(closePreviewSig()));
    connect(m_closeAllAction, SIGNAL(triggered()), this, SIGNAL(closeAllPreviewSig()));
//    connect(m_closeAction, SIGNAL(triggered()), this, SLOT(closePreviewSlot()));
}

PreviewWindow::~PreviewWindow()
{
}

BaseWidget*  PreviewWindow::clone()
{
    PreviewWindow* tem = new PreviewWindow;
    return tem;
}

void PreviewWindow::paintWindow(bool flag)
{
    m_flag = flag;
}

QString PreviewWindow::getDvrId()
{
    return m_dvr;
}

QString PreviewWindow::getChannelId()
{
    return m_channel;
}

void PreviewWindow::setDvrId(QString dvr)
{
    m_dvr = dvr;
}

void PreviewWindow::setChannelId(QString channel)
{
    m_channel = channel;
}

void PreviewWindow::setIsPreview(bool flag)
{
    m_previewFlag = flag;
}

bool PreviewWindow::getIsPreview()
{
    qDebug() << "PreviewWindow::getIsPreview" << m_previewFlag;
    return m_previewFlag;
}

void PreviewWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "PreviewWindow::mouseDoubleClickEvent" << getIsPreview();
    QWidget::mouseDoubleClickEvent(event);
}

void PreviewWindow::mousePressEvent(QMouseEvent *event)
{
    //传递给外层的PlayScreen部件
    QWidget::mousePressEvent(event);
}

void PreviewWindow::contextMenuEvent(QContextMenuEvent *event)
{
    //event->globalPos()是以桌面为基础的坐标
    if (m_previewFlag)
    {
        m_contextMenu->exec(event->globalPos());
    }
}

void PreviewWindow::closePreviewSlot()
{
    qDebug() << "PreviewWindow::closePreviewSlot()";
    if (!m_previewFlag)
        return;
    emit closePreviewSig();
}

void PreviewWindow::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing,true);
    QLinearGradient linearGradient(rect().width(),rect().height(),0,0);

    linearGradient.setSpread(QGradient::RepeatSpread);
//    linearGradient.setColorAt(0.0, Qt::lightGray);
//    linearGradient.setColorAt(0.2, Qt::lightGray);
//    linearGradient.setColorAt(0.8, Qt::lightGray);
//    linearGradient.setColorAt(1.0, Qt::lightGray);
    linearGradient.setColorAt(0.0, QColor(237, 252, 255));
    linearGradient.setColorAt(0.2, QColor(237, 252, 255));
    linearGradient.setColorAt(0.8, QColor(237, 252, 255));
    linearGradient.setColorAt(1.0, QColor(237, 252, 255));
    if (m_flag)
    {
        linearGradient.setSpread(QGradient::RepeatSpread);
        linearGradient.setColorAt(0.0, QColor(35, 255, 17));
        linearGradient.setColorAt(0.2, QColor(35, 255, 17));
        linearGradient.setColorAt(0.8, QColor(35, 255, 17));
        linearGradient.setColorAt(1.0, QColor(35, 255, 17));
        paint.setBrush(QBrush(linearGradient));
        paint.drawRect(rect());
//        int fontSize, width, height;
//        width = rect().width();
//        height = rect().height();
//        fontSize = ( height >= width ? width : height );
//        QFont font("Comic Sans MS",fontSize/6,QFont::Bold);
//        font.setCapitalization(QFont::SmallCaps);
//        font.setLetterSpacing(QFont::AbsoluteSpacing,2);

//        paint.setRenderHint(QPainter::TextAntialiasing);
//        paint.setFont(font);
//        paint.fillRect(rect(),QBrush(linearGradient));
//        if ( height >= width )
//        {
//            paint.drawText(rect(),Qt::AlignCenter,("正\n常\n预\n览"));
//            paint.drawRect(rect());
//        }
//        else
//        {
//            paint.drawText(rect(),Qt::AlignCenter,("正常预览"));
//            paint.drawRect(rect());
//        }
    }
    else
    {
        paint.setBrush(QBrush(linearGradient));
        paint.drawRect(rect());
    }
}

void PreviewWindow::setPreviewNum(int num)
{
    m_previewNum = num;
}

int PreviewWindow::getPreviewNum()
{
    return m_previewNum;
}
