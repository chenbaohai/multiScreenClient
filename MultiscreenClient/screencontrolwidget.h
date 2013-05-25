#ifndef SCREENCONTROLWIDGET_H
#define SCREENCONTROLWIDGET_H

#include <QWidget>
#include "playscreen.h"
#include "playwindow.h"
#include "basetreewidget.h"

#include <QList>

namespace Ui {
class ScreenControlWidget;
}

typedef struct
{
    qint64 dvr;
    qint64 channel;
} ChannelMsg;

typedef struct
{
    QTreeWidgetItem* item;
    qint64 channel;
}ItemMsg;

typedef struct
{
    QString     m_displayId;
    int         m_previewNum;
    QString     m_previewNumStr;
}SaveMsg;
class ScreenControlWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ScreenControlWidget(QWidget *parent = 0);
    ~ScreenControlWidget();
    
//    void createPreviewWindow();
    void initScreenLayout();
    void setItemMode(bool);
    void changeScreenLayout(QList<BaseWidget*> *);
    bool compareEqual(PlayScreen*,PlayScreen*);
    void assignment(PlayScreen*,PlayScreen*);
    void restoreScreen();
signals:
    void sendPreviewControlSig(QString);
    void sendSplitReqSig(QString);
    void paintPreviewScreenFontSig();
    void closePreviewCtrlSig(QString);
    void sendFullPreviewCtrlSig(QString);
public slots:
    void setPreviewWindowSlot(int);
    void sendPreviewControlSlot(QString);
    void closePreviewCtrlSlot(QString);
    void configChangeSlot();
    void paintScreen(BaseWidget*);
//    void sendPreviewSlot(QString);
    void restorePreWnd(BaseWidget*,int);
    void sendDefaultPreScreenSlot(PlayScreen*, int);
    void sendCurrentScreenSlot(PlayScreen*);
    void closeAllPreviewCtrlSlot(PlayScreen*);
private slots:
    void paintPreviewScreenFontSlot();
    void pressChannelSlot(QTreeWidgetItem*,int);
protected:
    void showEvent(QShowEvent *);
private:
    void setPreviewWindow(PlayScreen*,int);
    void closeAllPreviewCtrl(PlayScreen*);
private:
    QTreeWidgetItem *m_treeItem;
    ChannelMsg m_msg;
    QList<qint64> m_channelList;
    QList<ItemMsg> m_itemList;
    QMap<QTreeWidgetItem*,qint64> m_treeMap;
    qint64 m_channelId;
    QList<SaveMsg*>  m_saveMsg;
    int m_show;
    Ui::ScreenControlWidget *ui;
};

#endif // SCREENCONTROLWIDGET_H
