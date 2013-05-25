#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "interactdata.h"
#include "const.h"
#include "requestManager.h"
#include <QMessageBox>
#include <QList>
#include <QString>
#include <QDebug>
#include "skinmanager.h"

MainWidget::MainWidget(MSocket *socket,QWidget *parent) :
    TitleWidget(parent),
    m_show(0),
    m_firstshow(false),
    m_prebutton(NULL),
    m_socket(socket),
    m_getscreened(false),
    ui(new Ui::MainWidget)
{
    ui->setupUi(content());
    //轮巡界面的信号

//    m_socket = new MSocket;
//    m_socket->connectServer();
//    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);

    ui->cardConfigBtn->setProperty("index",ui->stackedWidget->addWidget(&m_CardConfig));
    ui->screenControlBtn->setProperty("index",ui->stackedWidget->addWidget(&m_ScreenControl));
    ui->screenConfigBtn->setProperty("index",ui->stackedWidget->addWidget(&m_ScreenConfig));
    ui->pollingSchemeBtn->setProperty("index", ui->stackedWidget->addWidget(&m_pollingScheme));

    ui->cardConfigBtn->setProperty("module","TOOLBUTTON");
    ui->screenControlBtn->setProperty("module","TOOLBUTTON");
    ui->screenConfigBtn->setProperty("module","TOOLBUTTON");
    ui->pollingSchemeBtn->setProperty("module","TOOLBUTTON");

    connect(ui->cardConfigBtn,SIGNAL(toggled(bool)),this,SLOT(toolBtnClickedSlot(bool)));
    connect(ui->screenConfigBtn,SIGNAL(toggled(bool)),this,SLOT(toolBtnClickedSlot(bool)));
    connect(ui->screenControlBtn,SIGNAL(toggled(bool)),this,SLOT(toolBtnClickedSlot(bool)));
    connect(ui->pollingSchemeBtn,SIGNAL(toggled(bool)), this, SLOT(toolBtnClickedSlot(bool)));

    //墙布局配置完之后发送消息给视频预览界面
    connect(&m_CardConfig, SIGNAL(saveConfigSig()), &m_ScreenControl, SLOT(configChangeSlot()));
    //墙布局配置完之后发送消息给拼接界面
    connect(&m_CardConfig, SIGNAL(saveConfigSig()), &m_ScreenConfig, SLOT(configChangeSlot()));
    //墙布局配置完之后发送消息给轮巡界面
    connect(&m_CardConfig, SIGNAL(saveConfigSig()), &m_pollingScheme, SLOT(configChangeSlot()));
    connect(&m_CardConfig, SIGNAL(sendConfigSig(QString)), this, SLOT(sendConfigSlot(QString)));

    connect(&m_ScreenControl, SIGNAL(sendPreviewControlSig(QString)), this, SLOT(sendPreviewControlSlot(QString)));
    connect(&m_ScreenControl, SIGNAL(sendSplitReqSig(QString)), this, SLOT(sendSplitReqSlot(QString)));
    connect(&m_ScreenControl, SIGNAL(closePreviewCtrlSig(QString)), this, SLOT(closePreviewWidgetSlot(QString)));
    connect(&m_ScreenControl, SIGNAL(sendFullPreviewCtrlSig(QString)), this, SLOT(sendFullPreviewSlot(QString)));

    connect(&m_ScreenConfig, SIGNAL(sendMergeXmlSig(QString)), this, SLOT(sendMergeXmlSlot(QString)));
    connect(&m_ScreenConfig, SIGNAL(changeLayoutSig(QList<BaseWidget*> *)), this, SLOT(changeCtrlLayoutSlot(QList<BaseWidget*> *)));

    //在预览小窗口上画出是否正常预览
    connect(this, SIGNAL(paintScreenFontSig()), &m_ScreenControl, SIGNAL(paintPreviewScreenFontSig()));

    connect(this, SIGNAL(closeBtnClickSig()),this,SLOT(hideMainWidgetSlot()));
    connect(this, SIGNAL(minBtnClickSig()), this, SLOT(minMainWidgetSlot()));
    connect(this, SIGNAL(maxBtnClickSig()), this, SLOT(maxMainWidgetSlot()));

    connect(&m_pollingScheme, SIGNAL(sendPollingSchemeSig(int, QString)), this, SLOT(sendPollSchemeSlot(int, QString)));
    connect(&m_pollingScheme, SIGNAL(sendCirculateSig(QString,bool)), this, SLOT(sendCirculateSlot(QString,bool)));
    connect(m_socket,SIGNAL(finishedSig(int)),this,SLOT(finishedSlot(int)));

    m_CardConfig.setMsgSocket(m_socket);


    sendXml();
    sendToken();
    sendGroupXml();
    createSystemTray();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initServer()
{
    if(m_getscreened) return;

    m_socket->sendMsg(INIT_REQUEST,"");
    m_getscreened=true;

//    InteractData initData;
//    initData.setCmd(INIT_REQUEST);
//    m_socket->setReadFlag(true);
//    if(m_socket->sendData(&initData))
//    {
//        initData.analyze();
//    }else
//    {
//        return;
//    }
//    m_CardConfig.setScreenCount(initData.recvCode());
//    m_CardConfig.setScreenCount(8);
}

void MainWidget::toolBtnClickedSlot(bool checked)
{
    if (checked)
    {
        int index = QObject::sender()->property("index").toInt();
        if (index == -1)
        {
            return;
        }
        ui->stackedWidget->setCurrentIndex(index);
        if(index==0)
            initServer();
    }

    changeActionIcon(QObject::sender());
}


void MainWidget::hideMainWidgetSlot()
{
    this->hide();
}

void MainWidget::minMainWidgetSlot()
{
    this->showMinimized();
}

void MainWidget::maxMainWidgetSlot()
{
    m_show++;
    if (m_show%2)
    {
        this->showMaximized();
    }
    else
    {
        this->showNormal();
    }
}

void MainWidget::closeMainWidgetSlot()
{
    InteractData quitData;
    quitData.setSendData(EXIT_REQUEST, "[ ]");
    m_socket->setReadFlag(true);
    if (m_socket->sendData(&quitData))
    {
    }

//    m_socket->setReadFlag(true);
//    m_socket->sendMsg(EXIT_REQUEST, "[ ]");

    QTime dieTime = QTime::currentTime().addMSecs(300);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    this->close();
}

void MainWidget::sendConfigSlot(QString configStr)
{
    m_socket->sendMsg(CONFIG_REQUEST,configStr);
//    qDebug() << "MainWidget::sendConfigSlot " << configStr;
//    InteractData configData;
//    QString tempData;
//    tempData = configData.buildUpData(CONFIG_REQUEST, configStr);
//    qDebug() << tempData;
//    configData.setSendData(CONFIG_REQUEST, tempData);
//    if (m_socket->sendData(&configData))
//    {
//        configData.analyze();
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendConfigSlot 电视墙配置发送失败";
//        return;
//    }
}

bool MainWidget::sendXml()
{
    m_restXml = RequestManager::instance()->getXml();
    m_socket->sendMsg(ORGXML_REQUEST,m_restXml);
//    InteractData xmlData;
//    xmlData.setSendData(ORGXML_REQUEST, m_restXml);
////    qDebug() << "MainWidget::sendXmlToServer" << m_restXml;
//    if (m_socket->sendData(&xmlData))
//    {
//        xmlData.analyze();
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendXml xml发送失败";
//        return false;
//    }
//    return true;
}

bool MainWidget::sendToken()
{
    m_token = RequestManager::instance()->getToken();
    m_socket->sendMsg(TOKEN_REQUEST,m_token);
//    InteractData tokenData;
//    QString tempData;
//    tempData = tokenData.buildUpData(TOKEN_REQUEST, m_token);
//    tokenData.setSendData(TOKEN_REQUEST, tempData);
////    qDebug() << "MainWidget::sendTokenToServer" << tempData;
//    if (m_socket->sendData(&tokenData))
//    {
//        tokenData.analyze();
////        qDebug() << "MainWidget::sendTokenToServer" << tokenData.recvCode();
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendXml token发送失败";
//        return false;
//    }
//    return true;
}


bool MainWidget::sendGroupXml()
{
    m_groupXml = RequestManager::instance()->getGroupXml();
    m_socket->sendMsg(GROUPXML_REQUEST,m_groupXml);
//    InteractData groupData;
//    groupData.setSendData(GROUPXML_REQUEST, m_groupXml);
////    qDebug() << "MainWidget::sendGroupXml" << m_groupXml;
//    if (m_socket->sendData(&groupData))
//    {
//        groupData.analyze();
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendGroupXml发送失败";
//        return false;
//    }
//    return true;
}

void MainWidget::sendPreviewControlSlot(QString previewStr)
{
    if (previewStr == NULL)
    {
        QMessageBox::information(this, "系统提示", "该屏幕已经在预览！",tr("确定"));
        return;
    }

    if (previewStr == "channel")
    {
        QMessageBox::information(this, "系统提示", "该通道已经在预览！",tr("确定"));
        return;
    }
    m_socket->sendMsg(PREVIEW_REQUEST,previewStr);
    m_ScreenControl.setItemMode(true);
    emit paintScreenFontSig();

//    InteractData channelData;
//    QString tempData;
//    tempData = channelData.buildUpData(PREVIEW_REQUEST, previewStr);
//    channelData.setSendData(PREVIEW_REQUEST, tempData);
//    m_socket->setwait(false);
//    qDebug() << "MainWidget::sendPreviewControlSlot" << tempData;
////    emit paintScreenFontSig();
//    if (m_socket->sendData(&channelData))
//    {
//        channelData.analyze();
////        qDebug() << "channelData.recvCode()" << channelData.recvCode();
////        if (channelData.recvCode() != 0)
////        {
//            m_ScreenControl.setItemMode(true);
//            emit paintScreenFontSig();
////        }
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendPreviewControlSlot 预览命令发送失败";
//        return;
//    }
}


void MainWidget::sendFullPreviewSlot(QString fullPreview)
{
    qDebug() << "MainWidget::sendFullPreviewSlot" << fullPreview;
    m_socket->sendMsg(FULLPREVIEW_REQUEST, fullPreview);
}

void MainWidget::sendSplitReqSlot(QString data)
{
    qDebug() << "MainWidget::sendSplitReqSlot" << data;
    m_socket->sendMsg(SPLITWINDOW_REQUEST,data);
//    InteractData splitData;
//    QString tempData;
//    tempData = splitData.buildUpData(SPLITWINDOW_REQUEST, data);
//    splitData.setSendData(SPLITWINDOW_REQUEST, tempData);
//    qDebug() << "MainWidget::sendSplitReqSlot" << tempData;
//    if (m_socket->sendData(&splitData))
//    {
//        splitData.analyze();
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendSplitReqSlot 分割命令发送失败";
//        return;
//    }
}

void MainWidget::sendMergeXmlSlot(QString mergeStr)
{
    m_socket->sendMsg(STRETCH_REQUEST,mergeStr);
//    InteractData mergeData;
//    QString tempData;
//    tempData = mergeData.buildUpData(STRETCH_REQUEST, mergeStr);
//    mergeData.setSendData(STRETCH_REQUEST, tempData);
//    qDebug() << "MainWidget::sendMergeXmlSlot" << tempData;
//    if (m_socket->sendData(&mergeData))
//    {
//        mergeData.analyze();
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendSplitReqSlot 拼接拆分xml发送失败";
//        return;
//    }
}

void MainWidget::closePreviewWidgetSlot(QString closeStr)
{
    if(closeStr=="") return;
    m_socket->sendMsg(STOPPREVIEW_REQUEST,closeStr);
    m_ScreenControl.setItemMode(false);
//    InteractData closeData;
//    QString tempData;
//    tempData = closeData.buildUpData(STOPPREVIEW_REQUEST, closeStr);
//    closeData.setSendData(STOPPREVIEW_REQUEST, tempData);
//    qDebug() << "MainWidget::closePreviewWidgetSlot" << tempData;
//    if (m_socket->sendData(&closeData))
//    {
//        m_ScreenControl.setItemMode(false);
//        closeData.analyze();
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendSplitReqSlot 关闭预览窗口发送失败";
//        return;
//    }
}

void MainWidget::changeCtrlLayoutSlot(QList<BaseWidget*> *pList)
{
    m_ScreenControl.changeScreenLayout(pList);
//    m_ScreenControl.restoreScreen();
    m_pollingScheme.changeScreenLayout(pList);
}

void MainWidget::sendPollSchemeSlot(int cmd, QString schemeStr)
{
    m_socket->sendMsg(SCHEDULEXML_REQUEST,schemeStr);
//    qDebug() << "MainWidget::sendPollSchemeSlot(int cmd, QString schemeStr)";
//    InteractData schemeData;
//    if (cmd == SCHEDULEXML_REQUEST)
//    {
//        qDebug() << "cmd == SCHEDULEXML_REQUEST";
//        schemeData.setSendData(SCHEDULEXML_REQUEST, schemeStr);
//    }
//    else
//    {
//        schemeData.setSendData(SCHEDULE_REQUEST, schemeStr);
//    }
//    qDebug() << "MainWidget::sendPollSchemeSlot" << schemeStr;
//    if (m_socket->sendData(&schemeData))
//    {
//        schemeData.analyze();
//    }
//    else
//    {
//        qDebug() << "MainWidget::sendPollSchemeSlot xml发送失败";
//        return;
//    }
//    return;
}

void MainWidget::sendCirculateSlot(QString str,bool started)
{        
    if(started)
    {
        m_socket->sendMsg(STARTCIRCULATE_REQUEST,str);
    }
    else
    {
       m_socket->sendMsg(STOPCIRCULATE_REQUEST,str);
    }



//    InteractData circulateData;
//    QString tempData;
//    if(started)
//    {
//        tempData = circulateData.buildUpData(STARTCIRCULATE_REQUEST, str);
//        circulateData.setSendData(STARTCIRCULATE_REQUEST, tempData);
//    }
//    else
//    {
//        tempData = circulateData.buildUpData(STOPCIRCULATE_REQUEST, str);
//        circulateData.setSendData(STOPCIRCULATE_REQUEST, tempData);
//    }

//    if (m_socket->sendData(&circulateData))
//    {
//        circulateData.analyze();

//    }
//    else
//    {
//        qDebug() << "MainWidget::sendPreviewControlSlot 预览命令发送失败";
//        return;
//    }
}

void MainWidget::changeActionIcon(QObject *object)
{
    int index=object->property("index").toInt();
    QToolButton *button=static_cast<QToolButton *>(object);

    QString checked=QString("action-%1-checked.png").arg(index);


    button->setIcon(QIcon(QPixmap(SkinManager::instance()->getPicture(checked))));

    if(m_prebutton)
    {
        QString normal=QString("action-%1.png").arg(m_preindex);
        m_prebutton->setIcon(QIcon(QPixmap(SkinManager::instance()->getPicture(normal))));
    }
    m_prebutton=button;
    m_preindex=index;

}

void MainWidget::showEvent(QShowEvent *)
{
    if(!m_firstshow)
    {
        //默认启动界面
        ui->screenControlBtn->toggle();
        m_firstshow=true;
    }
}

void MainWidget::setMsgSocket(MSocket * socket)
{
    m_socket=socket;
}

void MainWidget::finishedSlot(int value)
{
    m_CardConfig.setScreenCount(value);
    m_getscreened=value>0;
}

void MainWidget::createSystemTray()
{
    createTrayMenu();
    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        return;
    }
    m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setToolTip(tr("多屏应用客户端"));
    m_systemTray->setContextMenu(m_menu);
    m_systemTray->setIcon(QIcon(SkinManager::instance()->getPicture("logo.png")));
    m_systemTray->show();
    connect(m_systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayActivated(QSystemTrayIcon::ActivationReason)));
}

void MainWidget::createTrayMenu()
{
    m_closeSubMenu = new QAction(tr("退出(&Q)"), this);
    m_showSubMenu  = new QAction(tr("显示(&S)"), this);
    connect(m_closeSubMenu, SIGNAL(triggered()), this, SLOT(closeMainWidgetSlot()));
    connect(m_showSubMenu, SIGNAL(triggered()), this, SLOT(showMainWidgetSlot()));
    m_menu = new QMenu((QWidget* )QApplication::desktop());
    m_menu->addAction(m_closeSubMenu);
    m_menu->addAction(m_showSubMenu);
}

void MainWidget::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::DoubleClick:
            this->showMainWidget();
            break;
        default:
        break;
    }
}

void MainWidget::showMainWidgetSlot()
{
    showMainWidget();
}

void MainWidget::showMainWidget()
{
    this->activateWindow();
    this->showNormal();
}
