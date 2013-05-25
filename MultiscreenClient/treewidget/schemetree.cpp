#include "schemetree.h"
#include "skinmanager.h"
#include "schemexml.h"
#include "const.h"
#include <QMouseEvent>
#include <QDomDocument>
#include <QFile>
#include <QDebug>

SchemeTree::SchemeTree(QWidget *parent) :
    BaseTreeWidget(parent),
    m_pItem(NULL)
{
//    this->setDragEnabled(false);
    m_schemeXml = new SchemeXml;
    m_schemeXml->load("scheme.xml");

}

SchemeTree::~SchemeTree()
{
    clearTreeInfo();
}

void SchemeTree::append(SchemeItem *item)
{
    m_schemeXml->append(item);
}

void SchemeTree::buildUpTree()
{
//    qDebug() << "SchemeTree::buildUpTree()" << m_schemeXml->getSchemeXml();
//    emit sendSchemeXmlSig(SCHEDULEXML_REQUEST, m_schemeXml->getSchemeXml());
    m_schemeTreeList = m_schemeXml->getItems();
    createTopTree();
    for (int i = 0; i < m_schemeTreeList.count(); i++)
    {
        fillTreeByScheme(m_pItem, m_schemeTreeList.at(i));
    }
}

void SchemeTree::clearTreeInfo()
{
    qDeleteAll(m_schemeTreeList);
    m_schemeTreeList.clear();
}

void SchemeTree::modifyItemToTree(SchemeItem *item, int index)
{
    m_schemeTreeList.replace(index, item);
    this->currentItem()->setText(0, item->getSchemeName());
    m_schemeXml->setSchemeXml(item);
    emit sendSchemeXmlSig(SCHEDULEXML_REQUEST, m_schemeXml->getSchemeXml());
    qDebug() << "SchemeTree::modifyItemToTree(SchemeItem *item, int index)" << m_schemeXml->getSchemeXml();
//    m_pItem->takeChild(index)->setText(0, item->getSchemeName());
}

void SchemeTree::addItemToTree(SchemeItem* item)
{
    fillTreeByScheme(m_pItem, item);
    m_schemeXml->setSchemeXml(item);
    m_schemeTreeList.append(item);
    emit sendSchemeXmlSig(SCHEDULEXML_REQUEST, m_schemeXml->getSchemeXml());
    qDebug() << "SchemeTree::addItemToTree(SchemeItem* item)" << m_schemeXml->getSchemeXml();
    append(item);
}

bool SchemeTree::deleteScheme(SchemeItem* item, int index)
{
    item->setCreateFlag(2);
    m_schemeXml->setSchemeXml(item);
    emit sendSchemeXmlSig(SCHEDULEXML_REQUEST, m_schemeXml->getSchemeXml());
    qDebug() << "SchemeTree::deleteScheme(SchemeItem* item, int index)" << m_schemeXml->getSchemeXml();
    m_schemeXml->deleteItem(item);
    m_pItem->removeChild(m_pItem->takeChild(index));
    m_schemeTreeList.removeOne(item);
    saveSchemeXml();
}

SchemeItem* SchemeTree::getScheme(int index)
{
    return m_schemeTreeList.at(index);
}

bool SchemeTree::testSchemeName(QString name, int index)
{
    for(int i = 0; i < m_schemeTreeList.count(); i++)
    {
        if (i == index)
            continue;
        if(m_schemeTreeList.at(i)->getSchemeName() == name)
            return true;
    }
    return false;
}

bool SchemeTree::saveSchemeXml()
{
    return m_schemeXml->save();
}

void SchemeTree::fillTreeByScheme(QTreeWidgetItem *pItem, SchemeItem *pScheme)
{
    if (pScheme == NULL)
        return;
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, pScheme->getSchemeName());
    setNodeData(item, NODE_SCHEDULE, (int)pScheme);
    pItem->addChild(item);
}

void SchemeTree::createTopTree()
{
    QTreeWidgetItem *topItem = new QTreeWidgetItem;
    topItem->setText(0, "方案列表");
    topItem->setIcon(0,QIcon(SkinManager::instance()->getPicture("organization.png")));
    this->addTopLevelItem(topItem);
    m_pItem = topItem;
}

SchemeList SchemeTree::getSchemeList()
{
    return m_schemeTreeList;
}

void SchemeTree::customContextMenuRequested(const QPoint &pos)
{
    this->itemAt(pos);
}

