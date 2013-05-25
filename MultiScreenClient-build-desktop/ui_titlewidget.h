/********************************************************************************
** Form generated from reading UI file 'titlewidget.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITLEWIDGET_H
#define UI_TITLEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TitleWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *title;
    QHBoxLayout *horizontalLayout;
    QLabel *logo;
    QLabel *appName;
    QSpacerItem *horizontalSpacer;
    QToolButton *minBtn;
    QToolButton *maxBtn;
    QToolButton *closeBtn;
    QWidget *content;

    void setupUi(QWidget *TitleWidget)
    {
        if (TitleWidget->objectName().isEmpty())
            TitleWidget->setObjectName(QString::fromUtf8("TitleWidget"));
        TitleWidget->resize(785, 608);
        verticalLayout = new QVBoxLayout(TitleWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title = new QWidget(TitleWidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setMinimumSize(QSize(0, 30));
        horizontalLayout = new QHBoxLayout(title);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 1, 5, 1);
        logo = new QLabel(title);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setMinimumSize(QSize(16, 16));
        logo->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(logo);

        appName = new QLabel(title);
        appName->setObjectName(QString::fromUtf8("appName"));
        appName->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(appName);

        horizontalSpacer = new QSpacerItem(630, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        minBtn = new QToolButton(title);
        minBtn->setObjectName(QString::fromUtf8("minBtn"));
        minBtn->setMinimumSize(QSize(22, 22));
        minBtn->setMaximumSize(QSize(22, 22));

        horizontalLayout->addWidget(minBtn);

        maxBtn = new QToolButton(title);
        maxBtn->setObjectName(QString::fromUtf8("maxBtn"));
        maxBtn->setMinimumSize(QSize(22, 22));
        maxBtn->setMaximumSize(QSize(22, 22));

        horizontalLayout->addWidget(maxBtn);

        closeBtn = new QToolButton(title);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setMinimumSize(QSize(22, 22));
        closeBtn->setMaximumSize(QSize(22, 22));

        horizontalLayout->addWidget(closeBtn);


        verticalLayout->addWidget(title);

        content = new QWidget(TitleWidget);
        content->setObjectName(QString::fromUtf8("content"));

        verticalLayout->addWidget(content);

        verticalLayout->setStretch(1, 1);

        retranslateUi(TitleWidget);

        QMetaObject::connectSlotsByName(TitleWidget);
    } // setupUi

    void retranslateUi(QWidget *TitleWidget)
    {
        TitleWidget->setWindowTitle(QApplication::translate("TitleWidget", "\345\244\232\345\261\217\345\272\224\347\224\250\345\256\242\346\210\267\347\253\257", 0, QApplication::UnicodeUTF8));
        logo->setText(QString());
        appName->setText(QApplication::translate("TitleWidget", "\345\244\232\345\261\217\345\272\224\347\224\250\345\256\242\346\210\267\347\253\257", 0, QApplication::UnicodeUTF8));
        minBtn->setText(QString());
        maxBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TitleWidget: public Ui_TitleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITLEWIDGET_H
