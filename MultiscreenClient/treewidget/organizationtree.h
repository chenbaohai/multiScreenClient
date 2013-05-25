#ifndef GROUPTREE_H
#define GROUPTREE_H

#include "basetreewidget.h"
#include "organization.h"



class OrganizationTree : public BaseTreeWidget
{
    Q_OBJECT
public:
    explicit OrganizationTree(QWidget *parent = 0);
    ~OrganizationTree();

    virtual void buildUpTree();
    virtual void clearTreeInfo();
private:
    void fillTreeByOrganization(QTreeWidgetItem *, Organization *);
    void fillTreeByDvr(QTreeWidgetItem *, Dvr *);

private:
    OrgList m_orgTreeList;


};

#endif // GROUPTREE_H
