#include "group.h"

Group::Group():
    m_groupId(-1),
    m_groupName("")
{
}

Group::~Group()
{
    clear();
}

void Group::clear()
{
    Entity::clear();
    m_groupId = 0;
    m_groupName = "";

    if (!m_groupList.isEmpty())
    {
        qDeleteAll(m_groupList);
        m_groupList.clear();
    }
    if (!m_channelList.isEmpty())
    {
        qDeleteAll(m_channelList);
        m_channelList.clear();
    }
}

bool Group::validates()
{
    return Entity::validates();
}

void Group::fromXml(QDomElement element)
{
    QDomNodeList nodes;
    m_groupId = element.attribute("id").toInt();
    m_groupName = element.attribute("name");

    nodes = element.childNodes();

//    qDebug() << nodes.count();
    for (int i = 0; i < nodes.count(); i++)
    {
//        qDebug() << nodes.at(i).nodeName();
        if (nodes.at(i).nodeName() == "ChannelGroup")
        {
            Group *pGroup = new Group;
            this->addGroupList(pGroup);
            pGroup->fromXml(nodes.at(i).toElement());
            pGroup->fillChannel(nodes.at(i).childNodes());
        }
    }
}

void Group::fillChannel(QDomNodeList nodes)
{
    for (int i = 0; i < nodes.count(); i++)
    {
        QDomElement element;
        element = nodes.at(i).toElement();
        Channel *pChannel = new Channel;
        pChannel->setChannelId(element.attribute("id").toInt());
        pChannel->setChannelName(element.attribute("name"));

        this->addChannelList(pChannel);
    }
}

qint64 Group::getGroupId()
{
    return m_groupId;
}

QString Group::getGroupName()
{
    return m_groupName;
}

void Group::setGroupId(qint64 id)
{
    m_groupId = id;
}

void Group::setGroupName(QString name)
{
    m_groupName = name;
}

GroupList & Group::getGroupList()
{
    return m_groupList;
}

ChannelList & Group::getChannelList()
{
    return m_channelList;
}

void Group::addGroupList(Group *group)
{
    if (group == NULL)
    {
        return;
    }
    m_groupList.append(group);
}

void Group::addChannelList(Channel *channel)
{
    if (channel = NULL)
    {
        return;
    }
    m_channelList.append(channel);
}
