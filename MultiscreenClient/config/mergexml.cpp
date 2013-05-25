#include "mergexml.h"

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include "mergeitem.h"

MergeXml::MergeXml():
    m_path("merge.xml")
{
    QFile file(m_path);
    if(file.exists())
        return;
    file.open(QIODevice::WriteOnly|QIODevice::ReadOnly);
    file.close();
}

void MergeXml::append(MergeItem *item)
{
    this->m_merges.append(item);
}

void MergeXml::clear()
{
    qDeleteAll(m_merges);
    m_merges.clear();
}

QList<MergeItem *> & MergeXml::merges()
{
    return this->m_merges;
}

bool MergeXml::save()
{
    QFile file(m_path);
    if(file.exists())
        file.remove();
    if (!file.open(QIODevice::WriteOnly|QIODevice::ReadOnly))  return false;

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root=doc.createElement("Items");
    doc.appendChild(root);
    foreach(MergeItem* item,this->m_merges)
    {
        QDomElement elementItem=doc.createElement("Item");
        elementItem.setAttribute("displayid",item->displayID());
        elementItem.setAttribute("row",item->row());
        elementItem.setAttribute("col",item->col());
        elementItem.setAttribute("rowspan",item->rowspan());
        elementItem.setAttribute("colspan",item->colspan());
        elementItem.setAttribute("mergeflag",item->mergeFlag());
        elementItem.setAttribute("useflag",item->useFlag());

        createChildNode(elementItem,item,doc);
        root.appendChild(elementItem);
    }
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}

bool MergeXml::load()
{
    QFile file(m_path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return false;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    this->clear();
    QDomNodeList nodeList = doc.documentElement().elementsByTagName("Item");
    QDomNode node;
    for (int i = 0; i < nodeList.count(); i++)
    {
        node = nodeList.at(i);
        QDomElement element = node.toElement();
        int row = element.attribute("row").toInt();
        int col = element.attribute("col").toInt();
        int rowspan = element.attribute("rowspan").toInt();
        int colspan = element.attribute("colspan").toInt();

        QString displayid = element.attribute("displayid");
        QString mergeflag = element.attribute("mergeflag");
        QString useflag = element.attribute("useflag");

        MergeItem *item = new MergeItem;
        item->setDisplayID(displayid);
        item->setRow(row);
        item->setCol(col);
        item->setRowSpan(rowspan);
        item->setColSpan(colspan);
        item->setMergeFlag((mergeflag=="1"?true:false));
        item->setUesFlag((useflag=="1"?true:false));
        this->append(item);
        createContainItems(element, item);
    }
    return true;
}

bool MergeXml::del()
{
    QFile file(m_path);
    return file.remove();
}

void MergeXml::createChildNode(QDomElement &element, MergeItem *item, QDomDocument &doc)
{
    if (item->mergeFlag())
    {
        foreach(MergeItem* tempitem, *item->containItems())
        {
            QDomElement elementItem = doc.createElement("childItem");
            elementItem.setAttribute("displayid",tempitem->displayID());
            elementItem.setAttribute("row",tempitem->row());
            elementItem.setAttribute("col",tempitem->col());
            elementItem.setAttribute("rowspan",tempitem->rowspan());
            elementItem.setAttribute("colspan",tempitem->colspan());
            elementItem.setAttribute("mergeflag",tempitem->mergeFlag());
            elementItem.setAttribute("useflag",tempitem->useFlag());

            element.appendChild(elementItem);
            createChildNode(elementItem,tempitem,doc);
        }
    }
}

void MergeXml::createContainItems(QDomElement &element, MergeItem *item)
{
    QDomNodeList nodeList = element.childNodes();
    QDomNode node;
    if (nodeList.count() <= 0)
        return;
    for (int i = 0; i < nodeList.count(); i++)
    {
        node = nodeList.at(i);
        QDomElement element = node.toElement();
        int row = element.attribute("row").toInt();
        int col = element.attribute("col").toInt();
        int rowspan = element.attribute("rowspan").toInt();
        int colspan = element.attribute("colspan").toInt();

        QString displayid = element.attribute("displayid");
        QString mergeflag = element.attribute("mergeflag");
        QString useflag = element.attribute("useflag");

        MergeItem *subItem = new MergeItem;
        subItem->setDisplayID(displayid);
        subItem->setRow(row);
        subItem->setCol(col);
        subItem->setRowSpan(rowspan);
        subItem->setColSpan(colspan);
        subItem->setMergeFlag((mergeflag=="1"?true:false));
        subItem->setUesFlag((useflag=="1"?true:false));
        item->containItems()->append(subItem);
        createContainItems(element,subItem);
    }
}
