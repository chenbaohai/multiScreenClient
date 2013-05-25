#ifndef MONTAGELAYOUT_H
#define MONTAGELAYOUT_H

#include <QWidget>
#include "layoutwidget.h"
class QMenu;
class MontageLayout : public LayoutWidget
{
    Q_OBJECT
public:
    explicit MontageLayout(QWidget *parent = 0);
    ~MontageLayout();
    void saveConfigXml();
    void setConfigFlag();
    void setCancelFlag();
signals:
    void saveMergeXmlSig();
    void MergeScreenSignal();
    void cancelDisplayidSig(int);
public slots:
    void changeSpanSlot(BaseWidget* widget);
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void contextMenuEvent(QContextMenuEvent *);

    void focusOutEvent(QFocusEvent *);
    QList<Screen* > m_MergeList;
    virtual void FillMergeScreen(int Vminrow,int Vmincolumn,int rowSpan,int columnSpan,Screen* widget);
    void calucate();
    void MergeScreen();
    void getScreenSpan(int &Vminrow,int& Vmincolumn,int & rowSpan,int & columnSpan);
    void getMax_MinRowColumn(int& minRow,int& minColumn,int& maxRow,int& maxColumn,QList<Screen* > & list);
    bool searchMergeScreen(QList<Screen* > & list);//查询是否有一合并过的窗口

private slots:
    void cancelDisplayidSlot();
private:
    bool  dragMoveFlag;
    bool  mousePressFlag;
    QRect m_selrect;
    rectangle *rectfrm;

private:
    QAction*  m_cancelDisplayid;
    QMenu*    m_context;
    bool      m_configFlag;
    bool      m_cancelFlag;
};

#endif // MONTAGELAYOUT_H
