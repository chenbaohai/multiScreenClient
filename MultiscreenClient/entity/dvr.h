#ifndef Dvr_H
#define Dvr_H

#include <QObject>
#include <QDomDocument>

#include "entity.h"
#include "channel.h"

class Dvr;
typedef QList<Dvr*> DvrList;

class Dvr : public Entity
{
    Q_OBJECT
public:
    explicit Dvr(QObject *parent = 0);
    Dvr(const Dvr& dvr);
    ~Dvr();
    Dvr& operator =(const Dvr &dvr);

    QString dvrName() const;
    qint64  dvrId() const;
    QString dvrIp() const;
    qint64  dvrPort() const;
    QString dvrUserName() const;
    QString dvrPassword() const;
    QString dvrType() const;

    void setDvrName(const QString name);
    void setDvrId(const qint64 id);
    void setDvrIp(const QString ip);
    void setDvrPort(const qint64 port);
    void setDvrUserName(const QString userName);
    void setDvrPassword(const QString password);
    void setDvrType(const QString type);

    const   ChannelList& channelList();
    void    addChannelList(Channel *channel);
    void    fillChannel(QDomNodeList nodes, int dvrId);           //把通道信息显示在结构树上

private:
    QString     m_dvrName;         //名称
    qint64      m_dvrId;           //编号
    QString     m_dvrIp;
    qint64      m_dvrPort;
    QString     m_dvrUserName;     //Dvr登入用户名
    QString     m_dvrPassword;     //密码
    QString     m_dvrType;         //设备类型

    ChannelList m_channelList;
};

#endif // Dvr_H
