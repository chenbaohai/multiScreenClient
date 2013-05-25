#ifndef CHANNEL_H
#define CHANNEL_H

#include "entity.h"

class Channel;
typedef QList<Channel*> ChannelList;

class Channel : public Entity
{
    Q_OBJECT
public:
    explicit Channel(QObject *parent = 0);
    ~Channel();
    Channel(const Channel& channel);
    Channel& operator = (const Channel& channel);

    qint64  channelId() const;
    QString channelName() const;
    qint64  channelNo() const;
    qint64  dvrId() const;
    qint64  matrixCode() const;

    void    setChannelId(const qint64 id);
    void    setChannelName(const QString name);
    void    setChannelNo(const qint64 number);
    void    setDvrId(const qint64 dvrId);
    void    setMatrixCode(const qint64 code);

private:
    qint64  m_channelId;    //通道id
    QString m_channelName;  //通道名字
    qint64  m_channelNo;    //通道号
    qint64  m_dvrId;        //该通道关联的DVR
    qint64  m_matrixCode;   //矩阵号
};

#endif // CHANNEL_H
