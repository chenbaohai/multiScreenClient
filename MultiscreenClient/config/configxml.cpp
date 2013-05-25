#include "configxml.h"

#include <QDomDocument>
#include <QFile>
#include <QTextStream>

#include "configitem.h"

ConfigXML::ConfigXML()
{
}

QList<ConfigItem> ConfigXML::items()
{
    return this->m_items;
}

void ConfigXML::append(ConfigItem item)
{
    this->m_items.append(item);
}

void ConfigXML::append(int row,int col,int rowspan,int colspan,QString displayid)
{
    ConfigItem item(row,col,rowspan,colspan,displayid);
    this->m_items.append(item);
}

bool ConfigXML::save()
{
    QFile file("config.xml");
    if(file.exists())
        file.remove();
    if (!file.open(QIODevice::WriteOnly|QIODevice::ReadOnly))
        return false;

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root=doc.createElement("Items");
    doc.appendChild(root);
    foreach(ConfigItem item,this->m_items)
    {
        QDomElement elementItem=doc.createElement("Item");
        elementItem.setAttribute("displayid",item.displayID());
        elementItem.setAttribute("row",item.row());
        elementItem.setAttribute("col",item.col());
        elementItem.setAttribute("rowspan",item.rowspan());
        elementItem.setAttribute("colspan",item.colspan());

        root.appendChild(elementItem);
    }
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}

bool ConfigXML::load(QString filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    QDomNodeList nodelist =doc.documentElement().elementsByTagName("Item");
    QDomNode node;
    for(int i=0;i<nodelist.count();i++)
    {
        node=nodelist.at(i);
        QDomElement element=node.toElement();
        int row=element.attribute("row").toInt();
        int col=element.attribute("col").toInt();
        int rowspan=element.attribute("rowspan").toInt();
        int colspan=element.attribute("colspan").toInt();
        QString displayid=element.attribute("displayid");

        this->append(row,col,rowspan,colspan,displayid);
    }
    return true;
}

