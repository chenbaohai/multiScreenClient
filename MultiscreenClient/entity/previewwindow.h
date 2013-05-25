#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include "playwindow.h"
#include <QMenu>
#include <QAction>

class PreviewWindow : public PlayWindow
{
    Q_OBJECT
public:
     PreviewWindow(QWidget *parent = 0);
     ~PreviewWindow();
     BaseWidget* clone();
     void paintWindow(bool flag);
     QString getDvrId();
     QString getChannelId();
     void setDvrId(QString);
     void setChannelId(QString);
     void setIsPreview(bool);
     bool getIsPreview();
     void setPreviewNum(int);
     int  getPreviewNum();
protected:
     void paintEvent(QPaintEvent *);
     void mouseDoubleClickEvent(QMouseEvent *);
     void mousePressEvent(QMouseEvent *);
     void contextMenuEvent(QContextMenuEvent *);
signals:
     void closePreviewSig();
     void closeAllPreviewSig();
public slots:
     void closePreviewSlot();
private:
     QMenu   *m_contextMenu;
     QAction *m_closeAction;
     QAction *m_closeAllAction;
     bool     m_flag;
     bool     m_previewFlag;
     int      m_previewNum;
     QString  m_dvr;
     QString  m_channel;
};

#endif // PREVIEWWINDOW_H
