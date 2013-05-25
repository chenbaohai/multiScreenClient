#ifndef WINDOWLAYOUT_H
#define WINDOWLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>




class WindowLayoutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WindowLayoutWidget(QWidget *parent = 0);
    void createWidget(double num);
    void ruleChangeLayout(int, int);    
    int appendWidget(QWidget *);//·µ»Øindex
    bool insertWidget(int,QWidget*);
    bool removeByIndex(int index);

    void setRightMenu(QMenu *);
    QMenu * rightMenu();
    QList<QWidget*> allWidget();

signals:
    void forceStopSignal(int,QWidget *);
    void selectedSignal(int,QWidget *);
    void insertSignal(int);
    void switchSignal(int,int);

public slots:
protected:
    void mouseDoubleClickEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void contextMenuEvent(QContextMenuEvent *);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
protected:
    QList<QWidget*> m_allWidget;
    QMenu  *m_rightMenu;
    QGridLayout *m_gridLayout;
private:
    QWidget * m_curWidget;
    int m_curIndex ;
    bool m_doubleClicked;
    bool m_dbClicked;
    int m_paintCount;
    int m_index ;
    QPoint m_startPos; 
    void removeUnnecessaryWidget(int index);
    void singleWidgetMaximized();
    void showAllWidget();
};

#endif // WINDOWLAYOUT_H
