#include "dvr.h"
//#include "entity_global.h"

#include <QDebug>

Dvr::Dvr(QObject *parent) :
    Entity(parent),
    m_dvrId(-1),
    m_dvrPort(-1)
{

}

Dvr::Dvr(const Dvr& dvr)
{
    m_dvrName = dvr.m_dvrName;
    m_dvrId = dvr.m_dvrId;
    m_dvrIp = dvr.m_dvrIp;
    m_dvrPort = dvr.m_dvrPort;
    m_dvrUserName = dvr.m_dvrUserName;
    m_dvrPassword = dvr.m_dvrPassword;
    m_dvrType = dvr.m_dvrType;

    ChannelList list = dvr.m_channelList;
    if (list.count() > 0)
    {
        ChannelList::iterator iter = list.begin();
        for (; iter != list.end(); iter++)
        {
            Channel *channel = new Channel;
            *channel = **iter;
            m_channelList.append(channel);
        }
    }
}

Dvr& Dvr::operator = (const Dvr& dvr)
{
    if (this == &dvr)
    {
        return *this;
    }

    m_dvrName = dvr.m_dvrName;
    m_dvrId = dvr.m_dvrId;
    m_dvrIp = dvr.m_dvrIp;
    m_dvrPort = dvr.m_dvrPort;
    m_dvrUserName = dvr.m_dvrUserName;
    m_dvrPassword = dvr.m_dvrPassword;
    m_dvrType = dvr.m_dvrType;

    ChannelList list = dvr.m_channelList;
    if (list.count() > 0)
    {
        ChannelList::iterator iter = list.begin();
        for (; iter != list.end(); iter++)
        {
            Channel *channel = new Channel;
            *channel = **iter;
            m_channelList.append(channel);
        }
    }

    return *this;
}

Dvr::~Dvr()
{
    if (!m_channelList.isEmpty())
    {
        qDeleteAll(m_channelList);
        m_channelList.clear();
    }
}

QString Dvr::dvrName() const
{
    return m_dvrName;
}

qint64 Dvr::dvrId() const
{
    return m_dvrId;
}

QString Dvr::dvrIp() const
{
    return m_dvrIp;
}

qint64 Dvr::dvrPort() const
{
    return m_dvrPort;
}

QString Dvr::dvrUserName() const
{
    return m_dvrUserName;
}

QString Dvr::dvrPassword() const
{
    return m_dvrPassword;
}

QString Dvr::dvrType() const
{
    return m_dvrType;
}

void Dvr::setDvrName(const QString name)
{
    m_dvrName = name;
}

void Dvr::setDvrId(const qint64 id)
{
    m_dvrId = id;
}

void Dvr::setDvrIp(const QString ip)
{
    m_dvrIp = ip;
}

void Dvr::setDvrPort(const qint64 port)
{
    m_dvrPort = port;
}

void Dvr::setDvrUserName(const QString userName)
{
    m_dvrUserName = userName;
}

void Dvr::setDvrPassword(const QString password)
{
    m_dvrPassword = password;
}

void Dvr::setDvrType(const QString type)
{
    m_dvrType = type;
}

const ChannelList& Dvr::channelList()
{
    return m_channelList;
}

void Dvr::addChannelList(Channel *channel)
{
    if (channel == NULL)
    {
        return;
    }
    m_channelList.append(channel);
}

void Dvr::fillChannel(QDomNodeList nodes, int dvrId)
{
    for (int i = 0; i < nodes.count(); i++)
    {
        QDomElement element;
        element = nodes.at(i).toElement();
        Channel *pChannel = new Channel;
        pChannel->setChannelId(element.attribute("id").toInt());
        pChannel->setChannelNo(element.attribute("channelNo").toInt());
        pChannel->setMatrixCode(element.attribute("matrixCode").toInt());
        pChannel->setChannelName(element.attribute("name"));
        pChannel->setDvrId(dvrId);
//        qDebug() << element.attribute("name");
        this->addChannelList(pChannel);
    }
}
