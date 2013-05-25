#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>

namespace Ui {
    class ToolBarWidget;
}

class ToolBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBarWidget(QWidget *parent = 0);
    ~ToolBarWidget();

signals:
    void setPreviewWindowSig(int);
public slots:
    void setPreviewWindowSlot(int);
private slots:
    void on_setWinBtn2_clicked();

    void on_setWinBtn1_clicked();

    void on_setWinBtn3_clicked();

    void on_setWinBtn4_clicked();

private:
    Ui::ToolBarWidget *ui;
};

#endif // TOOLBARWIDGET_H
