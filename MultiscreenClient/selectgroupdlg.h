#ifndef SELECTGROUPDLG_H
#define SELECTGROUPDLG_H

#include <QDialog>
#include "group.h"
#include <QTreeWidgetItem>

namespace Ui {
    class SelectGroupDlg;
}

class SelectGroupDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelectGroupDlg(QWidget *parent = 0);
    ~SelectGroupDlg();
    void setGroupInfo(GroupList *);
    GroupList groups();


private slots:
    void on_selectGroupWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::SelectGroupDlg *ui;
private:
    GroupList m_groups;

    GroupList getSelectGroup();

};

#endif // SELECTGROUPDLG_H
