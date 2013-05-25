#ifndef SCREENTOOLBAR_H
#define SCREENTOOLBAR_H

#include <QWidget>
class QToolButton;

namespace Ui {
class ScreenToolBar;
}

class ScreenToolBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit ScreenToolBar(QWidget *parent = 0);
    ~ScreenToolBar();
    void setScreenCount(int count);
    void creatScreenId();
    void cancelDisplayId(int id);
    void cleanScreen();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    bool eventFilter(QObject *, QEvent *);
private slots:
    void on_RtoolBtn_clicked();
    void on_LtoolBtn_clicked();

private:
    void startDrag();
    bool existBtn(QObject* btn);
    QToolButton* getBtn(int id);
private:
    QPoint m_startPoint;
    QToolButton*m_selectedBtn;
    int m_screenCount;
    Ui::ScreenToolBar *ui;
    QList<QToolButton *> m_toolbottons;
};

#endif // SCREENTOOLBAR_H
