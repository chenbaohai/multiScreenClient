#ifndef SCHEMEXML_H
#define SCHEMEXML_H

#include <QList>
#include <QString>

class SchemeItem;
class SchemeXml
{
public:
    SchemeXml();
    void append(SchemeItem *);
    void append(int, QString, QString, int, QString, bool, int, QString,QString);
    QList<SchemeItem*> getItems();
    void setSchemeXml(SchemeItem*);
    bool save();
    bool load(QString);
    bool deleteItem(SchemeItem *);
    QString getSchemeXml();
private:
    QList<SchemeItem*> m_items;
    QString m_schemeXml;
};

#endif // SCHEMEXML_H
