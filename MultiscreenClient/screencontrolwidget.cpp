#include "screencontrolwidget.h"
#include "ui_screencontrolwidget.h"

#include "organizationtree.h"
#include "previewwindow.h"
#include "configxml.h"
#include "msocket.h"
#include "interactdata.h"
#include "channel.h"
#include "skinmanager.h"
#include "mergexml.h"
#include "mergeitem.h"
#include <QDir>
#include <QList>
#include <QDragEnterEvent>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>
#include <qmath.h>

ScreenControlWidget::ScreenControlWidget(QWidget *parent) :
    QWidget(parent),
    m_show(1),
    ui(new Ui::ScreenControlWidget)
{
    ui->setupUi(this);
    ui->orgTreewidget->showTree();
    this->setAttribute(Qt::WA_StyledBackground);

    m_saveMsg.clear();

//    createPreviewWindow();
    connect(ui->windowToolBar, SIGNAL(setPreviewWindowSig(int)), this, SLOT(setPreviewWindowSlot(int)));

    connect(this, SIGNAL(paintPreviewScreenFontSig()), this, SLOT(paintPreviewScreenFontSlot()));
    connect(ui->orgTreewidget, SIGNAL(pressChannelSig(QTreeWidgetItem*,int)), this, SLOT(pressChannelSlot(QTreeWidgetItem*,int)));
    connect(ui->screenLayout, SIGNAL(selectedScreenSignal(BaseWidget*)), this, SLOT(paintScreen(BaseWidget*)));

//    initScreenLayout();
}

ScreenControlWidget::~ScreenControlWidget()
{
    delete ui;
    m_saveMsg.clear();
}

void ScreenControlWidget::initScreenLayout()
{
    QDir file;
    bool exist = file.exists("merge.xml");
    if (exist)
    {
        MergeXml mergeXml;
        mergeXml.load();
        QList<BaseWidget*> *list = ui->screenLayout->ScreenList();
        qDeleteAll(*list);
        list->clear();
        foreach (MergeItem *item, mergeXml.merges())
        {
            PlayScreen* screen = new PlayScreen;
            PlayScreen* hideScreen = NULL;
            screen->setRow(item->row());
            screen->setColumn(item->col());
            screen->setSpanRow(item->rowspan());
            screen->setSpanColumn(item->colspan());
            screen->setDisplayid(item->displayID());
//            screen->setIsMerge(item->mergeFlag());
//            screen->setUseflag(item->useFlag());
            if (item->mergeFlag())
            {
                foreach(MergeItem *subItem, *item->containItems())
                {
                    if (subItem->mergeFlag())
                    {
                        screen->setOriginalRow(subItem->row());
                        screen->setOriginalColumn(subItem->col());
                        screen->setOriginalSpanRow(subItem->rowspan());
                        screen->setOriginalSpanColumn(subItem->colspan());
//                        screen->getMergeList()->append(screen);
                    }
                    else
                    {
                        hideScreen = new PlayScreen;
                        hideScreen->setRow(subItem->row());
                        hideScreen->setColumn(subItem->col());
                        hideScreen->setSpanRow(subItem->rowspan());
                        hideScreen->setSpanColumn(subItem->colspan());
                        hideScreen->setDisplayid(subItem->displayID());
//                        hideScreen->setIsMerge(subItem->mergeFlag());
                        hideScreen->setUseflag(subItem->useFlag());
//                        screen->getMergeList()->append(hideScreen);
                        connect(hideScreen, SIGNAL(sendPreviewScreenSig(QString)), this, SLOT(sendPreviewControlSlot(QString)));
                        connect(hideScreen, SIGNAL(closePreviewWindowSig(QString)), this, SLOT(closePreviewCtrlSlot(QString)));
                        connect(hideScreen, SIGNAL(sendDefaultPreScreenSig(PlayScreen*,int)), this, SLOT(sendDefaultPreScreenSlot(PlayScreen*,int)));
                        connect(hideScreen, SIGNAL(sendCurrentScreenSig(PlayScreen*)), this, SLOT(sendCurrentScreenSlot(PlayScreen*)));
                        connect(hideScreen, SIGNAL(closeAllPreviewWndSig(PlayScreen*)), this, SLOT(closeAllPreviewCtrlSlot(PlayScreen*)));
                        connect(hideScreen, SIGNAL(sendFullPreviewSig(QString)), this,SIGNAL(sendFullPreviewCtrlSig(QString)));
                        list->append(hideScreen);
                    }
                }
            }
            connect(screen, SIGNAL(sendPreviewScreenSig(QString)), this, SLOT(sendPreviewControlSlot(QString)));
            connect(screen, SIGNAL(closePreviewWindowSig(QString)), this, SLOT(closePreviewCtrlSlot(QString)));
            connect(screen, SIGNAL(sendDefaultPreScreenSig(PlayScreen* ,int)), this, SLOT(sendDefaultPreScreenSlot(PlayScreen* ,int)));
            connect(screen, SIGNAL(sendCurrentScreenSig(PlayScreen*)), this, SLOT(sendCurrentScreenSlot(PlayScreen*)));
            connect(screen, SIGNAL(closeAllPreviewWndSig(PlayScreen*)), this, SLOT(closeAllPreviewCtrlSlot(PlayScreen*)));
            connect(screen, SIGNAL(sendFullPreviewSig(QString)), this,SIGNAL(sendFullPreviewCtrlSig(QString)));
            list->append(screen);
        }
        ui->screenLayout->changeScreen();
    }
    else
    {
        ConfigXML cardConfig;
        if(!cardConfig.load()) return;
        QList<BaseWidget*> *list = ui->screenLayout->ScreenList();
        qDeleteAll(*list);
        list->clear();
        foreach (ConfigItem item, cardConfig.items())
        {
            PlayScreen* screen = new PlayScreen;
            screen->setRow(item.row());
            screen->setColumn(item.col());
            screen->setSpanRow(item.rowspan());
            screen->setSpanColumn(item.colspan());
            screen->setDisplayid(item.displayID());
//            setPreviewWindow(screen, 1);
            list->append(screen);
            connect(screen, SIGNAL(sendPreviewScreenSig(QString)), this, SLOT(sendPreviewControlSlot(QString)));
            connect(screen, SIGNAL(closePreviewWindowSig(QString)), this, SLOT(closePreviewCtrlSlot(QString)));
            connect(screen, SIGNAL(sendDefaultPreScreenSig(PlayScreen* ,int)), this, SLOT(sendDefaultPreScreenSlot(PlayScreen* ,int)));
            connect(screen, SIGNAL(sendCurrentScreenSig(PlayScreen*)), this, SLOT(sendCurrentScreenSlot(PlayScreen*)));
            connect(screen, SIGNAL(closeAllPreviewWndSig(PlayScreen*)), this, SLOT(closeAllPreviewCtrlSlot(PlayScreen*)));
            connect(screen, SIGNAL(sendFullPreviewSig(QString)), this,SIGNAL(sendFullPreviewCtrlSig(QString)));
        }
        ui->screenLayout->changeScreen();
    }
}

void ScreenControlWidget::restoreScreen()
{
    foreach(BaseWidget* w, *ui->screenLayout->ScreenList())
    {
        PlayScreen* screen = (PlayScreen*)w;
//        if (!screen->useflag())
//        {
//            m_saveDisplayId.removeAt();
//            continue;
//        }
        int temp = 0;
        for (int i = 0; i < m_saveMsg.count(); i++)
        {
            if (screen->displayId() == m_saveMsg.at(i)->m_displayId)
            {
                if (!screen->useflag())
                {
                    temp = i;
                }
                PreviewWindow previewWin;
                screen->createPlaywindows(m_saveMsg.at(i)->m_previewNum, m_saveMsg.at(i)->m_previewNum, &previewWin);
                qDebug() << "ScreenControlWidget::restoreScreen" << m_saveMsg.at(i)->m_previewNumStr;
            }
        }
        if (!screen->useflag())
        {
            m_saveMsg.removeAt(temp);
        }
    }
}

void ScreenControlWidget::setPreviewWindowSlot(int count)
{
    PlayScreen *curScreen = (PlayScreen *)ui->screenLayout->selectScreen();
    qDebug() << "ScreenControlWidget::setPreviewWindowSlot" << curScreen;

    if (curScreen != NULL)
    {
//        foreach(BaseWidget *temp, *curScreen->getPreviewWndLayout()->ScreenList())
//        {
//            PreviewWindow *pre = new PreviewWindow;
//            memcpy(pre, temp, sizeof(*temp));
//            m_preWndList.append(pre);

//            qDebug() << "ScreenControlWidget::setPreviewWindowSlot";
//        }

        setPreviewWindow(curScreen, sqrt(count));
    }
}

void ScreenControlWidget::setPreviewWindow(PlayScreen *screen,int count)
{
    PreviewWindow previewWin;
    QString splitData = screen->displayId() + "," + QString::number(count*count, 10);
    screen->createPlaywindows(count, count, &previewWin);
    screen->setColNum(count);
    screen->closeUnnecessaryWnd();

    SaveMsg *msg = new SaveMsg;
    msg->m_displayId = screen->displayId();
    msg->m_previewNum = count;
    msg->m_previewNumStr = "";
    m_saveMsg.append(msg);

    qDebug() << "ScreenControlWidget::setPreviewWindow" << splitData;
    emit sendSplitReqSig(splitData);
}

void ScreenControlWidget::restorePreWnd(BaseWidget* widget, int count)
{
    PlayScreen* screen = (PlayScreen*)widget;
//    screen->getPreviewWndLayout()->ScreenList()->
}

void ScreenControlWidget::configChangeSlot()
{
    initScreenLayout();
}

void ScreenControlWidget::paintPreviewScreenFontSlot()
{
    PlayScreen *curScreen = (PlayScreen *)ui->screenLayout->selectScreen();

    if(curScreen)
    {
        curScreen->paintPreviewWindow(true);
    }
    else
        return;
    int num = -1, j = 0;
    for(int i = 0; i < m_saveMsg.count(); i++)
    {
        if (m_saveMsg.at(i)->m_displayId == curScreen->displayId())
        {
            if (curScreen->getPreviewWndNum() == 0)
                continue;

            m_saveMsg.at(i)->m_previewNumStr += QString::number(curScreen->getPreviewWndNum()) + ",";
            num = i;
        }

        if (num == i)
        {
            qDebug() << "ScreenControlWidget::paintPreviewScreenFontSlot" << m_saveMsg.at(i)->m_previewNumStr;
        }
    }
}

void ScreenControlWidget::pressChannelSlot(QTreeWidgetItem *item, int column)
{
    qDebug() << "ScreenControlWidget::pressChannelSlot";
    m_treeItem = (QTreeWidgetItem*)item;
    Entity *pEntity = (Entity *)item->data(1,0).toInt();
    Channel *pChannel = static_cast<Channel *>(pEntity);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    m_channelId = pChannel->channelId();
//    ItemMsg itemMsg;
//    itemMsg.item = m_treeItem;
//    itemMsg.channel = pChannel->channelId();
//    m_itemList.append(itemMsg);
    m_treeMap.insert(item, pChannel->channelId());
    dataStream << pChannel->channelId() << pChannel->dvrId();
//    qDebug() << "PlayScreen::pressChannelSlot" << pChannel->channelId() << pChannel->dvrId();
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("screencontrolwidget/preview", itemData);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
    if (dropAction == Qt::MoveAction)
    {
        qDebug() << "ScreenControlWidget::pressChannelSlot(QTreeWidgetItem *item, int column)";
    }
}

void ScreenControlWidget::paintScreen(BaseWidget *widget)
{
    foreach(BaseWidget *w, *ui->screenLayout->ScreenList())
    {
        PlayScreen *sub = (PlayScreen*)w;
        sub->setPaintFlag(false);
    }

    qDebug() << "ScreenControlWidget::paintScreen";
    PlayScreen* curScreen = (PlayScreen*)widget;
    curScreen->setPaintFlag(true);
}

void ScreenControlWidget::setItemMode(bool mode)
{
    if (mode)
    {
        m_treeItem->setIcon(0,QIcon(SkinManager::instance()->getPicture("channelPlaying.png")));
    }
    else
    {
        m_treeMap.key(m_channelId)->setIcon(0,QIcon(SkinManager::instance()->getPicture("channel.png")));
    }
}

void ScreenControlWidget::sendPreviewControlSlot(QString str)
{
    if (str == NULL)
    {
        emit sendPreviewControlSig(NULL);
        return;
    }
    qDebug() << "ScreenControlWidget::sendPreviewControlSlot";
    int i;
    bool bInsert;
    for (i = 0; i < m_channelList.count(); i++)
    {
        if (m_channelList.contains(m_channelId))
        {
            emit sendPreviewControlSig("channel");
            bInsert = false;
            break;
        }
        bInsert = true;
    }

    if (m_channelList.count() == 0 || bInsert)
    {
        m_channelList.append(m_channelId);
        emit sendPreviewControlSig(str);
    }
}

void ScreenControlWidget::closePreviewCtrlSlot(QString str)
{
    qDebug() << "ScreenControlWidget::closePreviewCtrlSlot" << str;
    QStringList list = str.split(":");
    QStringList previewList = list.at(0).split(",");
    QString tempStr = list.at(1);
//    ChannelMsg msg;
//    msg.dvr = previewList.at(0).toInt();
//    msg.channel = previewList.at(1).toInt();
//    qDebug() << "ScreenControlWidget::closePreviewCtrlSlot" << previewList.at(1).toInt();
    m_channelId = previewList.at(1).toInt();
    m_channelList.removeOne(m_channelId);
    emit closePreviewCtrlSig(tempStr);
}

void ScreenControlWidget::showEvent(QShowEvent *)
{
    if (m_show == 1)
    {
        initScreenLayout();
        m_show++;
    }
}

void ScreenControlWidget::changeScreenLayout(QList<BaseWidget*> *pList)
{
    QList<BaseWidget*> *montageList = pList;
    foreach(BaseWidget *montageTemp, *montageList)
    {
        foreach(BaseWidget *screenTemp, *ui->screenLayout->ScreenList())
        {
            PlayScreen* montage = (PlayScreen*)montageTemp;
            PlayScreen* screen = (PlayScreen*)screenTemp;
            if (montage->displayId() == screen->displayId())
            {
                if (!compareEqual(screen, montage))
                {
                    assignment(screen, montage);
                    if (!screen->useflag())
                    {
                        //关闭被拼接屏上的预览界面
                        closeAllPreviewCtrl(screen);
//                        foreach(BaseWidget *temp, *screen->getPreviewWndLayout()->ScreenList())
//                        {
//                            PreviewWindow *pre = (PreviewWindow*)temp;
//                            if (pre->getIsPreview())
//                            {
//                                screen->closePreview(pre);
//                            }
//                        }
                    }
                }
                break;
            }
        }
    }
//    for(int i = 0; i < (*ui->screenLayout->ScreenList()).count(); i++)
//    {
//        PlayScreen* listTemp = (PlayScreen*)(*m_list).at(i);
//        PlayScreen* screenListTemp = (PlayScreen*)(*ui->screenLayout->ScreenList()).at(i);
//        if (!compareEqual(listTemp, screenListTemp))
//        {
//            assignment(listTemp, screenListTemp);
//        }
//    }
    ui->screenLayout->changeScreen();
}

bool ScreenControlWidget::compareEqual(PlayScreen *des, PlayScreen *org)
{
    if (org->SpanColumn() == des->SpanColumn() && org->SpanRow() == des->SpanRow() && org->useflag() == des->useflag())
    {
        return true;
    }
    return false;
}

void ScreenControlWidget::assignment(PlayScreen *des, PlayScreen *org)
{
    des->setSpanColumn(org->SpanColumn());
    des->setSpanRow(org->SpanRow());
    des->setUseflag(org->useflag());
    des->setColumn(org->column());
    des->setRow(org->row());
}

void ScreenControlWidget::sendDefaultPreScreenSlot(PlayScreen* screen, int count)
{
    setPreviewWindow(screen, count);
//    QString splitData = screen->displayId() + "," + QString::number(count*count, 10);
//    SaveMsg *msg = new SaveMsg;
//    msg->m_displayId = screen->displayId();
//    msg->m_previewNum = count;
//    msg->m_previewNumStr = "";
//    m_saveMsg.append(msg);

//    qDebug() << "ScreenControlWidget::setPreviewWindow" << splitData;
    //    emit sendSplitReqSig(splitData);
}

void ScreenControlWidget::sendCurrentScreenSlot(PlayScreen *screen)
{
    ui->screenLayout->setSelectScreen(screen);
}

void ScreenControlWidget::closeAllPreviewCtrlSlot(PlayScreen *screen)
{
    closeAllPreviewCtrl(screen);
}

void ScreenControlWidget::closeAllPreviewCtrl(PlayScreen *screen)
{
    foreach(BaseWidget *temp, *screen->getPreviewWndLayout()->ScreenList())
    {
        PreviewWindow *pre = (PreviewWindow*)temp;
        if (pre->getIsPreview())
        {
            screen->closePreview(pre);
        }
    }
}
