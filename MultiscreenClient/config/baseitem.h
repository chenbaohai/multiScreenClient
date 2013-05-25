#ifndef BASEITEM_H
#define BASEITEM_H

#include <QString>

class BaseItem
{
public:
    BaseItem();
    BaseItem(int,int,int,int,QString displayid);
    ~BaseItem();

    int row();
    int col();
    int rowspan();
    int colspan();
    QString displayID();

    void setRow(int);
    void setCol(int);
    void setRowSpan(int);
    void setColSpan(int);
    void setDisplayID(QString value);

protected:
    //所在行号
    int m_row;
    //所在列号
    int m_col;
    //行跨度
    int m_rowspan;
    //列跨度
    int m_colspan;

    QString m_displayid;
};

#endif // BASEITEM_H
