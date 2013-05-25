/********************************************************************************
** Form generated from reading UI file 'screentoolbar.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENTOOLBAR_H
#define UI_SCREENTOOLBAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenToolBar
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *LtoolBtn;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *ScreenIdLayoutContents;
    QHBoxLayout *ScreenIdLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *RtoolBtn;

    void setupUi(QWidget *ScreenToolBar)
    {
        if (ScreenToolBar->objectName().isEmpty())
            ScreenToolBar->setObjectName(QString::fromUtf8("ScreenToolBar"));
        ScreenToolBar->resize(753, 67);
        horizontalLayout = new QHBoxLayout(ScreenToolBar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        LtoolBtn = new QToolButton(ScreenToolBar);
        LtoolBtn->setObjectName(QString::fromUtf8("LtoolBtn"));
        LtoolBtn->setMinimumSize(QSize(0, 67));
        LtoolBtn->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(LtoolBtn);

        scrollArea = new QScrollArea(ScreenToolBar);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 705, 65));
        ScreenIdLayoutContents = new QHBoxLayout(scrollAreaWidgetContents);
        ScreenIdLayoutContents->setObjectName(QString::fromUtf8("ScreenIdLayoutContents"));
        ScreenIdLayout = new QHBoxLayout();
        ScreenIdLayout->setObjectName(QString::fromUtf8("ScreenIdLayout"));

        ScreenIdLayoutContents->addLayout(ScreenIdLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        ScreenIdLayoutContents->addItem(horizontalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        RtoolBtn = new QToolButton(ScreenToolBar);
        RtoolBtn->setObjectName(QString::fromUtf8("RtoolBtn"));
        RtoolBtn->setMinimumSize(QSize(0, 67));
        RtoolBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        RtoolBtn->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(RtoolBtn);


        retranslateUi(ScreenToolBar);

        QMetaObject::connectSlotsByName(ScreenToolBar);
    } // setupUi

    void retranslateUi(QWidget *ScreenToolBar)
    {
        ScreenToolBar->setWindowTitle(QApplication::translate("ScreenToolBar", "Form", 0, QApplication::UnicodeUTF8));
        LtoolBtn->setText(QString());
        RtoolBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ScreenToolBar: public Ui_ScreenToolBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENTOOLBAR_H
