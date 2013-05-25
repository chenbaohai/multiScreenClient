#ifndef MERGECONFIGXML_H
#define MERGECONFIGXML_H

#include <QList>
#include <QString>
#include <QDomElement>

class MergeItem;

class MergeXml
{
public:
    MergeXml();
    void append(MergeItem*);
    void clear();
    QList<MergeItem*>& merges();
    bool save();
    bool load();
    bool del();
private:
    void createChildNode(QDomElement&,MergeItem*,QDomDocument&);
    void createContainItems(QDomElement&,MergeItem*);
    QList<MergeItem*> m_merges;
    QString m_path;
};

#endif // MERGECONFIGXML_H
