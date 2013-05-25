#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QApplication>
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>

#include "skinmanager.h"
//#include "config.h"

#define SKIN_PATH "icons"
#define STYLE_SHEET_FILE "skin.css"
#define DEFAULT_SKIN "default"

SkinManager *SkinManager::m_skinManager = NULL;

SkinManager::SkinManager():
    QObject(NULL),
    m_path(QString("./%1").arg(SKIN_PATH))
{    
    this->init();
//    qDebug() << "create skin manager"<<m_path;
//    m_defaultSkin=DEFAULT_SKIN;
}

SkinManager::~SkinManager()
{
//    qDebug() << "release skin manager";
}

void SkinManager::skinSearch(QString path)
{
//    qDebug() << "finding skin in" << m_path;
    QDir currentDir = QDir(path);
    m_skinlist = currentDir.entryList(QDir::Dirs | QDir::NoSymLinks|QDir::NoDotAndDotDot);
    QStringList::iterator i = m_skinlist.begin();
    QString filename;
    QFileInfo fileInfo;
    while (i != m_skinlist.end()) {
        filename = getStyleFile(*i);
        fileInfo.setFile(filename);
        if (!fileInfo.exists()) {
            i = m_skinlist.erase(i);
        } else {
//            qDebug() << "has found skin" << *i;
            i++;
        }
    }

    if (m_skinlist.count() == 0) {
        m_defaultSkin = "";
        return;
    }
//    m_defaultSkin = Config::instance()->skin();
    if (m_skinlist.indexOf(m_defaultSkin) == -1)
        m_defaultSkin = m_skinlist.at(0);
}

void SkinManager::changeSkin(QString skinName)
{    
    QFile file(getStyleFile(skinName));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        m_currentSkin = skinName;
        QTextStream stream(&file);
        qApp->setStyleSheet(stream.readAll());
//        qDebug() << "change skin to" << skinName;
        emit skinChanged();
    }
}

QString SkinManager::currentSkin()
{
    return m_currentSkin;
}

SkinManager * SkinManager::instance()
{
    if (m_skinManager == NULL)
        m_skinManager = new SkinManager;
    return m_skinManager;
}

QString SkinManager::defaultSkin()
{
    return m_defaultSkin;
}

QString SkinManager::getPicture(QString name)
{ 
//    return m_path + "/" + m_currentSkin + "/" + name;
    return m_path + "/" + name;
}

QStringList SkinManager::skins()
{
    return m_skinlist;
}

QString SkinManager::getStyleFile(QString skin)
{ 
    return m_path + "/" + skin + "/" + STYLE_SHEET_FILE;
}

void SkinManager::init()
{
    skinSearch(m_path);
}

void SkinManager::release()
{
    if (m_skinManager != NULL)
        delete m_skinManager;
    m_skinManager = NULL;
}


QPixmap SkinManager::getPixmap(QString name)
{
    return QPixmap(getPicture(name));
}
