#ifndef LAYOUTWIDGET_H
#define LAYOUTWIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QGridLayout>
#include <QPoint>
#include "rectangle.h"
//#include "screenwidget.h"
#include "screen.h"

class QGridLayout;
namespace Ui {
class LayoutWidget;
}

class LayoutWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LayoutWidget(QWidget *parent = 0);
    ~LayoutWidget();
    void createLayout();
    bool createWidgetLayout(int,int,BaseWidget*);
    void createScreen(int,int,BaseWidget*);
    void changeScreen(bool streched=false);
    bool changeLayout(int,int,BaseWidget*);
    QMap<int,int>  m_RowColumn;
    QList<BaseWidget*>* ScreenList();
    QList<BaseWidget*>* getDelScreenList();
    BaseWidget* selectScreen();
    void setSelectScreen(BaseWidget*);
    void selectScreenWidget(QPoint startPoint);
    void setPaintFlag(bool flag);
    void delScreenList();
//    void setDoubleClick(bool);
//    void change();
//    void removeLayoutWidget();
//    void restoreScreen();
signals:
    void selectedScreenSignal(BaseWidget* selected);

protected:
    QPoint m_startPoint;
    QPoint m_endPoint;
    BaseWidget *m_selectedScreen;
    BaseWidget *getScreen(QPoint startPoint, QList<BaseWidget* > list);
    void paintEvent(QPaintEvent *);
public slots:
    virtual void changeSpanSlot(BaseWidget* widget);
    virtual void mouseEnterSlot(BaseWidget*);

private:
    int m_row;
    int m_column;
    void freeScreenList();

protected:
    BaseWidget *m_curwidget;

    void removeUnnecessaryWidget(int index);
//    void removeWidget(int);
    bool m_isMerged;
    bool m_flag;
    QList<BaseWidget*> m_ScreenList;
    QList<BaseWidget*> m_delScreenList;
    QGridLayout *m_GridLayout;
private:
    Ui::LayoutWidget *ui;    
    int m_wndNum;
};

#endif // LAYOUTWIDGET_H
