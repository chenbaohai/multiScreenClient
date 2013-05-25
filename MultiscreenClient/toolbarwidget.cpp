#include "toolbarwidget.h"
#include "ui_toolbarwidget.h"

#include <QDebug>

ToolBarWidget::ToolBarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBarWidget)
{
    ui->setupUi(this);
//    connect(ui->setWinBtn1, SIGNAL(clicked()), this, SLOT(setPreviewWindowSlot(int)));
//    connect(ui->setWinBtn1, SIGNAL(clicked()), this, SLOT(setPreviewWindowSlot(int)));
}

ToolBarWidget::~ToolBarWidget()
{
    delete ui;
}

void ToolBarWidget::setPreviewWindowSlot(int)
{
}

void ToolBarWidget::on_setWinBtn1_clicked()
{
    emit setPreviewWindowSig(1);
}

void ToolBarWidget::on_setWinBtn2_clicked()
{
    qDebug() << "ToolBarWidget::on_setWinBtn2_clicked";
    emit setPreviewWindowSig(4);
}

void ToolBarWidget::on_setWinBtn3_clicked()
{
    emit setPreviewWindowSig(9);
}

void ToolBarWidget::on_setWinBtn4_clicked()
{
    emit setPreviewWindowSig(16);
}
