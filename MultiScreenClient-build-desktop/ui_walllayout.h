/********************************************************************************
** Form generated from reading UI file 'walllayout.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WALLLAYOUT_H
#define UI_WALLLAYOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WallLayout
{
public:

    void setupUi(QWidget *WallLayout)
    {
        if (WallLayout->objectName().isEmpty())
            WallLayout->setObjectName(QString::fromUtf8("WallLayout"));
        WallLayout->resize(429, 298);

        retranslateUi(WallLayout);

        QMetaObject::connectSlotsByName(WallLayout);
    } // setupUi

    void retranslateUi(QWidget *WallLayout)
    {
        WallLayout->setWindowTitle(QApplication::translate("WallLayout", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WallLayout: public Ui_WallLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WALLLAYOUT_H
