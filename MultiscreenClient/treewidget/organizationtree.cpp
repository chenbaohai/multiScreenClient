#include "organizationtree.h"
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include "requestManager.h"

OrganizationTree::OrganizationTree(QWidget *parent) :
    BaseTreeWidget(parent)
{

}

OrganizationTree::~OrganizationTree()
{
    clearTreeInfo();
}

void OrganizationTree::buildUpTree()
{
//    RequestManager::instance()->getOrgInfo(&m_orgTreeList);

//    OrgList::iterator iter = m_orgTreeList.begin();
//    for (; iter != m_orgTreeList.end(); iter++)
//    {
//        Organization *temp = *iter;
////        qDebug() << temp->orgName();
//        fillTreeByOrganization(NULL, *iter);
//    }

    QFile file("Organizations.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QDomDocument doc;
    doc.setContent(&file);
    QDomElement root = doc.documentElement();
    qDebug() << "OrganizationTree::getOrganizationInfo()" << root.childNodes().count();
    for (int j = 0,i = 0; i < root.childNodes().count(); i++)
    {
        if (root.childNodes().at(i).nodeName() == "Organization")
        {
            m_orgTreeList.append(new Organization());
            m_orgTreeList.at(j)->fromXml(root.childNodes().at(i).toElement());
            fillTreeByOrganization(NULL, m_orgTreeList.at(j));
            j++;
        }
    }
}

void OrganizationTree::clearTreeInfo()
{
    qDeleteAll(m_orgTreeList);
    m_orgTreeList.clear();
}

void OrganizationTree::fillTreeByOrganization(QTreeWidgetItem *pitem, Organization *org)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, org->orgName());
    setNodeData(item, NODE_ORGANIZTION, (int)org);
    if (pitem)
    {
        pitem->addChild(item);
    }
    else
    {
        this->addTopLevelItem(item);
    }
    // add child Organization
    for(int i = 0; i < org->getOrgList().count(); i++)
    {
        Organization *child=static_cast<Organization *>(org->getOrgList().at(i));
        fillTreeByOrganization(item,child);
    }
    // add DVR
    for (int i = 0; i < org->getDvrList().count(); i++)
    {
        Dvr *dvr = static_cast<Dvr*>(org->getDvrList().at(i));
        fillTreeByDvr(item,dvr);
    }
}

void OrganizationTree::fillTreeByDvr(QTreeWidgetItem *pitem, Dvr *dvr)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0,dvr->dvrName());
    setNodeData(item,NODE_DVR,(int)dvr);
    for (int i = 0; i < dvr->channelList().count(); i++)
    {
        Channel *channel = static_cast<Channel*>(dvr->channelList().at(i));
        fillTreeByChannel(item, channel);
    }
    pitem->addChild(item);
}

