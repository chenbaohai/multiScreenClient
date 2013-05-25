#include "organizationrequest.h"
#include <QDebug>

OrganizationRequest::OrganizationRequest(QObject *parent ):
    RestRequest(parent)
{

}

void OrganizationRequest::setToken(QString token)
{
    m_token = token;
}

void OrganizationRequest::setOrgList(OrgList *list)
{
    m_orgList = list;
}

void OrganizationRequest::fillMap()
{
    this->m_UrlParameter.insert("_type","ws");
    this->m_UrlParameter.insert("_method", "getVisibleOrgs");
    this->m_UrlParameter.insert("token",m_token);
}

void OrganizationRequest::appendPath()
{
    m_path = "org";
}

bool OrganizationRequest::analyzeXml(QDomDocument &doc)
{
    QDomElement root = doc.documentElement();
//    qDebug() << "OrganizationTree::getOrganizationInfo()" << root.childNodes().count();
    for (int j = 0,i = 0; i < root.childNodes().count(); i++)
    {
        if (root.childNodes().at(i).nodeName() == "Organization")
        {
            m_orgList->append(new Organization());
            m_orgList->at(j++)->fromXml(root.childNodes().at(i).toElement());
        }
    }
    return true;
}
