#ifndef SCHEME_H
#define SCHEME_H

#include "entity.h"

class Scheme : public Entity
{
public:
    Scheme();
    ~Scheme();

    void clear();
    bool validates();
    void fromXml(QDomElement);

    QString getSchemeName();
    QString getGroupIds();
    QString getGroupNames();
    int getTime();
    QString getDiscribe();
    int getLayoutName();
    bool getCreateFlag();
    bool getExtendFlag();
    void setSchemeName(QString);
    void setGroupIds(QString);
    void setGroupNames(QString);
    void setTime(int);
    void setDiscribe(QString);
    void setLayoutName(int);
    void setCreateFlag(bool);
    void setExtendFlag(bool);

private:
    QString m_schemeName;
    QString m_groupIds;
    QString m_groupNames;
    int     m_time;
    QString m_discribe;
    int     m_layoutName;
    bool    m_createFlag;
    bool    m_extendFlag;
};

#endif // SCHEME_H
