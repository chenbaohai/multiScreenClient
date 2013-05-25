#ifndef SCREENCONFIG_H
#define SCREENCONFIG_H

#include <QWidget>

#include "subscreen.h"
#include <QMenu>
#include <QAction>

#include "msocket.h"


namespace Ui {
    class CardConfigWidget;
}

class CardConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CardConfigWidget(QWidget *parent = 0);
    ~CardConfigWidget();

    int screenCount();
    void setScreenCount(int count);

    void setMsgSocket(MSocket *);

signals:
    void saveConfigSig();
    void sendConfigSig(QString);

public slots:
    void cancelDisplayid(int);
    void paintScreen(BaseWidget*);
private slots:
    void on_btnSetLayout_clicked();
    void on_btnRecognise_clicked();
    void on_btnSave_clicked();

private:
    void saveConfigXml();
    void loadConfigXml();

private:
    QAction *m_cancelDisplayid;
    QMenu *m_context;

    Ui::CardConfigWidget *ui;
    QString m_displayid;
    int m_screenCount;
    MSocket *m_socket;
};

#endif // SCREENCONFIG_H
