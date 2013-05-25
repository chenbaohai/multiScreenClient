#include "basetreewidget.h"
#include "const.h"
#include <qglobal.h>
#include <QDebug>

#include "skinmanager.h"
#include <QScrollBar>
#include <QHeaderView>

BaseTreeWidget::BaseTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    init();
}

void BaseTreeWidget::init()
{
    initTree();
}

void BaseTreeWidget::uninit()
{
    clearTreeInfo();
}

void BaseTreeWidget::initTree()
{
    this->setFrameShape(QFrame::NoFrame);
    this->setHeaderHidden(true);

    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);

//    this->setDragDropMode(QAbstractItemView::InternalMove);
    connect(this,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(itemPressedSlot(QTreeWidgetItem*,int)));
//    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(on_itemClicked(QTreeWidgetItem*,int)));
//    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(on_itemDoubleClicked(QTreeWidgetItem*,int)));
    this->setColumnCount(4);
    this->setColumnHidden(1,true);     //store channel
    this->setColumnHidden(2,true);     //store nodetype
    this->setColumnHidden(3,true);     //store isplaying

    this->header()->setStretchLastSection(false);
    this->header()->setDefaultSectionSize(400);


}

void BaseTreeWidget::showTree()
{
    clearTreeInfo();
    buildUpTree();
}

void BaseTreeWidget::buildUpTree()
{
}

void BaseTreeWidget::clearTreeInfo()
{

}

void BaseTreeWidget::refreshTree()
{

}

bool BaseTreeWidget::dropMimeData(QTreeWidgetItem *parent, int index, const QMimeData *data, Qt::DropAction action)
{
    return true;
}

void BaseTreeWidget::setNodeData(QTreeWidgetItem *item, int itemType, int valueChannel)
{
    QVariant var;
    var.setValue(valueChannel);
    switch(itemType)
    {
    case NODE_ORGANIZTION:
        item->setIcon(0, QIcon(SkinManager::instance()->getPicture("organization.png")));
        break;
    case NODE_MONITORGROUP:
        item->setIcon(0,QIcon(SkinManager::instance()->getPicture("group.png")));
        break;
    case NODE_DVR:
        item->setIcon(0,QIcon(SkinManager::instance()->getPicture("dvr.png")));
        break;
    case NODE_CHANNEL:
        item->setIcon(0,QIcon(SkinManager::instance()->getPicture("channel.png")));
        break;
    case NODE_CHANNELPLAYING:
        item->setIcon(0,QIcon(SkinManager::instance()->getPicture("channelPlaying.png")));
        break;
    case NODE_SCHEDULE:
        item->setIcon(0,QIcon(SkinManager::instance()->getPicture("schedule.png")));
        break;
    }
    item->setText(2,QString::number(itemType));
    item->setData(1,0,var);
}

void BaseTreeWidget::fillTreeByChannel(QTreeWidgetItem *pitem, Channel *channel)
{
    QTreeWidgetItem *item=new QTreeWidgetItem;
    item->setText(0,channel->channelName());
    setNodeData(item,NODE_CHANNEL,(int)channel);
    pitem->addChild(item);
}

void BaseTreeWidget::itemPressedSlot(QTreeWidgetItem *item, int column)
{
    QString strNodeType = item->text(2).trimmed();
    NODETYPE nodeType = (NODETYPE)strNodeType.toInt();
    switch(nodeType)
    {
    case NODE_ORGANIZTION:
        emit pressIgnoreSig();
        break;
    case NODE_DVR:
        emit pressIgnoreSig();
        break;
    case NODE_CHANNEL:
        emit pressChannelSig(item,column);
        break;
    case NODE_MONITORGROUP:
        emit pressPollingSig(item,column);
        break;
     case NODE_SCHEDULE:
        emit pressPollingSig(item,column);
        break;
    }
}

void BaseTreeWidget::setUse()
{
    this->setDragEnabled(false);
    this->setAcceptDrops(false);
}
