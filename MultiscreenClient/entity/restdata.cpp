#include "interactdata.h"
#include "const.h"
#include <QDataStream>
#include <QStringList>
#include <QDebug>

InteractData::InteractData(QObject *parent) :
    BaseData(parent)
{
}

const QByteArray * InteractData::getSendData()
{
    QDataStream sendStream(&m_sendData, QIODevice::ReadWrite);
    sendStream << m_cmd << m_restSendData;
    qDebug() << "QByteArray * InteractData::getSendData" << m_cmd << m_restSendData;
    return &m_sendData;
}

void InteractData::setSendData(int cmd,QString data)
{
    m_cmd = cmd;
    m_restSendData = data.toAscii();
}

QString InteractData::buildUpData(int cmd, QString data)
{
    qDebug() << "InteractData::buildUpData";
    QString result;
    switch(cmd)
    {
    case TOKEN_REQUEST:
    {
        result = "{\"token\":\"";
        data = data.append("\"}");
        result += data;
        break;
    }
    case PREVIEW_REQUEST:
    {
        QStringList list = data.split(",");
        QString temp[4];
        temp[0] = "{\"displayid\":" + list.at(0);
        temp[1] = ",\"dvrid\":" + list.at(1);
        temp[2] = ",\"channelid\":" + list.at(2);
        temp[3] = ",\"smallwindow\":" + list.at(3) + "}";
        result = temp[0] + temp[1] + temp[2] + temp[3];
        qDebug() << "InteractData::buildUpData " << result;
        break;
    }
    case CONFIG_REQUEST:
    {
        qDebug() << "CONFIG_REQUEST";
        QStringList list = data.split(",");
        qDebug() << list.count();
//        for(int i = 0; i < list.count() - 1; i++)
//        {}
        break;
    }
    default:break;
    }
    return result;
}
