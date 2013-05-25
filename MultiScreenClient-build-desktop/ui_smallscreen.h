/********************************************************************************
** Form generated from reading UI file 'smallscreen.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMALLSCREEN_H
#define UI_SMALLSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmallScreen
{
public:

    void setupUi(QWidget *SmallScreen)
    {
        if (SmallScreen->objectName().isEmpty())
            SmallScreen->setObjectName(QString::fromUtf8("SmallScreen"));
        SmallScreen->resize(400, 300);
        SmallScreen->setStyleSheet(QString::fromUtf8("border-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));

        retranslateUi(SmallScreen);

        QMetaObject::connectSlotsByName(SmallScreen);
    } // setupUi

    void retranslateUi(QWidget *SmallScreen)
    {
        SmallScreen->setWindowTitle(QApplication::translate("SmallScreen", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SmallScreen: public Ui_SmallScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMALLSCREEN_H
