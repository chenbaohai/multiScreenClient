#include "schemexml.h"

#include "schemeitem.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>

SchemeXml::SchemeXml():
    m_schemeXml("")
{
}

void SchemeXml::append(SchemeItem *item)
{
    m_items.append(item);
}

void SchemeXml::append(int time, QString groupName, QString groupIds, int layout, QString discribe, bool extendFlag, int createFlag, QString schemeName,QString originalName)
{
    SchemeItem *item = new SchemeItem(time, groupName, groupIds, layout, discribe, extendFlag, createFlag, schemeName,originalName);
    m_items.append(item);
}

QList<SchemeItem*> SchemeXml::getItems()
{
    return m_items;
}

void SchemeXml::setSchemeXml(SchemeItem* item)
{
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root=doc.createElement("CirculateInfos");
    doc.appendChild(root);

    QDomElement elementItem=doc.createElement("CirculateInfo");
    elementItem.setAttribute("Time",item->getTime());
    elementItem.setAttribute("Group",item->getGroupName());
    elementItem.setAttribute("GroupIds",item->getGroupIds());
    elementItem.setAttribute("LayoutName",item->getLayout());
    elementItem.setAttribute("Decribe",item->getDiscribe());
    elementItem.setAttribute("IsExtend",item->getExtendFlag());
    elementItem.setAttribute("IsCreated",item->getCreateFlag());
    elementItem.setAttribute("OriginalName",item->getOriginalName());
    QDomText nodeText = doc.createTextNode(item->getSchemeName());
    elementItem.appendChild(nodeText);
    root.appendChild(elementItem);

    QString xml(doc.toByteArray());
    m_schemeXml = xml;
//    qDebug() << "m_schemeXml(doc.toByteArray())" << m_schemeXml;
    return;
}

bool SchemeXml::save()
{
    QFile file("scheme.xml");
    if(file.exists())
        file.remove();
    if (!file.open(QIODevice::WriteOnly|QIODevice::ReadOnly))
        return false;

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root=doc.createElement("CirculateInfos");
    doc.appendChild(root);
    foreach(SchemeItem *item,this->m_items)
    {
        QDomElement elementItem=doc.createElement("CirculateInfo");
        elementItem.setAttribute("Time",item->getTime());
        elementItem.setAttribute("Group",item->getGroupName());
        elementItem.setAttribute("GroupIds",item->getGroupIds());
        elementItem.setAttribute("LayoutName",item->getLayout());
        elementItem.setAttribute("Decribe",item->getDiscribe());
        elementItem.setAttribute("IsExtend",item->getExtendFlag());
        elementItem.setAttribute("IsCreated",item->getCreateFlag());
        elementItem.setAttribute("OriginalName",item->getOriginalName());
        QDomText nodeText = doc.createTextNode(item->getSchemeName());
        elementItem.appendChild(nodeText);
        root.appendChild(elementItem);
    }
    QTextStream out(&file);
    QString xml(doc.toByteArray());
    m_schemeXml = xml;
//    qDebug() << "QTextStream out(&file)" << m_schemeXml;

    doc.save(out,4);
    file.close();
    return true;
}

bool SchemeXml::load(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    QString xml(doc.toByteArray());
    m_schemeXml = xml;
    QDomNodeList nodelist =doc.documentElement().elementsByTagName("CirculateInfo");
    QDomNode node;
    for(int i=0;i<nodelist.count();i++)
    {
        node=nodelist.at(i);
        QDomElement element=node.toElement();
        int time = element.attribute("Time").toInt();
        QString groupName = element.attribute("Group");
        QString groupIds = element.attribute("GroupIds");
        int layout = element.attribute("LayoutName").toInt();
        QString discribe = element.attribute("Decribe");
        bool extendFlag = element.attribute("IsExtend").toInt();
        int createFlag = element.attribute("IsCreated").toInt();//OriginalName
        QString originalName = element.attribute("OriginalName");
        QString schemeName = element.text();

        this->append(time, groupName, groupIds, layout, discribe, extendFlag, createFlag, schemeName,originalName);
    }
    return true;
}

bool SchemeXml::deleteItem(SchemeItem *item)
{
    m_items.removeOne(item);
}

QString SchemeXml::getSchemeXml()
{
    return m_schemeXml;
}
