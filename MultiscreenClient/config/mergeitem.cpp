#include "mergeitem.h"

MergeItem::MergeItem()
{
}

bool MergeItem::mergeFlag()
{
    return m_mergeFlag;
}

void MergeItem::setMergeFlag(bool flag)
{
    m_mergeFlag = flag;
}

bool MergeItem::useFlag()
{
    return m_useFlag;
}

void MergeItem::setUesFlag(bool flag)
{
    m_useFlag = flag;
}

QList<MergeItem *> * MergeItem::containItems()
{
    return &m_containItems;
}
