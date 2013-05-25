#include "mainwidget.h"
#include "titlewidget.h"
#include "screencontrolwidget.h"
#include "cardconfigwidget.h"
#include "pollingschemewidget.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include "login.h"
#include "subscreen.h"
#include "skinmanager.h"
#include "interactdata.h"
#include "smallscreen.h"
#include "walllayout.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    SkinManager::instance()->init();
    SkinManager::instance()->changeSkin(SkinManager::instance()->defaultSkin());

    Login login;
//    if (login.exec() != QDialog::Accepted)
//    {
//        return -1;
//    }

    MainWidget w(login.msgSocket());
    w.setWindowTitle("多屏应用客户端");
//    ScreenControlWidget w;
//    PollingSchemeWidget w;
    w.show();

    return a.exec();
}
