#include "msocket.h"
#include "config/configini.h"
#include "interactdata.h"
#include <QHostAddress>
#include <QByteArray>
#include <QDebug>
#include <QEventLoop>
#include "json/qjson/parser.h"

MSocket::MSocket(QObject *parent) :
    QObject(parent),
    m_waited(true),
    m_Connected(false),
    m_bRead(false)
{
    m_Socket = new QTcpSocket;
//    connect(m_Socket,SIGNAL(connected()),this,SLOT(slot_connected()));
    connect(m_Socket,SIGNAL(readyRead()),this,SLOT(readyreadSlot()));
    connect(m_Socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slot_error(QAbstractSocket::SocketError)));
    this->connect(m_Socket,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(timeoutSlot()));

    m_timer.setInterval(5*1000);
    m_baseData=new InteractData;
}

MSocket::~MSocket()
{
    if(m_Socket)
    {
        m_Socket->abort();
        m_Socket->close();
        delete m_Socket;

        m_Socket=NULL;
    }

//    if(m_baseData)
//    {
//        delete m_baseData;
//        m_baseData=NULL;
//    }
}

bool MSocket::connectServer()
{ 
//    if(m_Connected) return true;
//    m_Socket->connectToHost(QHostAddress(ConfigIni::instance()->serverIp()),\
//                            ConfigIni::instance()->serverPort());
//    if(!m_Socket->waitForConnected(3*1000))
//    {
////        qDebug()<<"socket：" << m_Socket->errorString();
//        return false;
//    }

    m_Connected=true;
    return m_Connected;
}

bool MSocket::sendData(InteractData *entity)
{
//    m_baseData = entity;
//    QTcpSocket *socket=m_Socket;//createSocket();

//    const QByteArray* block = m_baseData->getSendData();
//    qDebug() << "sendData" << block->size()<<m_baseData->cmd();
//    qint64 size;
//    size = block->size();
//    socket->write((char*)&size,sizeof(qint64));
//    socket->write(block->data(),size);
    return true;
}

void MSocket::slot_connected()
{
    const QByteArray* block = m_baseData->getSendData();
    qDebug() << "MSocket::slot_connected" << block->size() << block<<m_baseData->cmd();
    qint64 size;
    size = block->size();
    m_Socket->write((char*)&size,sizeof(qint64));
    m_Socket->write(block->data(),size);
}

void MSocket::slot_error(QAbstractSocket::SocketError)
{
    qDebug()<<"socket error ：" << m_Socket->errorString();
    m_Connected=false;
    emit doneSig();

//    m_timer.start();
}

void MSocket::slot_read()
{
    int blockSize = 0;

    if(!m_Socket->property("read").toBool())
    {
        qDebug()<<"readall"<<m_Socket->readAll();
        return;
    }
//    m_Socket=static_cast<QTcpSocket *>(this->sender());

    while(m_Socket->bytesAvailable() >= sizeof(qint64))
    {
        if(blockSize == 0)
        {
            if(m_Socket->bytesAvailable() < sizeof(qint64))
            {
                emit doneSig();
                return;
            }
            m_Socket->read((char*)&blockSize, sizeof(qint64));  // read blockSize
        }

        if(m_Socket->bytesAvailable() < blockSize)				// have no enugh data
        {
            emit doneSig();
            return;
        }
        m_baseData->data()->resize(blockSize);
        QByteArray _data = m_Socket->read(blockSize);
        qDebug()<<"start read data:"<<_data;
        *m_baseData->data() = _data;
        qDebug()<<"end read data:"<<_data;
    }
//    delete m_Socket;
//    m_Socket=NULL;
    emit doneSig();
}

void MSocket::setReadFlag(bool flag)
{
    m_bRead = flag;
}

void MSocket::wait()
{
    qDebug()<<"enter wait------------------";
    QEventLoop q;
    connect(this, SIGNAL(doneSig()), &q, SLOT(quit()));
    q.exec();
    qDebug()<<"exit loop-------------------";
}

void MSocket::onConnected()
{
    qDebug()<<"connected";
    m_Connected=true;
    emit doneSig();
}

void MSocket::timeoutSlot()
{
    if(m_Connected)
        m_timer.stop();
    this->connectServer();
}

void MSocket::readyreadSlot()
{
    int blockSize=0;
//    QTcpSocket *socket=m_Socket;//static_cast<QTcpSocket *>(this->sender());
    while(m_Socket->bytesAvailable() >= sizeof(qint64))
    {
        if(blockSize == 0)
        {
            if(m_Socket->bytesAvailable() < sizeof(qint64))
            {
                emit doneSig();
                return;
            }
            m_Socket->read((char*)&blockSize, sizeof(qint64));  // read blockSize
        }

        if(m_Socket->bytesAvailable() < blockSize)
        {
            emit doneSig();
            return;
        }
        QByteArray data = m_Socket->read(blockSize);
        this->processData(data);
//        delete socket;
//        socket=NULL;
        blockSize = 0;
    }
}

void MSocket::processData(QByteArray &array)
{
    QDataStream in(&array,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_5);

    int key;
    QByteArray data;
    in >> key >> data;
    qDebug()<<key<<data;

    switch(key)
    {
    case INIT_RESPONSE: //
    {
        this->dealInitProtocol(data);
        break;
    }
    default:
        break;
    }

        emit doneSig();
}

void MSocket::setwait(bool value)
{
    m_waited=value;
}

void MSocket::sendMsg(int cmd, QString msg)
{   
    m_baseData->setSendData(cmd, msg);
    if (sendData(m_baseData))
    {
//        m_baseData.analyze();
    }
    else
    {
        qDebug() << "MSocket::sendMsg发送失败";
        return;
    }
}

QTcpSocket * MSocket::createSocket()
{
    QTcpSocket * socket=new QTcpSocket;
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyreadSlot()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slot_error(QAbstractSocket::SocketError)));
    this->connect(socket,SIGNAL(connected()),this,SLOT(onConnected()));
    socket->connectToHost(QHostAddress(ConfigIni::instance()->serverIp()),\
                            ConfigIni::instance()->serverPort());
    return socket;
}

void MSocket::dealInitProtocol(const QByteArray &body)
{
    QJson::Parser  parser;
    bool ok;
    QVariant var=parser.parse (body,&ok);
    if(!ok){
        return;
    }
    QVariantMap dismap =var.toMap();

    m_Rslt = dismap.value("result").toInt();
    qDebug()<<"dealInitProtocol->result:"<<m_Rslt;
    emit finishedSig(m_Rslt);
}
