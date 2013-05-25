#include <QString>
#include "scheme.h"

#include <QDebug>

Scheme::Scheme():
    m_schemeName(""),
    m_groupIds(""),
    m_groupNames("")
{
}

Scheme::~Scheme()
{
    clear();
}

void Scheme::clear()
{
    Entity::clear();

//    if (!m_schemeList.isEmpty())
//    {
//        qDeleteAll(m_schemeList);
//        m_schemeList.clear();
//    }
}

bool Scheme::validates()
{
    Entity::validates();
}

void Scheme::fromXml(QDomElement element)
{
//    QDomNodeList nodes;
    m_schemeName = element.text();
    m_groupIds = element.attribute("GroupIds");
    m_groupNames = element.attribute("Group");
    m_time = element.attribute("Time").toInt();
    m_discribe = element.attribute("Decribe");
    m_layoutName = element.attribute("LayoutName").toInt();
    m_createFlag = (bool)element.attribute("IsCreated").toInt();
    m_extendFlag = (bool)element.attribute("IsExtend").toInt();

//    nodes = element.childNodes();

//    for (int i = 0; i < nodes.count(); i++)
//    {
//        if (nodes.at(i).nodeName() == "CirculateInfo")
//        {
//            Scheme *pScheme = new Scheme;
//            this->addSchemeList(pScheme);
//        }
//    }
}

QString Scheme::getSchemeName()
{
    return m_schemeName;
}

QString Scheme::getGroupIds()
{
    return m_groupIds;
}

QString Scheme::getGroupNames()
{
    return m_groupNames;
}

int Scheme::getTime()
{
    return m_time;
}

QString Scheme::getDiscribe()
{
    return m_discribe;
}

int Scheme::getLayoutName()
{
    return m_layoutName;
}

bool Scheme::getCreateFlag()
{
    return m_createFlag;
}

bool Scheme::getExtendFlag()
{
    return m_extendFlag;
}

void Scheme::setSchemeName(QString name)
{
    m_schemeName = name;
}

void Scheme::setGroupIds(QString ids)
{
    m_groupIds = ids;
}

void Scheme::setGroupNames(QString names)
{
    m_groupNames = names;
}

void Scheme::setTime(int time)
{
    m_time = time;
}

void Scheme::setDiscribe(QString discribe)
{
    m_discribe = discribe;
}

void Scheme::setLayoutName(int num)
{
    m_layoutName = num;
}

void Scheme::setCreateFlag(bool flag)
{
    m_createFlag = flag;
}

void Scheme::setExtendFlag(bool flag)
{
    m_extendFlag = flag;
}

//SchemeList & Scheme::getSchemeList()
//{
//    return m_schemeList;
//}

//void Scheme::addSchemeList(Scheme *pScheme)
//{
//    m_schemeList.append(pScheme);
//}
