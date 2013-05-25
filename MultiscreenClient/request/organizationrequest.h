#ifndef ORGANIZATIONREQUEST_H
#define ORGANIZATIONREQUEST_H

#include "restrequest.h"
#include "organization.h"
#include <QDomDocument>

class OrganizationRequest : public RestRequest
{
public:
    OrganizationRequest(QObject *parent = 0);
    void setToken(QString token);
    void setOrgList(OrgList *list);
protected:
    void fillMap();
    void appendPath();
    bool analyzeXml(QDomDocument &doc);

private:
    QString m_token;
    OrgList *m_orgList;
};

#endif // ORGANIZATIONREQUEST_H
