/********************************************************************************
** Form generated from reading UI file 'selectgroupdlg.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTGROUPDLG_H
#define UI_SELECTGROUPDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "grouptree.h"

QT_BEGIN_NAMESPACE

class Ui_SelectGroupDlg
{
public:
    QVBoxLayout *verticalLayout;
    GroupTree *selectGroupWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_ok;
    QPushButton *btn_cancel;

    void setupUi(QDialog *SelectGroupDlg)
    {
        if (SelectGroupDlg->objectName().isEmpty())
            SelectGroupDlg->setObjectName(QString::fromUtf8("SelectGroupDlg"));
        SelectGroupDlg->resize(265, 333);
        SelectGroupDlg->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(SelectGroupDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 6);
        selectGroupWidget = new GroupTree(SelectGroupDlg);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        selectGroupWidget->setHeaderItem(__qtreewidgetitem);
        selectGroupWidget->setObjectName(QString::fromUtf8("selectGroupWidget"));

        verticalLayout->addWidget(selectGroupWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_ok = new QPushButton(SelectGroupDlg);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));
        btn_ok->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(btn_ok);

        btn_cancel = new QPushButton(SelectGroupDlg);
        btn_cancel->setObjectName(QString::fromUtf8("btn_cancel"));
        btn_cancel->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(btn_cancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SelectGroupDlg);

        QMetaObject::connectSlotsByName(SelectGroupDlg);
    } // setupUi

    void retranslateUi(QDialog *SelectGroupDlg)
    {
        SelectGroupDlg->setWindowTitle(QApplication::translate("SelectGroupDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        btn_ok->setText(QApplication::translate("SelectGroupDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        btn_cancel->setText(QApplication::translate("SelectGroupDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectGroupDlg: public Ui_SelectGroupDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTGROUPDLG_H
