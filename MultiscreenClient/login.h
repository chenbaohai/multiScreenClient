#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPoint>
#include <QString>
#include "msocket.h"



namespace Ui {
    class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QDialog *parent = 0);
    ~Login();
    MSocket * msgSocket();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:
    void dragMousePressSignal(QPoint);
    void dragMouseMoveSignal(QPoint);
private slots:
    void optWidgetShow();
    void on_loginBtn_clicked();
    void on_pwdEdit_returnPressed();

private:
    bool getLoginInfo();
private:
    QPoint  m_startPos;
    QPoint  m_parentPos;
    QString m_ip;
    int     m_port;
    QString m_multiIp;
    int     m_multiPort;
    QString m_user;
    QString m_password;
    Ui::Login *ui;
private:
    MSocket *m_socket;
};

#endif // LOGIN_H
