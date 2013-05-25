#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include "titlewidget.h"
#include "screenconfigwidget.h"
#include "screencontrolwidget.h"
#include "cardconfigwidget.h"
#include "pollingschemewidget.h"
#include "msocket.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public TitleWidget
{
    Q_OBJECT    
public:
    explicit MainWidget(MSocket *,QWidget *parent = 0);
    ~MainWidget();

    bool sendXml();
    bool sendToken();
    bool sendGroupXml();
    void setMsgSocket(MSocket *);
protected:
    void showEvent(QShowEvent *);

signals:
    void paintScreenFontSig();
public slots:
    void toolBtnClickedSlot(bool checked);
    void closeMainWidgetSlot();
    void hideMainWidgetSlot();
    void minMainWidgetSlot();
    void maxMainWidgetSlot();

    void sendConfigSlot(QString);
    void sendPreviewControlSlot(QString);
    void sendSplitReqSlot(QString);
    void sendMergeXmlSlot(QString);    
    void closePreviewWidgetSlot(QString);
    void sendPollSchemeSlot(int, QString);
    void sendCirculateSlot(QString,bool);
    void changeCtrlLayoutSlot(QList<BaseWidget*> *);
    void sendFullPreviewSlot(QString);
    void finishedSlot(int);
    void trayActivated(QSystemTrayIcon::ActivationReason);
    void showMainWidgetSlot();
private:
    void initServer();
    void changeActionIcon(QObject *object);
    void createSystemTray();
    void createTrayMenu();
    void showMainWidget();
private:
    Ui::MainWidget *ui;

    MSocket              *m_socket;
    ScreenConfigWidget   m_ScreenConfig;
    ScreenControlWidget  m_ScreenControl;
    CardConfigWidget     m_CardConfig;
    PollingSchemeWidget  m_pollingScheme;
    QString              m_restXml;
    QString              m_token;
    QString              m_groupXml;
    int                  m_show;
    bool                 m_firstshow;
    QToolButton          *m_prebutton;
    int                  m_preindex;
    bool                 m_getscreened;
    QSystemTrayIcon      *m_systemTray;
    QMenu                *m_menu;
    QAction              *m_showSubMenu;
    QAction              *m_closeSubMenu;
};

#endif // MAINWIDGET_H
