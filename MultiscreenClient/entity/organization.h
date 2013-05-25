#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QObject>
#include <QString>
#include <QPoint>

#include "entity.h"
#include "dvr.h"

class Organization;
typedef QList<Organization*> OrgList;

class Organization : public Entity
{
    Q_OBJECT
public:
    explicit Organization(QObject *parent = 0);
    ~Organization();

    void clear();
    bool validates();
    void fromXml(QDomElement element);

    qint64  orgId();
    QString orgName();

    void setOrgName(QString name);
    void setOrgId(qint64 id);

    const OrgList& getOrgList();
    const DvrList& getDvrList();

    void addOrgList(Organization* org);
    void addDvrList(Dvr* dvr);

private:
    qint64   m_orgId;     //机构ID
    QString  m_orgName;   //机构名称
    OrgList  m_orgList;   //子组织机构列表
    DvrList  m_dvrList;   //Dvr列表
};

#endif // Organization_H
