/********************************************************************************
** Form generated from reading UI file 'basewidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEWIDGET_H
#define UI_BASEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWidget
{
public:

    void setupUi(QWidget *BaseWidget)
    {
        if (BaseWidget->objectName().isEmpty())
            BaseWidget->setObjectName(QString::fromUtf8("BaseWidget"));
        BaseWidget->resize(400, 300);

        retranslateUi(BaseWidget);

        QMetaObject::connectSlotsByName(BaseWidget);
    } // setupUi

    void retranslateUi(QWidget *BaseWidget)
    {
        BaseWidget->setWindowTitle(QApplication::translate("BaseWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BaseWidget: public Ui_BaseWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWIDGET_H
