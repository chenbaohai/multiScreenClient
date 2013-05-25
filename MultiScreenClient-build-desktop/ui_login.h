/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Sat May 25 13:18:11 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *widget;
    QLabel *label;
    QToolButton *exitBtn;
    QPushButton *logoLabel;
    QWidget *bgWidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QPushButton *loginBtn;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *userEdit;
    QLineEdit *pwdEdit;
    QWidget *OptWidget;
    QPushButton *optBtn;
    QWidget *serverWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *serverIpEdit;
    QLabel *label_3;
    QLineEdit *portEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *edt_multiip;
    QLabel *label_5;
    QLineEdit *edt_multiport;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(468, 307);
        widget = new QWidget(Login);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 471, 30));
        widget->setMaximumSize(QSize(16777215, 30));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(29, 4, 112, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label->setFont(font);
        exitBtn = new QToolButton(widget);
        exitBtn->setObjectName(QString::fromUtf8("exitBtn"));
        exitBtn->setGeometry(QRect(440, 5, 24, 24));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(24);
        sizePolicy.setVerticalStretch(24);
        sizePolicy.setHeightForWidth(exitBtn->sizePolicy().hasHeightForWidth());
        exitBtn->setSizePolicy(sizePolicy);
        exitBtn->setMinimumSize(QSize(24, 24));
        exitBtn->setIconSize(QSize(16, 16));
        logoLabel = new QPushButton(widget);
        logoLabel->setObjectName(QString::fromUtf8("logoLabel"));
        logoLabel->setGeometry(QRect(10, 8, 16, 16));
        logoLabel->setMinimumSize(QSize(16, 16));
        logoLabel->setMaximumSize(QSize(16, 16));
        logoLabel->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        logoLabel->setIcon(icon);
        logoLabel->setIconSize(QSize(16, 16));
        logoLabel->setFlat(true);
        bgWidget = new QWidget(Login);
        bgWidget->setObjectName(QString::fromUtf8("bgWidget"));
        bgWidget->setGeometry(QRect(4, 32, 461, 271));
        verticalLayout_3 = new QVBoxLayout(bgWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_2 = new QWidget(bgWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        loginBtn = new QPushButton(widget_2);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
        loginBtn->setGeometry(QRect(340, 102, 60, 60));
        loginBtn->setFocusPolicy(Qt::NoFocus);
        loginBtn->setAutoDefault(false);
        loginBtn->setDefault(false);
        loginBtn->setFlat(false);
        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(100, 100, 223, 67));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        userEdit = new QLineEdit(widget_4);
        userEdit->setObjectName(QString::fromUtf8("userEdit"));

        verticalLayout_2->addWidget(userEdit);

        pwdEdit = new QLineEdit(widget_4);
        pwdEdit->setObjectName(QString::fromUtf8("pwdEdit"));
        pwdEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(pwdEdit);


        verticalLayout_3->addWidget(widget_2);

        OptWidget = new QWidget(bgWidget);
        OptWidget->setObjectName(QString::fromUtf8("OptWidget"));
        OptWidget->setMinimumSize(QSize(458, 29));
        OptWidget->setMaximumSize(QSize(16777215, 58));
        optBtn = new QPushButton(OptWidget);
        optBtn->setObjectName(QString::fromUtf8("optBtn"));
        optBtn->setGeometry(QRect(403, 29, 58, 29));
        optBtn->setMinimumSize(QSize(54, 29));
        optBtn->setMaximumSize(QSize(58, 29));
        optBtn->setFocusPolicy(Qt::NoFocus);
        serverWidget = new QWidget(OptWidget);
        serverWidget->setObjectName(QString::fromUtf8("serverWidget"));
        serverWidget->setGeometry(QRect(0, 0, 404, 61));
        serverWidget->setMinimumSize(QSize(404, 29));
        verticalLayout = new QVBoxLayout(serverWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 1, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, -1, 2, 0);
        label_2 = new QLabel(serverWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        serverIpEdit = new QLineEdit(serverWidget);
        serverIpEdit->setObjectName(QString::fromUtf8("serverIpEdit"));

        horizontalLayout->addWidget(serverIpEdit);

        label_3 = new QLabel(serverWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        portEdit = new QLineEdit(serverWidget);
        portEdit->setObjectName(QString::fromUtf8("portEdit"));

        horizontalLayout->addWidget(portEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, -1, 2, -1);
        label_4 = new QLabel(serverWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        edt_multiip = new QLineEdit(serverWidget);
        edt_multiip->setObjectName(QString::fromUtf8("edt_multiip"));
        edt_multiip->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(edt_multiip);

        label_5 = new QLabel(serverWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        edt_multiport = new QLineEdit(serverWidget);
        edt_multiport->setObjectName(QString::fromUtf8("edt_multiport"));

        horizontalLayout_2->addWidget(edt_multiport);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(OptWidget);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "\345\244\232\345\261\217\345\272\224\347\224\250\345\256\242\346\210\267\347\253\257", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Login", "\345\244\232\345\261\217\345\272\224\347\224\250\345\256\242\346\210\267\347\253\257", 0, QApplication::UnicodeUTF8));
        exitBtn->setText(QString());
        logoLabel->setText(QString());
        loginBtn->setText(QApplication::translate("Login", "\347\231\273 \345\275\225", 0, QApplication::UnicodeUTF8));
        optBtn->setText(QApplication::translate("Login", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Login", "\344\270\255\345\277\203\346\234\215\345\212\241IP\357\274\232", 0, QApplication::UnicodeUTF8));
        serverIpEdit->setInputMask(QApplication::translate("Login", "000.000.000.000; ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Login", "\347\253\257\345\217\243\357\274\232", 0, QApplication::UnicodeUTF8));
        portEdit->setInputMask(QString());
        label_4->setText(QApplication::translate("Login", "\345\244\232\345\261\217\346\234\215\345\212\241IP\357\274\232", 0, QApplication::UnicodeUTF8));
        edt_multiip->setInputMask(QApplication::translate("Login", "000.000.000.000; ", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Login", "\347\253\257\345\217\243\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
