#ifndef CONFIGITEM_H
#define CONFIGITEM_H
#include "baseitem.h"
#include <QString>
///配置文件子项
/** @class ConfigItem
 *
 */

class ConfigItem : public BaseItem
{
public:
    explicit ConfigItem();
    ConfigItem(int,int,int,int,QString displayid);
};

#endif // CONFIGITEM_H
