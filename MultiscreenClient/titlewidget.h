#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>

namespace Ui {
class TitleWidget;
}

class TitleWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TitleWidget(QWidget *parent = 0);
     ~TitleWidget();

public:
    QWidget* content();
signals:
    void closeBtnClickSig();
    void minBtnClickSig();
    void maxBtnClickSig();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);
private:
    QPoint m_DragPos;
    QPoint m_startPos;
    QPoint m_SchemesPos;
    bool m_move;


    
private:
    Ui::TitleWidget *ui;
};

#endif // TITLEWIDGET_H
