#ifndef SCHEMEITEM_H
#define SCHEMEITEM_H

#include <QString>

class SchemeItem
{
public:
    SchemeItem();
    SchemeItem(int, QString, QString, int, QString, bool, int, QString,QString);
    ~SchemeItem();

    int getTime();
    void setTime(int);
    QString getGroupName();
    void setGroupName(QString);
    QString getGroupIds();
    void setGroupIds(QString);
    int getLayout();
    void setLayout(int);
    QString getDiscribe();
    void setDiscribe(QString);
    bool getExtendFlag();
    void setExtendFlag(bool);
    int getCreateFlag();
    void setCreateFlag(int);
    QString getSchemeName();
    void setSchemeName(QString);
    void setOriginalName(QString);
    QString getOriginalName();
private:
    int     m_time;
    QString m_groupName;
    QString m_groupIds;
    int     m_layout;
    QString m_discribe;
    bool    m_extendFlag;
    int    m_createFlag;
    QString m_schemeName;
    QString m_originalName;
};

#endif // SCHEMEITEM_H
