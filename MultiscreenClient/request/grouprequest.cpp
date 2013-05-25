#include "grouprequest.h"
#include <QDebug>

GroupRequest::GroupRequest()
{
}

void GroupRequest::setToken(QString token)
{
    m_token = token;
}

void GroupRequest::setGroupList(GroupList *list)
{
    m_groupList = list;
}

void GroupRequest::fillMap()
{
    this->m_UrlParameter.insert("_type", "ws");
    this->m_UrlParameter.insert("_method", "channelGroup");
    this->m_UrlParameter.insert("token", m_token);
}

void GroupRequest::appendPath()
{
    m_path = "channelGroup";
}

bool GroupRequest::analyzeXml(QDomDocument &doc)
{
    QDomElement root = doc.documentElement();
//    qDebug() << "GroupRequest::analyzeXml" << root.childNodes().count();
    for (int j = 0,i = 0; i < root.childNodes().count(); i++)
    {
        if (root.childNodes().at(i).nodeName() == "ChannelGroup")
        {
            m_groupList->append(new Group());
            m_groupList->at(j++)->fromXml(root.childNodes().at(i).toElement());
        }
    }
    return true;
}
