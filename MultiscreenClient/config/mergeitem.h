#ifndef MERGEITEM_H
#define MERGEITEM_H

#include "baseitem.h"
#include <QList>

class MergeItem : public BaseItem
{
public:
    MergeItem();

    bool mergeFlag();
    void setMergeFlag(bool);
    bool useFlag();
    void setUesFlag(bool);
    QList<MergeItem*>* containItems();
private:
    bool m_mergeFlag;
    bool m_useFlag;
    QList<MergeItem*> m_containItems;
};

#endif // MERGEITEM_H
