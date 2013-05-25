#ifndef PLAYERLAYOUT_H
#define PLAYERLAYOUT_H

#include "layoutwidget.h"
#include <QMenu>
#include <QAction>

class PlayerLayout : public LayoutWidget
{
    Q_OBJECT
public:
    explicit PlayerLayout(QWidget *parent = 0);
    ~PlayerLayout();

signals:
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *e);
//    void paintEvent(QPaintEvent *);
//    void mouseReleaseEvent(QMouseEvent *e);
//    void contextMenuEvent(QContextMenuEvent *);
private:
    QMenu   *m_contextMenu;
    QAction *m_closeAction;
};

#endif // PLAYERLAYOUT_H
