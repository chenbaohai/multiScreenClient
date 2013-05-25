#include "grouptree.h"

GroupTree::GroupTree(QWidget *parent ):
    BaseTreeWidget(parent)
{
    this->setColumnCount(2);
    this->setDragEnabled(false);
}
GroupTree::~GroupTree()
{
}

void GroupTree::setGroupInfo(GroupList *lists)
{
    QTreeWidgetItem *top=this->topLevelItem(0);
    foreach(Group *group,*lists)
    {
        fillGroupTree(top,group);
    }
}

void GroupTree::fillGroupTree(QTreeWidgetItem *parent, Group *group)
{
    QTreeWidgetItem *item=new QTreeWidgetItem();
    item->setText(0,group->getGroupName());
    item->setCheckState(0,Qt::Unchecked);

//    QVariant var;
//    var.setValue((int)group);
//    item->setData(0,Qt::UserRole,var);

    this->setNodeData(item,NODE_MONITORGROUP,int(group));


    if(parent)
        parent->addChild(item);
    else
       this->addTopLevelItem(item);

    foreach(Group *tmp,group->getGroupList())
    {
        fillGroupTree(item,tmp);
    }
}
