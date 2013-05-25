#ifndef MSOCKET_H
#define MSOCKET_H

#include <QObject>
#include <QTcpSocket> 
#include <QTimer>
#include "interactdata.h"
#include "const.h"

class MSocket : public QObject
{
    Q_OBJECT
public:
    explicit MSocket(QObject *parent = 0);
    ~MSocket();
    bool connectServer();
    bool sendData(InteractData* entity);

    void setReadFlag(bool);    
    void setwait(bool);
    void sendMsg(int cmd,QString msg);
signals:
    void doneSig();
    void finishedSig(int );
private slots:
    void slot_connected();
    void slot_error(QAbstractSocket::SocketError);
    void slot_read();
    void onConnected();

    void timeoutSlot();

    void readyreadSlot();

private:
    QTcpSocket   *m_Socket;
    InteractData *m_baseData;
    bool          m_bRead;
    bool          m_Connected;
    bool          m_waited;
    QTimer m_timer;
    int m_Rslt;

    void wait();
    void processData(QByteArray& array);
    QTcpSocket *createSocket();
    void dealInitProtocol(const QByteArray & body);
};

#endif // MSOCKET_H
