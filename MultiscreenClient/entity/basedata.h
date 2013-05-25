#ifndef BASEDATA_H
#define BASEDATA_H
#include <QByteArray>
#include <QObject>

class QByteArray;

class BaseData :public QObject
{
    Q_OBJECT
public:
    BaseData(QObject *parent = 0);
    ~BaseData();
    QByteArray* data();
    virtual void analyze();
    virtual const QByteArray* getSendData();
    int recvCode();
    void setCmd(int cmd);
    int cmd();

protected:
    QByteArray m_recvData;
    QByteArray m_sendData;
    int m_cmd;
    int m_recvCode;
};

#endif // BASEDATA_H
