/********************************************************************************
** Form generated from reading UI file 'layoutwidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYOUTWIDGET_H
#define UI_LAYOUTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LayoutWidget
{
public:

    void setupUi(QWidget *LayoutWidget)
    {
        if (LayoutWidget->objectName().isEmpty())
            LayoutWidget->setObjectName(QString::fromUtf8("LayoutWidget"));
        LayoutWidget->resize(807, 591);
        LayoutWidget->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(LayoutWidget);

        QMetaObject::connectSlotsByName(LayoutWidget);
    } // setupUi

    void retranslateUi(QWidget *LayoutWidget)
    {
        LayoutWidget->setWindowTitle(QApplication::translate("LayoutWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LayoutWidget: public Ui_LayoutWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYOUTWIDGET_H
