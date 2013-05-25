#ifndef GROUPTREE_H
#define GROUPTREE_H

#include "basetreewidget.h"
#include "group.h"


class GroupTree : public BaseTreeWidget
{
public:
    GroupTree(QWidget *parent = 0);
    ~GroupTree();
    void setGroupInfo(GroupList *);
private:
    void fillGroupTree(QTreeWidgetItem *,Group *);

};

#endif // GROUPTREE_H
