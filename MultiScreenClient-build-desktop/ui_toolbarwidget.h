/********************************************************************************
** Form generated from reading UI file 'toolbarwidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBARWIDGET_H
#define UI_TOOLBARWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolBarWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *setWinBtn1;
    QToolButton *setWinBtn2;
    QToolButton *setWinBtn3;
    QToolButton *setWinBtn4;

    void setupUi(QWidget *ToolBarWidget)
    {
        if (ToolBarWidget->objectName().isEmpty())
            ToolBarWidget->setObjectName(QString::fromUtf8("ToolBarWidget"));
        ToolBarWidget->resize(517, 41);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ToolBarWidget->sizePolicy().hasHeightForWidth());
        ToolBarWidget->setSizePolicy(sizePolicy);
        ToolBarWidget->setMaximumSize(QSize(16777215, 41));
        horizontalLayout = new QHBoxLayout(ToolBarWidget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 4, -1, -1);
        horizontalSpacer = new QSpacerItem(441, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        setWinBtn1 = new QToolButton(ToolBarWidget);
        setWinBtn1->setObjectName(QString::fromUtf8("setWinBtn1"));
        setWinBtn1->setMinimumSize(QSize(32, 32));
        setWinBtn1->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/1X1.png"), QSize(), QIcon::Normal, QIcon::Off);
        setWinBtn1->setIcon(icon);
        setWinBtn1->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(setWinBtn1);

        setWinBtn2 = new QToolButton(ToolBarWidget);
        setWinBtn2->setObjectName(QString::fromUtf8("setWinBtn2"));
        setWinBtn2->setMinimumSize(QSize(32, 32));
        setWinBtn2->setMaximumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("icons/2X2.png"), QSize(), QIcon::Normal, QIcon::Off);
        setWinBtn2->setIcon(icon1);
        setWinBtn2->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(setWinBtn2);

        setWinBtn3 = new QToolButton(ToolBarWidget);
        setWinBtn3->setObjectName(QString::fromUtf8("setWinBtn3"));
        setWinBtn3->setMinimumSize(QSize(32, 32));
        setWinBtn3->setMaximumSize(QSize(32, 32));
        setWinBtn3->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(setWinBtn3);

        setWinBtn4 = new QToolButton(ToolBarWidget);
        setWinBtn4->setObjectName(QString::fromUtf8("setWinBtn4"));
        setWinBtn4->setMinimumSize(QSize(32, 32));
        setWinBtn4->setMaximumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("icons/4X4.png"), QSize(), QIcon::Normal, QIcon::Off);
        setWinBtn4->setIcon(icon2);
        setWinBtn4->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(setWinBtn4);


        retranslateUi(ToolBarWidget);

        QMetaObject::connectSlotsByName(ToolBarWidget);
    } // setupUi

    void retranslateUi(QWidget *ToolBarWidget)
    {
        ToolBarWidget->setWindowTitle(QApplication::translate("ToolBarWidget", "Form", 0, QApplication::UnicodeUTF8));
        setWinBtn1->setText(QString());
        setWinBtn2->setText(QString());
        setWinBtn3->setText(QString());
        setWinBtn4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ToolBarWidget: public Ui_ToolBarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBARWIDGET_H
