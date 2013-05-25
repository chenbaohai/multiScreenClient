/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *toolwidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *cardConfigBtn;
    QToolButton *screenControlBtn;
    QToolButton *screenConfigBtn;
    QToolButton *pollingSchemeBtn;
    QSpacerItem *horizontalSpacer;
    QStackedWidget *stackedWidget;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(766, 577);
        verticalLayout = new QVBoxLayout(MainWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 1, 1);
        toolwidget = new QWidget(MainWidget);
        toolwidget->setObjectName(QString::fromUtf8("toolwidget"));
        horizontalLayout = new QHBoxLayout(toolwidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 1, 0, 0);
        cardConfigBtn = new QToolButton(toolwidget);
        buttonGroup = new QButtonGroup(MainWidget);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(cardConfigBtn);
        cardConfigBtn->setObjectName(QString::fromUtf8("cardConfigBtn"));
        cardConfigBtn->setEnabled(true);
        cardConfigBtn->setFocusPolicy(Qt::NoFocus);
        cardConfigBtn->setIconSize(QSize(28, 28));
        cardConfigBtn->setCheckable(true);
        cardConfigBtn->setChecked(false);
        cardConfigBtn->setAutoExclusive(false);
        cardConfigBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        cardConfigBtn->setAutoRaise(false);

        horizontalLayout->addWidget(cardConfigBtn);

        screenControlBtn = new QToolButton(toolwidget);
        buttonGroup->addButton(screenControlBtn);
        screenControlBtn->setObjectName(QString::fromUtf8("screenControlBtn"));
        screenControlBtn->setFocusPolicy(Qt::NoFocus);
        screenControlBtn->setIconSize(QSize(28, 28));
        screenControlBtn->setCheckable(true);
        screenControlBtn->setChecked(false);
        screenControlBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(screenControlBtn);

        screenConfigBtn = new QToolButton(toolwidget);
        buttonGroup->addButton(screenConfigBtn);
        screenConfigBtn->setObjectName(QString::fromUtf8("screenConfigBtn"));
        screenConfigBtn->setFocusPolicy(Qt::NoFocus);
        screenConfigBtn->setIconSize(QSize(28, 28));
        screenConfigBtn->setCheckable(true);
        screenConfigBtn->setChecked(false);
        screenConfigBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(screenConfigBtn);

        pollingSchemeBtn = new QToolButton(toolwidget);
        buttonGroup->addButton(pollingSchemeBtn);
        pollingSchemeBtn->setObjectName(QString::fromUtf8("pollingSchemeBtn"));
        pollingSchemeBtn->setFocusPolicy(Qt::NoFocus);
        pollingSchemeBtn->setIconSize(QSize(28, 28));
        pollingSchemeBtn->setCheckable(true);
        pollingSchemeBtn->setChecked(false);
        pollingSchemeBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(pollingSchemeBtn);

        horizontalSpacer = new QSpacerItem(655, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(toolwidget);

        stackedWidget = new QStackedWidget(MainWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));

        verticalLayout->addWidget(stackedWidget);

        verticalLayout->setStretch(1, 1);

        retranslateUi(MainWidget);

        stackedWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "MainWidget", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cardConfigBtn->setToolTip(QApplication::translate("MainWidget", "\347\224\265\350\247\206\345\242\231\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cardConfigBtn->setText(QApplication::translate("MainWidget", "\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        screenControlBtn->setToolTip(QApplication::translate("MainWidget", "\344\270\212\345\242\231\351\242\204\350\247\210", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        screenControlBtn->setText(QApplication::translate("MainWidget", "\351\242\204\350\247\210", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        screenConfigBtn->setToolTip(QApplication::translate("MainWidget", "\346\213\274\346\216\245\346\213\206\345\210\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        screenConfigBtn->setText(QApplication::translate("MainWidget", "\346\213\274\346\216\245", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pollingSchemeBtn->setToolTip(QApplication::translate("MainWidget", "\344\270\212\345\242\231\350\275\256\345\267\241", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pollingSchemeBtn->setText(QApplication::translate("MainWidget", "\350\275\256\345\267\241", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
