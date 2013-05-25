#ifndef WALLLAYOUT_H
#define WALLLAYOUT_H

#include <QWidget>
#include <QGridLayout>

#include "rectangle.h"
#include "smallscreen.h"


namespace Ui {
    class WallLayout;
}

class WallLayout : public QWidget
{
    Q_OBJECT

public:
    explicit WallLayout(QWidget *parent = 0);
    void createLayout(int row,int col);
    void setSplicing(bool value);
    ~WallLayout();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

    void paintEvent(QPaintEvent *);

    void timerEvent(QTimerEvent *);



private:
    Ui::WallLayout *ui;
    QGridLayout *m_layout;
    QList<QWidget *> m_laywidgets;
    SmallScreen *m_curWidget;
    int m_curindex;
    QPoint m_startPoint;
    QPoint m_endPoint;

    bool m_splicing,m_moved,m_draged,m_doubleClicked;
    rectangle m_rectfrm;
    QRect m_selrect;
    QVector<int> m_indexs;

private slots:
    void selectedSlot(SmallScreen *);

private:
    void calucateSplicingRect();
    void reLayout();
    void reCreateLayout();
    bool splicing();
    bool unsplicing();
    void clear();
    void changeIndex(int first,int second);
    bool swap1(int, int,bool span=true);

    int getWidgetIndexByPosition(QPoint pos); 

    void swap(int index1,int index2);

private:
    void singleWidgetMaximized();
    void showAllWidget();

};

#endif // WALLLAYOUT_H
