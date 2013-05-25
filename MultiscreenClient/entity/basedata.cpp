#include "basedata.h"
#include "json/qjson/parser.h"
#include "const.h"
#include <QIODevice>
#include <QDataStream>
#include <QVariant>
#include <QVariantMap>
#include <QDebug>

BaseData::BaseData(QObject *parent) :
    QObject(parent)
{

}

BaseData::~BaseData()
{
}
QByteArray *BaseData::data()
{
    return &m_recvData;
}

void BaseData::analyze()
{
    if(m_recvData.isEmpty()) return;
    qDebug()<<"analyze json:"<<m_recvData;
    QDataStream in(&m_recvData,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_5);
    int recCmd;
    QByteArray temp;
    in>>recCmd>>temp;
    /*  5.0版的json类解析
   // QByteArray temp = m_recvData.mid(4,len);
    QJsonDocument  doc = QJsonDocument::fromJson(temp);
    QJsonObject obj = doc.object();
    m_recvCode = (int)obj.value("result").toDouble();
//    if(m_recvCode==0){
//        return ;
//    }
*/
    QJson::Parser  parser;
    bool ok;
    QVariant var=parser.parse (temp,&ok);
    if(!ok){
        return;
    }
    QVariantMap dismap =var.toMap();

    m_recvCode = dismap.value("result").toInt();

}

const QByteArray *BaseData::getSendData()
{
    QDataStream sendStream(&m_sendData, QIODevice::ReadWrite);
    sendStream << m_cmd ;
    return &m_sendData;
}

int BaseData::recvCode()
{
    return m_recvCode;
}

void BaseData::setCmd(int cmd)
{
    m_cmd = cmd;
}

int BaseData::cmd()
{
    return this->m_cmd;
}
