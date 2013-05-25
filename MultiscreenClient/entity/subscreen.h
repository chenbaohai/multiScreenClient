#ifndef SUBSCREEN_H
#define SUBSCREEN_H

#include "screen.h"
#include "screentoolbar.h"
#include <QVector>
#include <QToolButton>

class SubScreen : public Screen
{
    Q_OBJECT
public:
    explicit SubScreen(QWidget *parent = 0);
    ~SubScreen();
    void setDisplayid(const QString& id);
    virtual BaseWidget* clone();
     void cancelDisPlayid();
protected:
    void paintEvent(QPaintEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
private:
    QVector<QToolButton* >*  m_vector;
    void fillLayout();
    QWidget* m_text;
    int m_buttonCount;
    ScreenToolBar* m_toolBar;
};

#endif // SUBSCREEN_H
