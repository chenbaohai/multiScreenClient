/********************************************************************************
** Form generated from reading UI file 'screenconfigwidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENCONFIGWIDGET_H
#define UI_SCREENCONFIGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "montagelayout.h"

QT_BEGIN_NAMESPACE

class Ui_ScreenConfigWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *schemeList;
    MontageLayout *screenLayout;

    void setupUi(QWidget *ScreenConfigWidget)
    {
        if (ScreenConfigWidget->objectName().isEmpty())
            ScreenConfigWidget->setObjectName(QString::fromUtf8("ScreenConfigWidget"));
        ScreenConfigWidget->resize(787, 597);
        verticalLayout = new QVBoxLayout(ScreenConfigWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        schemeList = new QWidget(ScreenConfigWidget);
        schemeList->setObjectName(QString::fromUtf8("schemeList"));

        verticalLayout->addWidget(schemeList);

        screenLayout = new MontageLayout(ScreenConfigWidget);
        screenLayout->setObjectName(QString::fromUtf8("screenLayout"));

        verticalLayout->addWidget(screenLayout);

        verticalLayout->setStretch(1, 1);

        retranslateUi(ScreenConfigWidget);

        QMetaObject::connectSlotsByName(ScreenConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *ScreenConfigWidget)
    {
        ScreenConfigWidget->setWindowTitle(QApplication::translate("ScreenConfigWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScreenConfigWidget: public Ui_ScreenConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENCONFIGWIDGET_H
