#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include "basewidget.h"

class Screen : public BaseWidget
{
    Q_OBJECT
public:
    Screen(QWidget *parent = 0);
    ~Screen();

//    const QString& displayid();
    virtual BaseWidget* clone();
    bool isMerged();
    void setIsMerge(bool);
    QList<Screen*>* getMergeList();

signals:

protected:
    void paintEvent(QPaintEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

private:
    bool m_isMerged;
    QList<Screen*> m_mergeList;
};

#endif // SCREEN_H
