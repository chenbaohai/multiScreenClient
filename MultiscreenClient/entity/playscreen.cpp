#include "playscreen.h"
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDataStream>
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>

#include "organizationtree.h"
#include "interactdata.h"

PlayScreen::PlayScreen(QWidget *parent) :
    BaseWidget(parent),
    m_closePollingFlag(false),
    m_closePreFlag(false),
    m_previewWndFlag(false),
    m_dropFlag(false),
    m_doubleClickFlag(false)
{
    m_layout = new QHBoxLayout;
    m_layoutwidget = new LayoutWidget;
    m_layout->addWidget(m_layoutwidget);
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_closePolling = new QAction(this);
    m_closePolling->setText("关闭轮巡");
    m_pollingMenu = new QMenu();
    m_pollingMenu->addAction(m_closePolling);
    connect(m_closePolling,SIGNAL(triggered()),this,SLOT(closePollingSlot()));

    setLayout(m_layout);
    setAcceptDrops(true);

    m_previewWndNum = 0;
    m_schedule="";
}

PlayScreen::~PlayScreen()
{
    delete m_layoutwidget;
    delete m_layout;
}

BaseWidget *PlayScreen::clone()
{
    PlayScreen* temp = new PlayScreen;
    return temp;
}

void PlayScreen::createPlaywindows(int row, int column, PlayWindow *win)
{
    setPreviewWndFlag(true);
    m_layoutwidget->createWidgetLayout(row,column,win);
}

void PlayScreen::closeUnnecessaryWnd()
{
    if (!(*m_layoutwidget->getDelScreenList()).isEmpty())
    {
        foreach(BaseWidget* temp, *m_layoutwidget->getDelScreenList())
        {
            PreviewWindow *pre = (PreviewWindow*)temp;
            if (pre->getIsPreview())
            {
                closePreview(pre);
            }
        }
        m_layoutwidget->delScreenList();
    }
}

void PlayScreen::setColNum(int colNum)
{
    m_colNum = colNum;
}

int PlayScreen::getColNum()
{
    return m_colNum;
}

int PlayScreen::getPreviewWndNum()
{
    return m_previewWndNum;
}

void PlayScreen::paintPreviewWindow(bool flag)
{
//    qDebug() << "PlayScreen::painterPreviewWindowSlot"<<m_previewWindow;
    m_previewWindow->paintWindow(flag);
    m_previewWindow->setIsPreview(flag);
}

int PlayScreen::calPreviewWindow(QPoint point)
{
    int row, col, previewWindowNum;
    m_layoutwidget->setPaintFlag(false);
    m_layoutwidget->selectScreenWidget(point);
    m_previewWindow = (PreviewWindow*)m_layoutwidget->selectScreen();
    if (m_previewWindow == NULL)
    {
        QMessageBox::information(this, "Warning", "请设置预览窗口", tr("确定"));
        return 0;
    }
    qDebug() << "PlayScreen::calPreviewWindow" << m_previewWindow;

    row = m_layoutwidget->selectScreen()->row();
    col = m_layoutwidget->selectScreen()->column();
    previewWindowNum = m_colNum * (row - 1) + col;
    m_previewWindow->setPreviewNum(previewWindowNum);
    return previewWindowNum;
}

void PlayScreen::dragEnterEvent(QDragEnterEvent *event)
{
//    if (event->mimeData()->hasFormat("application/x-qt-cbh"))
    {
        event->acceptProposedAction();
    }
}

void PlayScreen::dropEvent(QDropEvent *event)
{
    qDebug() << "PlayScreen::dropEvent " << event->pos();

    if (event->mimeData()->hasFormat("screencontrolwidget/preview"))
    {
        emit sendCurrentScreenSig(this);
        int previewWindowNum;
        if (!m_previewWndFlag)
        {
//            m_previewWindow = new PreviewWindow;
//            createPlaywindows(1, 1, m_previewWindow);
//            emit sendDefaultPreScreenSig(this, 1);
//            m_previewWindow->setPreviewNum(1);
//            previewWindowNum = 1;
            emit sendDefaultPreScreenSig(this, 1);
        }
//        else
//        {

        previewWindowNum = calPreviewWindow(event->pos());
//        }

        if (previewWindowNum == 0)
            return;
//        m_previewWndNum.append(previewWindowNum);
        m_previewWndNum = previewWindowNum;
    //    qDebug() << "m_previewWindow->getIsPreview()" << m_previewWindow->getIsPreview();
        if (m_previewWindow->getIsPreview())
        {
            emit sendPreviewScreenSig(NULL);
            return;
        }
        connect(m_previewWindow, SIGNAL(closePreviewSig()), this, SLOT(closePreviewSlot()));
        connect(m_previewWindow, SIGNAL(closeAllPreviewSig()), this, SLOT(closeAllPreviewSlot()));
        QByteArray itemData = event->mimeData()->data("screencontrolwidget/preview");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        qint64 channelId, dvrId;
        QString tempStr = displayId();

        dataStream >> channelId >> dvrId;

        QString channelStr = QString::number(channelId, 10);
        QString dvrStr = QString::number(dvrId, 10);

        m_previewWindow->setDvrId(dvrStr);
        m_previewWindow->setChannelId(channelStr);

        tempStr += "," + dvrStr;
        tempStr += "," + channelStr;
        tempStr += "," + QString::number(previewWindowNum, 10);
        //tempStr中DVR与Channel按顺序写入与解析
//        qDebug() << "application/x-qt-cbh" << channelId << dvrId << tempStr << displayId() << dvrStr << channelStr;
        emit sendPreviewScreenSig(tempStr);
    }
    if (event->mimeData()->hasFormat("PollingSchemeWidget/circulate"))
    {
        if (m_dropFlag)
        {
            QMessageBox::information(this, "Warning", "该屏正在轮巡，请先关闭",tr("确定"));
            return;
        }
        m_schedule = "";
        m_dropFlag = true;
        QByteArray itemData = event->mimeData()->data("PollingSchemeWidget/circulate");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QString schedulename;
        QString tempStr = displayId();

        dataStream >> schedulename;

        tempStr += "," + schedulename;

        m_schedule = tempStr;

        emit sendCirculateSig(tempStr,true);
        qDebug()<<"PlayScreen::dropEvent->"<<tempStr;
    }
}

void PlayScreen::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        qDebug() << "PlayScreen::mousePressEvent" << event->pos();
        m_point = event->pos();
    }
    else
    {
        BaseWidget::mousePressEvent(event);
    }
}

void PlayScreen::closePreviewSlot()
{
    int previewWindowNum;
    if (m_closePreFlag)
    {
        previewWindowNum = m_previewWindow->getPreviewNum();
        m_closePreFlag = false;
    }
    else
    {
        previewWindowNum = calPreviewWindow(m_point);
    }

//    int previewWindowNum = m_previewWindow->getPreviewNum();
    if (previewWindowNum == 0)
        return;
//    m_previewWndNum.removeOne(previewWindowNum);
    QString tempStr = m_previewWindow->getDvrId();
    tempStr += "," + m_previewWindow->getChannelId();
    tempStr += ":" + displayId();
    tempStr += "," + QString::number(previewWindowNum, 10);
    qDebug() << "PlayScreen::closePreviewSlot" << displayId() << tempStr << m_previewWindow->getIsPreview();
//    m_previewWindow->setIsPreview(false);
//    qDebug()<<"Set WindowStatus:false->"<<m_previewWindow;
//    qDebug() << m_previewWindow->getIsPreview();

    paintPreviewWindow(false);
    update();
    emit closePreviewWindowSig(tempStr);
}

void PlayScreen::closePollingSlot()
{
    qDebug() << "PlayScreen::closePollingSlot";
    if(m_schedule == "")
        return;
    m_dropFlag = false;
    emit sendCirculateSig(m_schedule,false);
    update();
}

void PlayScreen::mouseDoubleClickEvent(QMouseEvent *e)
{
    int flag;
    if (m_doubleClickFlag)
    {
        m_doubleClickFlag = false;
        foreach(BaseWidget *temp, *this->m_layoutwidget->ScreenList())
        {
            temp->setDoubleClick(false);
            temp->showNormal();
        }
        flag = 0;
    }
    else
    {
        m_previewWndNum = calPreviewWindow(e->pos());
        foreach(BaseWidget *temp, *this->m_layoutwidget->ScreenList())
        {
            if (m_previewWindow != (PreviewWindow*)temp)
            {
                temp->setDoubleClick(true);
                temp->hide();
            }
        }
        flag = 1;
        qDebug() << "PlayScreen::mouseDoubleClickEvent displayId = " << displayId() << " m_previewWndNum = " << m_previewWndNum;

        m_doubleClickFlag = true;
    }
    m_layoutwidget->changeScreen();
    QString tempStr = displayId();
    tempStr += "," + QString::number(m_previewWndNum, 10);
    tempStr += "," + QString::number(flag, 10);
    emit(sendFullPreviewSig(tempStr));
}

void PlayScreen::paintEvent(QPaintEvent *e)
{
    BaseWidget::paintEvent(e);
//    QPainter paint(this);
//    paint.setRenderHint(QPainter::Antialiasing,true);
//    QLinearGradient linearGradient(rect().width(),rect().height(),0,0);

    if (m_dropFlag)
    {
        QPainter paint(this);
//        paint.setRenderHint(QPainter::Antialiasing,true);
//        QLinearGradient linearGradient(rect().width(),rect().height(),0,0);
//        linearGradient.setSpread(QGradient::RepeatSpread);
//        linearGradient.setColorAt(0.0, QColor(35, 255, 17));
//        linearGradient.setColorAt(0.2, QColor(35, 255, 17));
//        linearGradient.setColorAt(0.8, QColor(35, 255, 17));
//        linearGradient.setColorAt(1.0, QColor(35, 255, 17));
//        paint.setBrush(QBrush(linearGradient));
//        paint.drawRect(rect());

        QFont font("Comic Sans MS",rect().width()/6,QFont::Bold);
        font.setCapitalization(QFont::SmallCaps);
        font.setLetterSpacing(QFont::AbsoluteSpacing,2);

        paint.setRenderHint(QPainter::TextAntialiasing);
        paint.setFont(font);
//        paint.fillRect(rect(),QBrush(linearGradient));
        paint.drawText(rect(),Qt::AlignCenter,m_schedule);
        paint.drawRect(rect());
    }
//    else
//    {
//        linearGradient.setSpread(QGradient::RepeatSpread);
//        linearGradient.setColorAt(0.0, Qt::lightGray);
//        linearGradient.setColorAt(0.2, Qt::lightGray);
//        linearGradient.setColorAt(0.8, Qt::lightGray);
//        linearGradient.setColorAt(1.0, Qt::lightGray);
//    }
//    paint.setBrush(QBrush(linearGradient));
//    paint.drawRect(rect());
}

void PlayScreen::contextMenuEvent(QContextMenuEvent *event)
{
    if (m_closePollingFlag)
    {
        m_pollingMenu->exec(event->globalPos());
    }
}

void PlayScreen::setClosePollingFlag(bool flag)
{
    m_closePollingFlag = flag;
}

LayoutWidget * PlayScreen::getPreviewWndLayout()
{
    return m_layoutwidget;
}

void PlayScreen::closePreview(PreviewWindow *preWnd)
{
    m_closePreFlag = true;
    m_previewWindow = preWnd;
    closePreviewSlot();
}

void PlayScreen::closeCirculate()
{
    closePollingSlot();
}

void PlayScreen::setPreviewWndFlag(bool flag)
{
    m_previewWndFlag = true;
}

void PlayScreen::closeAllPreviewSlot()
{
    emit closeAllPreviewWndSig(this);
}

