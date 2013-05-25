#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H


#include "layoutwidget.h"
#include "previewwindow.h"
#include "msocket.h"
#include <QHBoxLayout>
#include <QTreeWidgetItem>

class PlayScreen : public BaseWidget
{
    Q_OBJECT
public:
    explicit PlayScreen(QWidget *parent = 0);
    ~PlayScreen();
    virtual BaseWidget* clone();
    void createPlaywindows(int row,int column,PlayWindow*);
    void closeUnnecessaryWnd();
    void setColNum(int);
    int getColNum();
    void paintPreviewWindow(bool);
    int  calPreviewWindow(QPoint);
    void setClosePollingFlag(bool);
    void setPreviewWndFlag(bool);
    int getPreviewWndNum();
    LayoutWidget* getPreviewWndLayout();
    //调用关闭预览，不由信号触发
    void closePreview(PreviewWindow*);
    void closeCirculate();
signals:
    void sendPreviewScreenSig(QString);
    void sendCirculateSig(QString,bool);
    void closePreviewWindowSig(QString);
    void closeAllPreviewWndSig(PlayScreen*);
    void sendDefaultPreScreenSig(PlayScreen*, int);
    void sendCurrentScreenSig(PlayScreen*);
    void sendFullPreviewSig(QString);
public slots:
    void closePreviewSlot();
    void closeAllPreviewSlot();
    void closePollingSlot();
protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent *);
private:
    LayoutWidget  *m_layoutwidget;
    QHBoxLayout   *m_layout;
    PreviewWindow *m_previewWindow;
    int           m_colNum;
    QPoint        m_point;
    QMenu         *m_pollingMenu;
    QAction       *m_closePolling;
    bool          m_closePollingFlag;
    bool          m_dropFlag;
    bool          m_closePreFlag;
    bool          m_previewWndFlag;
    bool          m_doubleClickFlag;
    QString       m_schedule;
//    QList<int>    m_previewWndNum;
    int           m_previewWndNum;
};

#endif // PLAYSCREEN_H
