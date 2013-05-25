#include "selectgroupdlg.h"
#include "ui_selectgroupdlg.h"
#include <QDebug>

SelectGroupDlg::SelectGroupDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectGroupDlg)
{
    ui->setupUi(this);     
    this->setWindowTitle(QString::fromLocal8Bit("Ñ¡Ôñ¼à¿Ø×é"));
    this->setAttribute(Qt::WA_StyledBackground);
}

SelectGroupDlg::~SelectGroupDlg()
{
    delete ui;
}

void SelectGroupDlg::setGroupInfo(GroupList *list)
{
    ui->selectGroupWidget->setGroupInfo(list);
}

void SelectGroupDlg::on_selectGroupWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Qt::CheckState state=item->checkState(0);
    qDebug()<<"on_treeWidget_itemClicked"<<state;
//    if(state!=Qt::Checked)
//        state=Qt::Unchecked;
//    else
//        state=Qt::Checked;

    for(int i=0;i<item->childCount();i++)
    {
        QTreeWidgetItem *tmp=item->child(i);
        tmp->setCheckState(0,state);
    }
}

GroupList SelectGroupDlg::getSelectGroup()
{
    QTreeWidgetItemIterator it(ui->selectGroupWidget);
    while (*it)
    {
        QTreeWidgetItem *item=(*it);
        if(item->checkState(0)==Qt::Checked)
        {
            Group *group = (Group *)item->data(1,0).toInt();
            m_groups.append(group);
        }
        ++it;
    }
    return m_groups;
}

GroupList SelectGroupDlg::groups()
{
    return getSelectGroup();
}

void SelectGroupDlg::on_btn_ok_clicked()
{
    this->accept();
}

void SelectGroupDlg::on_btn_cancel_clicked()
{
    this->reject();
}
