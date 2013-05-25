/********************************************************************************
** Form generated from reading UI file 'pollingschemewidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLLINGSCHEMEWIDGET_H
#define UI_POLLINGSCHEMEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "layout/playerlayout.h"
#include "schemetree.h"

QT_BEGIN_NAMESPACE

class Ui_PollingSchemeWidget
{
public:
    QHBoxLayout *horizontalLayout_5;
    SchemeTree *pollingTreeWidget;
    QWidget *pollingMainWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *layoutLabel;
    QComboBox *layoutCombo;
    QLabel *cycleLabel;
    QSpinBox *cycleSpin;
    QSpacerItem *horizontalSpacer_3;
    QFormLayout *formLayout_2;
    QLabel *label;
    QListWidget *groupListWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QToolButton *addListBtn;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *createSchemeBtn;
    QPushButton *saveSchemeBtn;
    QPushButton *delSchemeBtn;
    QSpacerItem *horizontalSpacer;
    PlayerLayout *PlayWidget;

    void setupUi(QWidget *PollingSchemeWidget)
    {
        if (PollingSchemeWidget->objectName().isEmpty())
            PollingSchemeWidget->setObjectName(QString::fromUtf8("PollingSchemeWidget"));
        PollingSchemeWidget->resize(674, 332);
        horizontalLayout_5 = new QHBoxLayout(PollingSchemeWidget);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pollingTreeWidget = new SchemeTree(PollingSchemeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        pollingTreeWidget->setHeaderItem(__qtreewidgetitem);
        pollingTreeWidget->setObjectName(QString::fromUtf8("pollingTreeWidget"));
        pollingTreeWidget->setMinimumSize(QSize(200, 0));
        pollingTreeWidget->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_5->addWidget(pollingTreeWidget);

        pollingMainWidget = new QWidget(PollingSchemeWidget);
        pollingMainWidget->setObjectName(QString::fromUtf8("pollingMainWidget"));
        pollingMainWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(pollingMainWidget);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 0, 1, 1);
        widget = new QWidget(pollingMainWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 143));
        widget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 9, -1, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setVerticalSpacing(15);
        nameLabel = new QLabel(widget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameEdit = new QLineEdit(widget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setEnabled(true);
        nameEdit->setMinimumSize(QSize(100, 0));
        nameEdit->setMaximumSize(QSize(100, 16777215));
        nameEdit->setMaxLength(32767);
        nameEdit->setFrame(true);
        nameEdit->setCursorPosition(2);
        nameEdit->setReadOnly(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        layoutLabel = new QLabel(widget);
        layoutLabel->setObjectName(QString::fromUtf8("layoutLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, layoutLabel);

        layoutCombo = new QComboBox(widget);
        layoutCombo->setObjectName(QString::fromUtf8("layoutCombo"));
        layoutCombo->setMinimumSize(QSize(100, 0));
        layoutCombo->setMaximumSize(QSize(100, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, layoutCombo);

        cycleLabel = new QLabel(widget);
        cycleLabel->setObjectName(QString::fromUtf8("cycleLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, cycleLabel);

        cycleSpin = new QSpinBox(widget);
        cycleSpin->setObjectName(QString::fromUtf8("cycleSpin"));
        cycleSpin->setMinimumSize(QSize(100, 0));
        cycleSpin->setMaximumSize(QSize(100, 16777215));
        cycleSpin->setMaximum(1000);
        cycleSpin->setValue(5);

        formLayout->setWidget(2, QFormLayout::FieldRole, cycleSpin);


        horizontalLayout->addLayout(formLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setVerticalSpacing(6);
        formLayout_2->setContentsMargins(-1, 0, -1, 6);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        groupListWidget = new QListWidget(widget);
        groupListWidget->setObjectName(QString::fromUtf8("groupListWidget"));
        groupListWidget->setMinimumSize(QSize(110, 0));
        groupListWidget->setMaximumSize(QSize(100, 100));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, groupListWidget);


        horizontalLayout->addLayout(formLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 8);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        addListBtn = new QToolButton(widget);
        addListBtn->setObjectName(QString::fromUtf8("addListBtn"));
        addListBtn->setMinimumSize(QSize(22, 22));
        addListBtn->setMaximumSize(QSize(22, 22));

        verticalLayout->addWidget(addListBtn);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        createSchemeBtn = new QPushButton(widget);
        createSchemeBtn->setObjectName(QString::fromUtf8("createSchemeBtn"));
        createSchemeBtn->setMaximumSize(QSize(50, 16777215));

        verticalLayout_3->addWidget(createSchemeBtn);

        saveSchemeBtn = new QPushButton(widget);
        saveSchemeBtn->setObjectName(QString::fromUtf8("saveSchemeBtn"));
        saveSchemeBtn->setMaximumSize(QSize(50, 16777215));

        verticalLayout_3->addWidget(saveSchemeBtn);

        delSchemeBtn = new QPushButton(widget);
        delSchemeBtn->setObjectName(QString::fromUtf8("delSchemeBtn"));
        delSchemeBtn->setMaximumSize(QSize(50, 16777215));

        verticalLayout_3->addWidget(delSchemeBtn);


        horizontalLayout_4->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(widget);

        PlayWidget = new PlayerLayout(pollingMainWidget);
        PlayWidget->setObjectName(QString::fromUtf8("PlayWidget"));

        verticalLayout_2->addWidget(PlayWidget);

        verticalLayout_2->setStretch(1, 1);

        horizontalLayout_5->addWidget(pollingMainWidget);

        horizontalLayout_5->setStretch(1, 1);

        retranslateUi(PollingSchemeWidget);

        QMetaObject::connectSlotsByName(PollingSchemeWidget);
    } // setupUi

    void retranslateUi(QWidget *PollingSchemeWidget)
    {
        PollingSchemeWidget->setWindowTitle(QApplication::translate("PollingSchemeWidget", "Form", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("PollingSchemeWidget", "\346\226\271\346\241\210\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        nameEdit->setInputMask(QString());
        nameEdit->setText(QApplication::translate("PollingSchemeWidget", "\346\226\271\346\241\210", 0, QApplication::UnicodeUTF8));
        layoutLabel->setText(QApplication::translate("PollingSchemeWidget", "\345\270\203\345\261\200\357\274\232", 0, QApplication::UnicodeUTF8));
        layoutCombo->clear();
        layoutCombo->insertItems(0, QStringList()
         << QApplication::translate("PollingSchemeWidget", "\344\270\200\347\224\273\351\235\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PollingSchemeWidget", "\345\233\233\347\224\273\351\235\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PollingSchemeWidget", "\344\271\235\347\224\273\351\235\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("PollingSchemeWidget", "\345\215\201\345\205\255\347\224\273\351\235\242", 0, QApplication::UnicodeUTF8)
        );
        cycleLabel->setText(QApplication::translate("PollingSchemeWidget", "\345\221\250\346\234\237(\347\247\222)\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PollingSchemeWidget", "\347\273\204\345\210\227\350\241\250\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addListBtn->setToolTip(QApplication::translate("PollingSchemeWidget", "\351\200\211\346\213\251\347\233\221\346\216\247\347\273\204", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addListBtn->setText(QString());
        createSchemeBtn->setText(QApplication::translate("PollingSchemeWidget", "\346\226\260\345\273\272", 0, QApplication::UnicodeUTF8));
        saveSchemeBtn->setText(QApplication::translate("PollingSchemeWidget", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        delSchemeBtn->setText(QApplication::translate("PollingSchemeWidget", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PollingSchemeWidget: public Ui_PollingSchemeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLLINGSCHEMEWIDGET_H
