#ifndef BASETREEWIDGET_H
#define BASETREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "organization.h"
#include "const.h"

class BaseTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit BaseTreeWidget(QWidget *parent = 0);
    virtual void showTree();

public:
    void init();
    void uninit();
    void initTree();

    void refreshTree();
    void setUse();
protected:
    virtual void buildUpTree();
    virtual void clearTreeInfo();

    bool dropMimeData(QTreeWidgetItem *parent, int index, const QMimeData *data, Qt::DropAction action);
    void setNodeData(QTreeWidgetItem *,int itemType,int valuepoint);
    void fillTreeByChannel(QTreeWidgetItem *, Channel *);
signals:
    void pressChannelSig(QTreeWidgetItem *item, int column);
    void pressPollingSig(QTreeWidgetItem *item, int column);
    void pressIgnoreSig();
public slots:
    void itemPressedSlot(QTreeWidgetItem *item, int column);
};

#endif // BaseTreeWidget_H
