#ifndef SCREENCONFIG_H
#define SCREENCONFIG_H

#include "screen.h"
#include "basedata.h"

class ScreenConfig : public BaseData
{
    Q_OBJECT
public:
     ScreenConfig(QObject *parent = 0);
     ~ScreenConfig();
signals:
    
public slots:
    
};

#endif // SCREENCONFIG_H
