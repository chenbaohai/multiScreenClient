#include "pollingschemewidget.h"
#include "ui_pollingschemewidget.h"

#include "requestManager.h"
#include "selectgroupdlg.h"
#include "schemeitem.h"
#include "schemexml.h"
#include "mergeitem.h"
#include "mergexml.h"
#include "configxml.h"
#include "playscreen.h"
#include <QStringList>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDataStream>

PollingSchemeWidget::PollingSchemeWidget(QWidget *parent) :
    QWidget(parent),
    m_index(-1),
    m_createFlag(-1),
    m_pCurItem(NULL),
    ui(new Ui::PollingSchemeWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);

    connect(ui->createSchemeBtn, SIGNAL(clicked()), this, SLOT(createSchemeSlot()));
    connect(ui->saveSchemeBtn, SIGNAL(clicked()), this, SLOT(saveSchemeSlot()));
    connect(ui->delSchemeBtn, SIGNAL(clicked()), this, SLOT(deleteSchemeSlot()));
    connect(ui->addListBtn, SIGNAL(clicked()), this, SLOT(addGroupListSlot()));
    connect(ui->pollingTreeWidget, SIGNAL(pressPollingSig(QTreeWidgetItem*,int)), this, SLOT(pressPollingSlot(QTreeWidgetItem*,int)));
    connect(ui->pollingTreeWidget, SIGNAL(sendSchemeXmlSig(int, QString)), this, SIGNAL(sendPollingSchemeSig(int, QString)));
    connect(ui->PlayWidget, SIGNAL(selectedScreenSignal(BaseWidget*)), this, SLOT(paintScreen(BaseWidget*)));
    connect(ui->pollingTreeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(clickSlot(QModelIndex)));

    initWidgetLayout();
    ui->pollingTreeWidget->showTree();
    ui->pollingTreeWidget->expandAll();

    RequestManager::instance()->getGroupInfo(&m_groupList);

    ui->nameEdit->clear();
}

PollingSchemeWidget::~PollingSchemeWidget()
{
    delete ui;
}

SchemeItem* PollingSchemeWidget::msgUiToVar(SchemeItem* item)
{
    QString groupNames(""), groupIds("");
    item->setTime(ui->cycleSpin->value());
    item->setLayout(ui->layoutCombo->currentIndex());
    item->setDiscribe("");
    item->setExtendFlag(false);
    item->setCreateFlag(m_createFlag);
    if(m_createFlag==1)
        item->setOriginalName(ui->nameEdit->text());
    else if(m_createFlag==0)
        item->setOriginalName(item->getSchemeName());
    item->setSchemeName(ui->nameEdit->text());


    for(int i = 0; i < m_curGroupList.count(); i++)
    {
        Group *group = m_curGroupList.at(i);

        if (i != m_curGroupList.count() - 1)
        {
            groupNames += group->getGroupName() + ",";
            groupIds += QString::number(group->getGroupId()) + ",";
        }
        else
        {
            groupNames += group->getGroupName();
            groupIds += QString::number(group->getGroupId());
        }
    }
    item->setGroupName(groupNames);
    item->setGroupIds(groupIds);
    return item;
}

void PollingSchemeWidget::createSchemeSlot()
{
    m_createFlag = 1;
    ui->nameEdit->setText("");
    ui->layoutCombo->setCurrentIndex(0);
    ui->cycleSpin->setValue(5);
    ui->groupListWidget->clear();
    m_curGroupList.clear();
}

void PollingSchemeWidget::saveSchemeSlot()
{
    if (ui->nameEdit->text().isEmpty())
    {
        QMessageBox::information(0, "提示", "方案名不能为空",QString::fromUtf8("确定"));
        return;
    }

    if (m_curGroupList.isEmpty())
    {
        QMessageBox::information(0, "提示", "组列表不能为空",tr("确定"));
        return;
    }
    if (m_createFlag == 1)
    {
        if (ui->pollingTreeWidget->testSchemeName(ui->nameEdit->text(), -1))
        {
            QMessageBox::information(0, "提示", "方案名已存在",tr("确定"));
            return;
        }
        SchemeItem *item = new SchemeItem;
        ui->pollingTreeWidget->addItemToTree(msgUiToVar(item));
    }
    else if (m_createFlag == 0)
    {
        if (ui->pollingTreeWidget->testSchemeName(ui->nameEdit->text(), m_index))
        {
            QMessageBox::information(0, "提示", "方案名已存在",tr("确定"));
            return;
        }
        ui->pollingTreeWidget->modifyItemToTree(msgUiToVar(m_pCurItem), m_index);
    }
    else
    {
        QMessageBox::information(0, "提示", "点击新建后才能新建方案",tr("确定"));
        return;
    }

    if (ui->pollingTreeWidget->saveSchemeXml())
    {
        QMessageBox::information(0, "提示", "保存成功",tr("确定"));
    }
}

void PollingSchemeWidget::deleteSchemeSlot()
{
    if (m_index < 0)
    {
        QMessageBox::information(0, "提示", "请选择方案结点！",tr("确定"));
        return;
    }
    ui->pollingTreeWidget->deleteScheme(ui->pollingTreeWidget->getScheme(m_index), m_index);
}

void PollingSchemeWidget::addGroupListSlot()
{
    SelectGroupDlg dlg;
    dlg.setGroupInfo(&m_groupList);
    if(dlg.exec()==QDialog::Accepted)
    {
        ui->groupListWidget->clear();
        m_curGroupList = dlg.groups();

        foreach(Group *group, m_curGroupList)
        {
//            ui->groupListEdit->append(group->getGroupName());
            ui->groupListWidget->addItem(group->getGroupName());
        }
    }
} 

void PollingSchemeWidget::on_pollingTreeWidget_doubleClicked(const QModelIndex &index)
{
    qDebug() << "PollingSchemeWidget::on_pollingTreeWidget_doubleClicked" << index.row();
    m_index = index.row();

    m_pCurItem = ui->pollingTreeWidget->getSchemeList().at(m_index);
    m_createFlag = 0;
    ui->nameEdit->setText(m_pCurItem->getSchemeName());
    ui->layoutCombo->setCurrentIndex(m_pCurItem->getLayout());

    ui->cycleSpin->setValue(m_pCurItem->getTime());

    ui->groupListWidget->clear();
    m_curGroupList.clear();
    m_wholeGroupList.clear();
    QStringList list = m_pCurItem->getGroupName().split(",");
    getWholeGroupList(m_groupList);
    foreach(QString str, list)
    {
        foreach(Group *pGroup, m_wholeGroupList)
        {
            if (pGroup->getGroupName() == str)
            {
                m_curGroupList.append(pGroup);
            }
        }
        ui->groupListWidget->addItem(str);
    }
}

void PollingSchemeWidget::getWholeGroupList(GroupList list)
{
    foreach(Group *pGroup, list)
    {
        m_wholeGroupList.append(pGroup);
        getWholeGroupList(pGroup->getGroupList());
    }
}

void PollingSchemeWidget::sendPollingSchemeSlot(int cmd, QString xml)
{
    qDebug() << "PollingSchemeWidget::sendPollingSchemeSlot(int cmd, QString xml)";
    emit sendPollingSchemeSig(cmd, xml);
}

void PollingSchemeWidget::showEvent(QShowEvent *)
{
//    if(ui->pollingTreeWidget->topLevelItemCount()==0)
//    {
//        ui->pollingTreeWidget->showTree();
    //    }
}

void PollingSchemeWidget::initWidgetLayout()
{
    QDir file;
    bool exist = file.exists("merge.xml");
    if (exist)
    {
        MergeXml mergeXml;
        mergeXml.load();
        QList<BaseWidget*> *list = ui->PlayWidget->ScreenList();
        qDeleteAll(*list);
        list->clear();
        foreach (MergeItem *item, mergeXml.merges())
        {
            PlayScreen* screen = new PlayScreen;
            PlayScreen* hideScreen = NULL;
            screen->setRow(item->row());
            screen->setColumn(item->col());
            screen->setSpanRow(item->rowspan());
            screen->setSpanColumn(item->colspan());
            screen->setDisplayid(item->displayID());
            screen->setClosePollingFlag(true);
//            screen->setIsMerge(item->mergeFlag());
//            screen->setUseflag(item->useFlag());
            if (item->mergeFlag())
            {
                foreach(MergeItem *subItem, *item->containItems())
                {
                    if (subItem->mergeFlag())
                    {
                        screen->setOriginalRow(subItem->row());
                        screen->setOriginalColumn(subItem->col());
                        screen->setOriginalSpanRow(subItem->rowspan());
                        screen->setOriginalSpanColumn(subItem->colspan());
//                        screen->getMergeList()->append(screen);
                    }
                    else
                    {
                        hideScreen = new PlayScreen;
                        hideScreen->setRow(subItem->row());
                        hideScreen->setColumn(subItem->col());
                        hideScreen->setSpanRow(subItem->rowspan());
                        hideScreen->setSpanColumn(subItem->colspan());
                        hideScreen->setDisplayid(subItem->displayID());
//                        hideScreen->setIsMerge(subItem->mergeFlag());
                        hideScreen->setUseflag(subItem->useFlag());
                        hideScreen->setClosePollingFlag(true);
//                        screen->getMergeList()->append(hideScreen);
//                        connect(hideScreen, SIGNAL(sendPreviewScreenSig(QString)), this, SLOT(sendPreviewControlSlot(QString)));
//                        connect(hideScreen, SIGNAL(closePreviewWindowSig(QString)), this, SLOT(closePreviewCtrlSlot(QString)));
                        connect(hideScreen, SIGNAL(sendCirculateSig(QString,bool)), this, SIGNAL(sendCirculateSig(QString,bool)));
                        list->append(hideScreen);
                    }
                }
            }
//            connect(screen, SIGNAL(sendPreviewScreenSig(QString)), this, SLOT(sendPreviewControlSlot(QString)));
//            connect(screen, SIGNAL(closePreviewWindowSig(QString)), this, SLOT(closePreviewCtrlSlot(QString)));
            connect(screen, SIGNAL(sendCirculateSig(QString,bool)), this, SIGNAL(sendCirculateSig(QString,bool)));
            list->append(screen);
        }
        ui->PlayWidget->changeScreen();
    }
    else
    {
        ConfigXML cardConfig;
        if(!cardConfig.load()) return;
        QList<BaseWidget*> *list = ui->PlayWidget->ScreenList();
        qDeleteAll(*list);
        list->clear();
        foreach (ConfigItem item, cardConfig.items())
        {
            PlayScreen* screen = new PlayScreen;
            screen->setRow(item.row());
            screen->setColumn(item.col());
            screen->setSpanRow(item.rowspan());
            screen->setSpanColumn(item.colspan());
            screen->setDisplayid(item.displayID());
            screen->setClosePollingFlag(true);
            list->append(screen);
//            connect(screen, SIGNAL(sendPreviewScreenSig(QString)), this, SLOT(sendPreviewControlSlot(QString)));
//            connect(screen, SIGNAL(closePreviewWindowSig(QString)), this, SLOT(closePreviewCtrlSlot(QString)));
            connect(screen, SIGNAL(sendCirculateSig(QString,bool)), this, SIGNAL(sendCirculateSig(QString,bool)));
        }
        ui->PlayWidget->changeScreen();
    }
}

void PollingSchemeWidget::pressPollingSlot(QTreeWidgetItem *item, int column)
{

    qDebug() << "PollingSchemeWidget::itemclick"<<item->text(0);


    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);


    dataStream <<item->text(0);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("PollingSchemeWidget/circulate", itemData);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}

void PollingSchemeWidget::on_saveSchemeBtn_clicked()
{

}

void PollingSchemeWidget::beginPollingScheme()
{
    qDebug() << "PollingSchemeWidget::beginPollingScheme";

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);


    dataStream <<m_pCurItem->getSchemeName();

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("PollingSchemeWidget/circulate", itemData);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}

void PollingSchemeWidget::paintScreen(BaseWidget *widget)
{
    foreach(BaseWidget *w, *ui->PlayWidget->ScreenList())
    {
        PlayScreen *sub = (PlayScreen*)w;
        sub->setPaintFlag(false);
    }
    qDebug() << "PollingSchemeWidget::paintScreen";
    PlayScreen* curScreen = (PlayScreen*)widget;
    curScreen->setPaintFlag(true);
}

void PollingSchemeWidget::clickSlot(const QModelIndex &index)
{
    qDebug() << "PollingSchemeWidget::clickSlot" << index.row();
    m_index = index.row();
    if(ui->pollingTreeWidget->getSchemeList().isEmpty()) return;
    m_pCurItem = ui->pollingTreeWidget->getSchemeList().at(m_index);
}

void PollingSchemeWidget::configChangeSlot()
{
    initWidgetLayout();
}

void PollingSchemeWidget::changeScreenLayout(QList<BaseWidget *> *pList)
{
    QList<BaseWidget*> *montageList = pList;
    foreach(BaseWidget *listTemp, *montageList)
    {
        foreach(BaseWidget *screenListTemp, *ui->PlayWidget->ScreenList())
        {
            PlayScreen* list = (PlayScreen*)listTemp;
            PlayScreen* screenList = (PlayScreen*)screenListTemp;
            if (list->displayId() == screenList->displayId())
            {
                if (!compareEqual(screenList, list))
                {
                    assignment(screenList, list);
                    if (!screenList->useflag())
                    {
                        screenList->closeCirculate();
                    }
                }
                break;
            }
        }
    }
    ui->PlayWidget->changeScreen();
}

bool PollingSchemeWidget::compareEqual(PlayScreen* des, PlayScreen* org)
{
    if (org->SpanColumn() == des->SpanColumn() && org->SpanRow() == des->SpanRow() && org->useflag() == des->useflag())
    {
        return true;
    }
    return false;
}

void PollingSchemeWidget::assignment(PlayScreen *des, PlayScreen *org)
{
    des->setSpanColumn(org->SpanColumn());
    des->setSpanRow(org->SpanRow());
    des->setUseflag(org->useflag());
    des->setColumn(org->column());
    des->setRow(org->row());
}
