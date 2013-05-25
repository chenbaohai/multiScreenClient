#include "cardconfigwidget.h"
#include "ui_cardconfigwidget.h"
//#include "identificfactory.h"
#include "interactdata.h"
#include "subscreen.h"
#include "const.h"

#include "configitem.h"
#include "configxml.h"
#include "interactdata.h"

#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QFile>

CardConfigWidget::CardConfigWidget(QWidget *parent) :
    QWidget(parent),
    m_screenCount(0),
    ui(new Ui::CardConfigWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
//    ui->lbl_refresh->setVisible(false);
//    ui->cmb_refreshrate->setVisible(false);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->wx_layout->setCancelFlag();
    connect(ui->wx_layout, SIGNAL(cancelDisplayidSig(int)),this,SLOT(cancelDisplayid(int)));
    connect(ui->wx_layout, SIGNAL(selectedScreenSignal(BaseWidget*)), this, SLOT(paintScreen(BaseWidget*)));
    loadConfigXml();
}

CardConfigWidget::~CardConfigWidget()
{
    delete ui;
}

void CardConfigWidget::setScreenCount(int count)
{
    m_screenCount = count;
    ui->screenBar->setScreenCount(count);
    ui->screenBar->creatScreenId();
}

void CardConfigWidget::cancelDisplayid(int id)
{
   ui->screenBar->cancelDisplayId(id);
}

void CardConfigWidget::on_btnSetLayout_clicked()
{
    SubScreen * temp = new SubScreen;
    int row=ui->spinBoxRow->value();
    int col=ui->spinBoxCol->value();
    ui->wx_layout->changeLayout(row,col,temp);

    ui->screenBar->cleanScreen();
    setScreenCount(m_screenCount);

    delete temp;
    temp =NULL;
}

void CardConfigWidget::on_btnRecognise_clicked()
{
    m_socket->sendMsg(IDENTIFY_REQUEST,"");
}

void CardConfigWidget::on_btnSave_clicked()
{
    QFile file("merge.xml");
    if (file.exists())
        file.remove();
    saveConfigXml();
    emit saveConfigSig();
}

void CardConfigWidget::saveConfigXml()
{
    ConfigXML cardConfig;
    QString tempData = NULL;
//    int col = ui->spinBoxCol->value();
//    int row = ui->spinBoxRow->value();

    foreach(BaseWidget *w, *ui->wx_layout->ScreenList())
    {
        SubScreen *sub = (SubScreen*)w;
        QString displayid = sub->displayId();
        ConfigItem item;

        if (sub->useflag() == false)
            continue;
        if (displayid != "0")
        {
            item.setDisplayID(displayid);
            item.setRow(sub->row());
            item.setCol(sub->column());
            item.setRowSpan(sub->SpanRow());
            item.setColSpan(sub->SpanColumn());
            tempData += displayid + "," + QString::number(sub->row(), 10) + "," + QString::number(sub->column(), 10) + ":";
            cardConfig.append(item);
        }
    }
    cardConfig.save();
    emit sendConfigSig(tempData);
    QMessageBox::information(this, "系统提示", "电视墙配置保存成功");
}

void CardConfigWidget::loadConfigXml()
{
    ConfigXML cardConfig;
    cardConfig.load();
    QList<BaseWidget*> *list = ui->wx_layout->ScreenList();
    qDeleteAll(*list);
    list->clear();
    foreach(ConfigItem item, cardConfig.items())
    {
        SubScreen* screen = new SubScreen;
        screen->setRow(item.row());
        screen->setColumn(item.col());
        screen->setSpanRow(item.rowspan());
        screen->setSpanColumn(item.colspan());
        screen->setDisplayid(item.displayID());
        list->append(screen);
    }
    ui->wx_layout->changeScreen();
}

void CardConfigWidget::paintScreen(BaseWidget *widget)
{
    foreach(BaseWidget *w, *ui->wx_layout->ScreenList())
    {
        SubScreen *sub = (SubScreen*)w;
        sub->setPaintFlag(false);
    }
    qDebug() << "CardConfigWidget::paintScreen";
    SubScreen* curScreen = (SubScreen*)widget;
    curScreen->setPaintFlag(true);
}

int CardConfigWidget::screenCount()
{
    return m_screenCount;
}

void CardConfigWidget::setMsgSocket(MSocket *socket)
{
    m_socket=socket;
}

