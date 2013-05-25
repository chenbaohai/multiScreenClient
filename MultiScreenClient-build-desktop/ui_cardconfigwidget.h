/********************************************************************************
** Form generated from reading UI file 'cardconfigwidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDCONFIGWIDGET_H
#define UI_CARDCONFIGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "montagelayout.h"
#include "screentoolbar.h"

QT_BEGIN_NAMESPACE

class Ui_CardConfigWidget
{
public:
    QHBoxLayout *horizontalLayout_11;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpinBox *spinBoxRow;
    QLabel *label_2;
    QSpinBox *spinBoxCol;
    QPushButton *btnSetLayout;
    QPushButton *btnRecognise;
    QPushButton *btnSave;
    ScreenToolBar *screenBar;
    MontageLayout *wx_layout;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_5;

    void setupUi(QWidget *CardConfigWidget)
    {
        if (CardConfigWidget->objectName().isEmpty())
            CardConfigWidget->setObjectName(QString::fromUtf8("CardConfigWidget"));
        CardConfigWidget->resize(577, 312);
        horizontalLayout_11 = new QHBoxLayout(CardConfigWidget);
        horizontalLayout_11->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        widget = new QWidget(CardConfigWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, 4, -1, 6);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBoxRow = new QSpinBox(widget);
        spinBoxRow->setObjectName(QString::fromUtf8("spinBoxRow"));
        spinBoxRow->setMaximumSize(QSize(35, 16777215));
        spinBoxRow->setValue(3);

        horizontalLayout->addWidget(spinBoxRow);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBoxCol = new QSpinBox(widget);
        spinBoxCol->setObjectName(QString::fromUtf8("spinBoxCol"));
        spinBoxCol->setMaximumSize(QSize(35, 16777215));
        spinBoxCol->setValue(3);

        horizontalLayout->addWidget(spinBoxCol);

        btnSetLayout = new QPushButton(widget);
        btnSetLayout->setObjectName(QString::fromUtf8("btnSetLayout"));
        btnSetLayout->setMinimumSize(QSize(40, 25));
        btnSetLayout->setMaximumSize(QSize(40, 25));

        horizontalLayout->addWidget(btnSetLayout);

        btnRecognise = new QPushButton(widget);
        btnRecognise->setObjectName(QString::fromUtf8("btnRecognise"));
        btnRecognise->setMinimumSize(QSize(40, 25));
        btnRecognise->setMaximumSize(QSize(40, 25));

        horizontalLayout->addWidget(btnRecognise);

        btnSave = new QPushButton(widget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(40, 25));
        btnSave->setMaximumSize(QSize(40, 25));

        horizontalLayout->addWidget(btnSave);


        verticalLayout_3->addLayout(horizontalLayout);

        screenBar = new ScreenToolBar(widget);
        screenBar->setObjectName(QString::fromUtf8("screenBar"));
        screenBar->setMinimumSize(QSize(0, 0));
        screenBar->setMaximumSize(QSize(16777215, 70));

        verticalLayout_3->addWidget(screenBar);

        wx_layout = new MontageLayout(widget);
        wx_layout->setObjectName(QString::fromUtf8("wx_layout"));
        wx_layout->setMinimumSize(QSize(0, 150));

        verticalLayout_3->addWidget(wx_layout);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout_3->setStretch(2, 8);

        horizontalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_11->addWidget(widget);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));

        horizontalLayout_11->addLayout(verticalLayout_5);


        retranslateUi(CardConfigWidget);

        QMetaObject::connectSlotsByName(CardConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *CardConfigWidget)
    {
        CardConfigWidget->setWindowTitle(QApplication::translate("CardConfigWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CardConfigWidget", "\350\241\214\346\225\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CardConfigWidget", "\345\210\227\346\225\260", 0, QApplication::UnicodeUTF8));
        btnSetLayout->setText(QApplication::translate("CardConfigWidget", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        btnRecognise->setText(QApplication::translate("CardConfigWidget", "\350\257\206\345\210\253", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("CardConfigWidget", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CardConfigWidget: public Ui_CardConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDCONFIGWIDGET_H
