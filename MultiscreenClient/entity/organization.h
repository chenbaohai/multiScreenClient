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
    qint64   m_orgId;     //����ID
    QString  m_orgName;   //��������
    OrgList  m_orgList;   //����֯�����б�
    DvrList  m_dvrList;   //Dvr�б�
};

#endif // Organization_H
