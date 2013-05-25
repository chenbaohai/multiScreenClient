#ifndef CONFIGXML_H
#define CONFIGXML_H

#include "configitem.h"
#include <QList>

class ConfigXML
{
public:
    ConfigXML();
    void append(ConfigItem );
    void append(int row,int col,int rowspan,int colspan,QString displayid);
    QList<ConfigItem> items();     
    bool save();
    bool load(QString filename="config.xml");
private:
    QList<ConfigItem> m_items;
};

#endif // CONFIGXML_H
