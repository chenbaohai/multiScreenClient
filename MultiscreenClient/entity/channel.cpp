#include "channel.h"

Channel::Channel(QObject *parent) :
    Entity(parent),
    m_channelId(-1),
    m_channelName(""),
    m_channelNo(-1),
    m_dvrId(-1),
    m_matrixCode(-1)
{
}

Channel::Channel(const Channel& channel)
{
    m_channelId = channel.m_channelId;
    m_channelName = channel.m_channelName;
    m_channelNo = channel.m_channelNo;
    m_dvrId = channel.m_dvrId;
    m_matrixCode = channel.m_matrixCode;
}

Channel& Channel::operator = (const Channel& channel)
{
    if (this == &channel)
    {
        return *this;
    }

    m_channelId = channel.m_channelId;
    m_channelName = channel.m_channelName;
    m_channelNo = channel.m_channelNo;
    m_dvrId = channel.m_dvrId;
    m_matrixCode = channel.m_matrixCode;

    return *this;
}

Channel::~Channel()
{

}

qint64 Channel::channelId() const
{
    return m_channelId;
}

QString Channel::channelName() const
{
    return m_channelName;
}

qint64 Channel::channelNo() const
{
    return m_channelNo;
}

qint64 Channel::dvrId() const
{
    return m_dvrId;
}

qint64 Channel::matrixCode() const
{
    return m_matrixCode;
}

void Channel::setChannelId(const qint64 id)
{
    m_channelId = id;
}

void Channel::setChannelName(const QString name)
{
    m_channelName = name;
}

void Channel::setChannelNo(const qint64 number)
{
    m_channelNo = number;
}

void Channel::setDvrId(const qint64 dvrId)
{
    m_dvrId = dvrId;
}

void Channel::setMatrixCode(const qint64 code)
{
    m_matrixCode = code;
}
