/********************************************************************************
** Form generated from reading UI file 'rectangle.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTANGLE_H
#define UI_RECTANGLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rectangle
{
public:

    void setupUi(QWidget *rectangle)
    {
        if (rectangle->objectName().isEmpty())
            rectangle->setObjectName(QString::fromUtf8("rectangle"));
        rectangle->resize(400, 300);
        rectangle->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        retranslateUi(rectangle);

        QMetaObject::connectSlotsByName(rectangle);
    } // setupUi

    void retranslateUi(QWidget *rectangle)
    {
        rectangle->setWindowTitle(QApplication::translate("rectangle", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class rectangle: public Ui_rectangle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTANGLE_H
