#include "organization.h"
#include <QDebug>

Organization::Organization(QObject *patent) :
    Entity(patent),
    m_orgId(-1),
    m_orgName("")
{

}

Organization::~Organization()
{
    clear();
}

void Organization::clear()
{
    Entity::clear();
    m_orgId = 0;
    m_orgName = "";

    if (!m_orgList.isEmpty())
    {
        qDeleteAll(m_orgList);
        m_orgList.clear();
    }
    if (!m_dvrList.isEmpty())
    {
        qDeleteAll(m_dvrList);
        m_dvrList.clear();
    }
}

bool Organization::validates()
{
    return Entity::validates();
}

void Organization::fromXml(QDomElement element)
{
    QDomNodeList nodes;
    m_orgId = element.attribute("id").toInt();
    m_orgName = element.attribute("name");
//    qDebug() << m_orgName << m_orgId;
    nodes = element.childNodes();

//    qDebug() << nodes.count();
    for (int i = 0; i < nodes.count(); i++)
    {
//        qDebug() << nodes.at(i).nodeName();
        if (nodes.at(i).nodeName() == "Organization")
        {
            Organization *pOrg = new Organization;
            this->addOrgList(pOrg);
            pOrg->fromXml(nodes.at(i).toElement());
        }

        if (nodes.at(i).nodeName() == "Dvr")
        {
            QDomElement dvrElement;
            dvrElement = nodes.at(i).toElement();
            Dvr *pDvr = new Dvr;
            pDvr->setDvrName(dvrElement.attribute("name"));
            pDvr->setDvrId(dvrElement.attribute("id").toInt());
            pDvr->setDvrIp(dvrElement.attribute("serverHost"));
            pDvr->setDvrPort(dvrElement.attribute("serverPort").toInt());
            pDvr->setDvrUserName(dvrElement.attribute("loginUser"));
            pDvr->setDvrPassword(dvrElement.attribute("password"));
            pDvr->setDvrType(dvrElement.attribute("deviceType"));

//            qDebug() << nodes.at(i).childNodes().count() << dvrElement.attribute("name");
            pDvr->fillChannel(nodes.at(i).childNodes(), pDvr->dvrId());
            this->addDvrList(pDvr);
        }
    }
}

qint64 Organization::orgId()
{
    return m_orgId;
}

QString Organization::orgName()
{
    return m_orgName;
}

void Organization::setOrgId(qint64 id)
{
    m_orgId = id;
}

void Organization::setOrgName(QString orgName)
{
    m_orgName = orgName;
}

const OrgList& Organization::getOrgList()
{
    return m_orgList;
}

void Organization::addOrgList(Organization* org)
{
    if (org == NULL)
    {
        return;
    }
    m_orgList.append(org);
}

const DvrList & Organization::getDvrList()
{
    return m_dvrList;
}

void Organization::addDvrList(Dvr *dvr)
{
    if (dvr == NULL)
    {
        return;
    }
    m_dvrList.append(dvr);
}
