#include "schemeitem.h"
#include <QDomDocument>

SchemeItem::SchemeItem():
    m_time(0),
    m_groupName(""),
    m_groupIds(""),
    m_layout(0),
    m_discribe(""),
    m_extendFlag(false),
    m_createFlag(-1),
    m_schemeName(""),
    m_originalName("")
{

}

SchemeItem::SchemeItem(int time, QString groupName, QString groupIds, int layout, QString discribe, bool extendFlag, int createFlag, QString schemeName,QString originalName):
    m_time(time),
    m_groupName(groupName),
    m_groupIds(groupIds),
    m_layout(layout),
    m_discribe(discribe),
    m_extendFlag(extendFlag),
    m_createFlag(createFlag),
    m_schemeName(schemeName),
    m_originalName(originalName)
{

}

SchemeItem::~SchemeItem()
{

}

int SchemeItem::getTime()
{
    return m_time;
}

void SchemeItem::setTime(int time)
{
    m_time = time;
}

QString SchemeItem::getGroupName()
{
    return m_groupName;
}

void SchemeItem::setGroupName(QString name)
{
    m_groupName = name;
}

QString SchemeItem::getGroupIds()
{
    return m_groupIds;
}

void SchemeItem::setGroupIds(QString ids)
{
    m_groupIds = ids;
}

int SchemeItem::getLayout()
{
    return m_layout;
}

void SchemeItem::setLayout(int layout)
{
    m_layout = layout;
}

QString SchemeItem::getDiscribe()
{
    return m_discribe;
}

void SchemeItem::setDiscribe(QString discribe)
{
    m_discribe = discribe;
}

bool SchemeItem::getExtendFlag()
{
    return m_extendFlag;
}

void SchemeItem::setExtendFlag(bool flag)
{
    m_extendFlag = flag;
}

int SchemeItem::getCreateFlag()
{
    return m_createFlag;
}

void SchemeItem::setCreateFlag(int flag)
{
    m_createFlag = flag;
}

QString SchemeItem::getSchemeName()
{
    return m_schemeName;
}

void SchemeItem::setSchemeName(QString name)
{
    m_schemeName = name;
}

void SchemeItem::setOriginalName(QString value)
{
    this->m_originalName=value;
}

QString SchemeItem::getOriginalName()
{
    return this->m_originalName;
}
