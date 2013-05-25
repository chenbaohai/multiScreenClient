/********************************************************************************
** Form generated from reading UI file 'screencontrolwidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENCONTROLWIDGET_H
#define UI_SCREENCONTROLWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "layout/playerlayout.h"
#include "organizationtree.h"
#include "toolbarwidget.h"

QT_BEGIN_NAMESPACE

class Ui_ScreenControlWidget
{
public:
    QHBoxLayout *horizontalLayout;
    OrganizationTree *orgTreewidget;
    QVBoxLayout *verticalLayout;
    ToolBarWidget *windowToolBar;
    PlayerLayout *screenLayout;

    void setupUi(QWidget *ScreenControlWidget)
    {
        if (ScreenControlWidget->objectName().isEmpty())
            ScreenControlWidget->setObjectName(QString::fromUtf8("ScreenControlWidget"));
        ScreenControlWidget->resize(604, 334);
        horizontalLayout = new QHBoxLayout(ScreenControlWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        orgTreewidget = new OrganizationTree(ScreenControlWidget);
        orgTreewidget->setObjectName(QString::fromUtf8("orgTreewidget"));
        orgTreewidget->setEnabled(true);
        orgTreewidget->setMinimumSize(QSize(200, 0));
        orgTreewidget->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(orgTreewidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        windowToolBar = new ToolBarWidget(ScreenControlWidget);
        windowToolBar->setObjectName(QString::fromUtf8("windowToolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(windowToolBar->sizePolicy().hasHeightForWidth());
        windowToolBar->setSizePolicy(sizePolicy);
        windowToolBar->setMinimumSize(QSize(0, 40));
        windowToolBar->setMaximumSize(QSize(16777215, 40));

        verticalLayout->addWidget(windowToolBar);

        screenLayout = new PlayerLayout(ScreenControlWidget);
        screenLayout->setObjectName(QString::fromUtf8("screenLayout"));

        verticalLayout->addWidget(screenLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(1, 1);

        retranslateUi(ScreenControlWidget);

        QMetaObject::connectSlotsByName(ScreenControlWidget);
    } // setupUi

    void retranslateUi(QWidget *ScreenControlWidget)
    {
        ScreenControlWidget->setWindowTitle(QApplication::translate("ScreenControlWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScreenControlWidget: public Ui_ScreenControlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENCONTROLWIDGET_H
