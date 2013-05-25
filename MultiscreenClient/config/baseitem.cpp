#include "baseitem.h"

BaseItem::BaseItem():
    m_row(1),
    m_col(1),
    m_rowspan(1),
    m_colspan(1),
    m_displayid("")
{
}

BaseItem::BaseItem(int row,int col ,int rowspan,int colspan,QString displayid)
{
    this->m_row=row;
    this->m_col=col;
    this->m_rowspan=rowspan;
    this->m_colspan=colspan;
    this->m_displayid=displayid;
}

BaseItem::~BaseItem()
{

}

int BaseItem::row()
{
    return this->m_row;
}

int BaseItem::col()
{
    return this->m_col;
}

int BaseItem::rowspan()
{
    return this->m_rowspan;
}

int BaseItem::colspan()
{
    return this->m_colspan;
}

void BaseItem::setRow(int value)
{
    this->m_row=value;
}

void BaseItem::setCol(int value)
{
    this->m_col=value;
}

void BaseItem::setRowSpan(int value)
{
    this->m_rowspan=value;
}

void BaseItem::setColSpan(int value)
{
    this->m_colspan=value;
}

void BaseItem::setDisplayID(QString value)
{
    this->m_displayid=value;
}

QString BaseItem::displayID()
{
    return this->m_displayid;
}
