#ifndef SCREENCONFIGWIDGET_H
#define SCREENCONFIGWIDGET_H

#include <QWidget>
#include "screen.h"

namespace Ui {
class ScreenConfigWidget;
}

class ScreenConfigWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ScreenConfigWidget(QWidget *parent = 0);
    ~ScreenConfigWidget();
    
    void initScreenConfig();
    void saveMergeXml();
signals:
    void sendMergeXmlSig(QString);
    void changeLayoutSig(QList<BaseWidget*> *);
public slots:
    void configChangeSlot();
    void saveMergeXmlSlot();
    void paintScreen(BaseWidget*);
private:
    Ui::ScreenConfigWidget *ui;
};

#endif // SCREENCONFIGWIDGET_H
