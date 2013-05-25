#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QWidget>

namespace Ui {
    class rectangle;
}

class rectangle : public QWidget
{
    Q_OBJECT

public:
    explicit rectangle(QWidget *parent = 0);
    ~rectangle();
protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::rectangle *ui;
};

#endif // RECTANGLE_H
