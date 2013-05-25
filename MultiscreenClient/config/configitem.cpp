#include "configitem.h"

ConfigItem::ConfigItem()
{
}

ConfigItem::ConfigItem(int row,int col,int rowspan,int colspan,QString displayid)
    :BaseItem(row,col,rowspan,colspan,displayid)
{
}
