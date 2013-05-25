#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include "basewidget.h"
#include "channel.h"

class PlayWindow : public BaseWidget
{
    Q_OBJECT
public:
    PlayWindow(QWidget *parent = 0);
    ~PlayWindow();

signals:
    
public slots:

protected:
//    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
private:
    Channel* m_channel;
};

#endif // PLAYWINDOW_H
