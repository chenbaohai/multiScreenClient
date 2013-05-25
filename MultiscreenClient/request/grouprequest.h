#ifndef GROUPREQUEST_H
#define GROUPREQUEST_H

#include "restrequest.h"
#include "group.h"
class GroupRequest : public RestRequest
{
public:
    GroupRequest();
    void setToken(QString token);
    void setGroupList(GroupList *list);
protected:
    void fillMap();
    void appendPath();
    bool analyzeXml(QDomDocument &doc);

private:
    QString    m_token;
    GroupList *m_groupList;
};

#endif // GROUPREQUEST_H
