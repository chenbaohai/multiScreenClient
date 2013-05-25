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
//    qDebug() << "QByteArray * InteractData::getSendData" << m_cmd << m_restSendData;
    return &m_sendData;
}

void InteractData::setSendData(int cmd,QString data)
{
    m_cmd = cmd;
    m_restSendData = buildUpData(cmd, data).toAscii();
//    m_restSendData = data.toAscii();
}

QString InteractData::buildUpData(int cmd, QString data)
{
    QString result = NULL;


    //有些发送字符命令比较简单则直接发送
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
        QString tempStr = "{\"displayid\":" + list.at(0);
        tempStr += ",\"dvrid\":" + list.at(1);
        tempStr += ",\"channelid\":" + list.at(2);
        tempStr += ",\"smallwindow\":" + list.at(3) + "}";
        result = tempStr;
        qDebug() << "InteractData::buildUpData " << result;
        break;
    }
    case CONFIG_REQUEST:
    {
        QStringList list = data.split(":");

        for (int i = 0; i < list.count() - 1; i++)
        {
            QStringList subList = list.at(i).split(",");
            QString tempStr = "{\"displayid\":" + subList.at(0);
            tempStr += ",\"row\":" + subList.at(1);
            tempStr += ",\"col\":" + subList.at(2) + "}";
            result += tempStr;
            if (i == list.count() - 2)
                continue;
            result += ",";
        }
        result = "[" + result + "]";
        qDebug() << "InteractData::buildUpData " << result;
        break;
    }
    case SPLITWINDOW_REQUEST:
    {
        QStringList list = data.split(",");
        QString tempStr = "{\"displayid\":" + list.at(0);
        tempStr += ",\"number\":" + list.at(1) + "}";
        result = "[" + tempStr + "]";
        qDebug() << "SPLITWINDOW_REQUEST Data " << result;
        break;
    }
    case STOPPREVIEW_REQUEST:
    {
        QStringList list = data.split(",");
        QString tempStr = "{\"displayid\":" + list.at(0);
        tempStr += ",\"smallwindow\":" + list.at(1) + "}";
        result = tempStr;
        qDebug() << "STOPPREVIEW_REQUEST Data" << result;
        break;
    }
    case STRETCH_REQUEST:
    {
        QStringList list = data.split(":");
        QString tempStr = NULL;
        for(int i = 0; i < list.count(); i++)
        {
            if (list.at(i).count() != 1)
            {
                QStringList mergeList = list.at(i).split(";");
                tempStr += "{\"displayid\":" + mergeList.at(0);
//                QStringList splitList = mergeList.at(1).split(",");
//                QString str = splitList.at(1) + "," + splitList.at(0);
                tempStr += ",\"displayids\":\"" + mergeList.at(1) + "\"}";
            }
            else
            {
                tempStr += "{\"displayid\":" + list.at(i);
                tempStr += ",\"displayids\":\"" + list.at(i) + "\"}";
            }
            tempStr += ",";
        }
        tempStr.remove(tempStr.count() - 1, tempStr.count() - 2);
        result = "[" + tempStr + "]";
        qDebug() << "STRETCH_REQUEST Data" << result;
        break;
    }
    case STARTCIRCULATE_REQUEST:
    {
        QStringList list = data.split(",");
        QString tempStr = "{\"displayid\":" + list.at(0);
        tempStr += ",\"schedulename\":\"" + list.at(1) + "\"}";
        result = tempStr;
        qDebug() << "STARTCIRCULATE_REQUEST Data" << result;
        break;
    }
    case STOPCIRCULATE_REQUEST:
    {
        QStringList list = data.split(",");
        QString tempStr = "{\"displayid\":" + list.at(0);
        tempStr += ",\"schedulename\":\"" + list.at(1) + "\"}";
        result = tempStr;
        qDebug() << "STOPCIRCULATE_REQUEST Data" << result;
        break;
    }
    case FULLPREVIEW_REQUEST:
    {
        QStringList list = data.split(",");
        QString tempStr = "{\"displayid\":" + list.at(0);
        tempStr += ",\"smallwindow\":" + list.at(1);
        tempStr += ",\"fullpreview\":" + list.at(2) + "}";
        result = tempStr;
        qDebug() << "FULLPREVIEW_REQUEST Data" << result;
        break;
    }
    default:
    {
        result = data;
        break;
    }
    }

    return result;
}
