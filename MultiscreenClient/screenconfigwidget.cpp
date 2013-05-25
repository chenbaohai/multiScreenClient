#include "screenconfigwidget.h"
#include "ui_screenconfigwidget.h"

#include "mergexml.h"
#include "configxml.h"
#include "mergeitem.h"
#include <QDebug>
#include <QDir>

ScreenConfigWidget::ScreenConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenConfigWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
    initScreenConfig();

    connect(ui->screenLayout, SIGNAL(selectedScreenSignal(BaseWidget*)), this, SLOT(paintScreen(BaseWidget*)));
    connect(ui->screenLayout, SIGNAL(saveMergeXmlSig()), this, SLOT(saveMergeXmlSlot()));
}

ScreenConfigWidget::~ScreenConfigWidget()
{
    delete ui;
}

void ScreenConfigWidget::initScreenConfig()
{
    QDir file;
    bool exist = file.exists("merge.xml");
    if (exist)
    {
        MergeXml mergeXml;
        mergeXml.load();
        QList<BaseWidget*> *list = ui->screenLayout->ScreenList();
        qDeleteAll(*list);
        list->clear();
        foreach (MergeItem *item, mergeXml.merges())
        {
            Screen* screen = new Screen;
            Screen* hideScreen = NULL;
            screen->setRow(item->row());
            screen->setColumn(item->col());
            screen->setSpanRow(item->rowspan());
            screen->setSpanColumn(item->colspan());
            screen->setDisplayid(item->displayID());
            screen->setIsMerge(item->mergeFlag());
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
                        screen->getMergeList()->append(screen);
                    }
                    else
                    {
                        hideScreen = new Screen;
                        hideScreen->setRow(subItem->row());
                        hideScreen->setColumn(subItem->col());
                        hideScreen->setSpanRow(subItem->rowspan());
                        hideScreen->setSpanColumn(subItem->colspan());
                        hideScreen->setDisplayid(subItem->displayID());
                        hideScreen->setIsMerge(subItem->mergeFlag());
                        hideScreen->setUseflag(subItem->useFlag());
                        screen->getMergeList()->append(hideScreen);
                        connect(screen,SIGNAL(changeSpanSignal(BaseWidget*)),ui->screenLayout,SLOT(changeSpanSlot(BaseWidget*)));
                        list->append(hideScreen);
                    }
                }
            }
            connect(screen,SIGNAL(changeSpanSignal(BaseWidget*)),ui->screenLayout,SLOT(changeSpanSlot(BaseWidget*)));
            list->append(screen);
        }
        ui->screenLayout->changeScreen();
    }
    else
    {
        ConfigXML cardConfig;
        cardConfig.load();
        QList<BaseWidget*> *list = ui->screenLayout->ScreenList();
        qDeleteAll(*list);
        list->clear();
        foreach (ConfigItem item, cardConfig.items())
        {
            Screen* screen = new Screen;
            screen->setRow(item.row());
            screen->setColumn(item.col());
            screen->setSpanRow(item.rowspan());
            screen->setSpanColumn(item.colspan());
            screen->setDisplayid(item.displayID());
            connect(screen,SIGNAL(changeSpanSignal(BaseWidget*)),ui->screenLayout,SLOT(changeSpanSlot(BaseWidget*)));
            list->append(screen);
        }
        ui->screenLayout->changeScreen();
    }
}

void ScreenConfigWidget::configChangeSlot()
{
    initScreenConfig();
}

void ScreenConfigWidget::paintScreen(BaseWidget *widget)
{
    foreach(BaseWidget *w, *ui->screenLayout->ScreenList())
    {
        Screen *sub = (Screen*)w;
        sub->setPaintFlag(false);
    }
    qDebug() << "ScreenConfigWidget::paintScreen";
    Screen* curScreen = (Screen*)widget;
    curScreen->setPaintFlag(true);
}

void ScreenConfigWidget::saveMergeXml()
{
    MergeXml mergeConfig;
    QString tempData = NULL;
    foreach(BaseWidget *w, *ui->screenLayout->ScreenList())
    {
        Screen *screen = (Screen*)w;
        MergeItem *item = new MergeItem;

        if (!screen->useflag())
            continue;
        item->setDisplayID(screen->displayId());
        item->setRow(screen->row());
        item->setCol(screen->column());
        item->setRowSpan(screen->SpanRow());
        item->setColSpan(screen->SpanColumn());
        item->setMergeFlag(screen->isMerged());
        item->setUesFlag(screen->useflag());

        tempData += screen->displayId();
        if (screen->isMerged())
        {
            tempData += ";" + screen->displayId() + ",";
            foreach(BaseWidget *sub, *screen->getMergeList())
            {
                Screen *subScreen = (Screen*)sub;
                MergeItem *subItem = new MergeItem;
                if (subScreen->isMerged())
                {
                    subItem->setRow(subScreen->originalRow());
                    subItem->setCol(subScreen->originalColumn());
                    subItem->setRowSpan(subScreen->originalSpanRow());
                    subItem->setColSpan(subScreen->originalSpanColumn());
                }
                else
                {

                    subItem->setRow(subScreen->row());
                    subItem->setCol(subScreen->column());
                    subItem->setRowSpan(subScreen->SpanRow());
                    subItem->setColSpan(subScreen->SpanColumn());
                }
                subItem->setDisplayID(subScreen->displayId());
                subItem->setMergeFlag(subScreen->isMerged());
                subItem->setUesFlag(subScreen->useflag());
                item->containItems()->append(subItem);
                if (screen->displayId() == subScreen->displayId())
                    continue;
                tempData += subScreen->displayId() + ",";
            }
            //取出末尾无用字符
            tempData.remove(tempData.count() - 1,tempData.count() - 2);
        }

        tempData += ":";
        mergeConfig.append(item);
    }
    //取出末尾无用字符
    tempData.remove(tempData.count() - 1,tempData.count() - 2);
    mergeConfig.save();
    emit sendMergeXmlSig(tempData);
    emit changeLayoutSig(ui->screenLayout->ScreenList());
    qDebug() << "ScreenConfigWidget::saveMergeXml" << tempData;
}

void ScreenConfigWidget::saveMergeXmlSlot()
{
    qDebug() << "ScreenConfigWidget::saveMergeXmlSlot";
    saveMergeXml();
}
