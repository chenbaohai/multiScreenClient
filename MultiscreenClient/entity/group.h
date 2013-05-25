#ifndef GROUP_H
#define GROUP_H

#include "entity.h"
#include "channel.h"

class Group;
typedef QList<Group*> GroupList;

class Group : public Entity
{
public:
    Group();
    ~Group();

    void clear();
    bool validates();
    void fromXml(QDomElement);

    void fillChannel(QDomNodeList);
    qint64  getGroupId();
    QString getGroupName();
    void setGroupId(qint64);
    void setGroupName(QString);

    GroupList& getGroupList();
    ChannelList& getChannelList();
    void addGroupList(Group*);
    void addChannelList(Channel*);

private:
    qint64      m_groupId;
    QString     m_groupName;
    GroupList   m_groupList;
    ChannelList m_channelList;
};

#endif // GROUP_H
