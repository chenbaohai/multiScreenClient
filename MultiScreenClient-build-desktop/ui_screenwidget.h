/********************************************************************************
** Form generated from reading UI file 'screenwidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENWIDGET_H
#define UI_SCREENWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenWidget
{
public:

    void setupUi(QWidget *ScreenWidget)
    {
        if (ScreenWidget->objectName().isEmpty())
            ScreenWidget->setObjectName(QString::fromUtf8("ScreenWidget"));
        ScreenWidget->resize(306, 219);
        ScreenWidget->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(ScreenWidget);

        QMetaObject::connectSlotsByName(ScreenWidget);
    } // setupUi

    void retranslateUi(QWidget *ScreenWidget)
    {
        ScreenWidget->setWindowTitle(QApplication::translate("ScreenWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScreenWidget: public Ui_ScreenWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENWIDGET_H
