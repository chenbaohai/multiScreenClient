#include "configini.h"
#include <QTextCodec>
#include <QDir>
#include <string.h>
#include <QDebug>

Q_GLOBAL_STATIC(ConfigIni,configIni)

ConfigIni::ConfigIni()
{
    QDir file;
    bool exist = file.exists("config.ini");
    //    qDebug() << exist;
    if (!exist)
    {
        this->createfile();
    }
    this->load();
    keyBoard();
    m_pctl = new char[10];
    m_pkey = new char[10];
}

ConfigIni::~ConfigIni()
{
    delete [] m_pctl;
    delete [] m_pkey;
}

ConfigIni* ConfigIni::instance()
{
    return configIni();
}

void ConfigIni::clear()
{
    delete configIni();
}

bool ConfigIni::createfile()
{
    QSettings ini("config.ini", QSettings::IniFormat);
    ini.setValue("/Server/ip", "192.168.208.31");
    ini.setValue("/Server/port", 5234);
    ini.setValue("/Rest/ip", "192.168.208.41");
    ini.setValue("/Rest/port", 8380);
    return true;
}

bool ConfigIni::load(QString filename)
{    
    m_path = filename;
    QSettings ini(filename, QSettings::IniFormat);
    ini.setIniCodec(QTextCodec::codecForName("UTF-8"));
    m_serverIp= ini.value("/Server/ip").toString();
    m_serverPort = ini.value("/Server/port").toInt();
    m_restIp = ini.value("/Rest/ip").toString();
    m_restPort = ini.value("/Rest/port").toInt();
    return true;
}

QString ConfigIni::schemeName()
{
    return this->m_schemename;
}

bool ConfigIni::showPic()
{
    return this->m_showpic;
}

QString ConfigIni::cardType()
{
    return this->m_cardtype;
}

QStringList ConfigIni::keyBoard()
{
    m_lists = m_keyboard.split("+");
    return m_lists;
}

int ConfigIni::grabInterval()
{
    return this->m_grabinterval;
}

bool ConfigIni::isUsingCard()
{
    return this->m_using;
}

int ConfigIni::serverPort()
{
    return this->m_serverPort;
}

QString ConfigIni::serverIp()
{
    return m_serverIp;
}

int ConfigIni::restPort()
{
    return m_restPort;
}

QString ConfigIni::restIp()
{
    return m_restIp;
}

void ConfigIni::setServerPort(int port)
{
    m_serverPort = port;    
    QSettings ini(m_path, QSettings::IniFormat);
    ini.setIniCodec(QTextCodec::codecForName("UTF-8"));
    ini.setValue("/Server/port", m_serverPort);
}

void ConfigIni::setServerIp(QString ip)
{
    m_serverIp = ip;    
    QSettings ini(m_path, QSettings::IniFormat);
    ini.setIniCodec(QTextCodec::codecForName("UTF-8"));
    ini.setValue("/Server/ip", m_serverIp);
}

void ConfigIni::setRestPort(int port)
{
    m_restPort = port;
    QSettings ini(m_path, QSettings::IniFormat);
    ini.setIniCodec(QTextCodec::codecForName("UTF-8"));
    ini.setValue("/Rest/port", m_restPort);
}

void ConfigIni::setRestIp(QString ip)
{
    m_restIp = ip;
    QSettings ini(m_path, QSettings::IniFormat);
    ini.setIniCodec(QTextCodec::codecForName("UTF-8"));
    ini.setValue("/Rest/ip", m_restIp);
}

int ConfigIni::control()
{
    QString ctl[2];
    int ctl_ = 0;
    for (int i = 0; i < (m_lists.count() - 1); i++)
    {
        ctl[i] = m_lists.at(i);
        ctl[i] = capToLow(ctl[i]);
        //        qDebug() << "ConfigIni::control" << ctl[i];
    }
    if (m_lists.count() == 2)
    {
        ctl_ = strToGreat(ctl[0]);
    }
    else if (m_lists.count() == 3)
    {
        ctl_ = strToGreat(ctl[0]) | strToGreat(ctl[1]);
    }
    //    qDebug() << "ConfigIni::control" << ctl[0] << ctl_;
    return ctl_;
}

QString ConfigIni::capToLow(QString str)
{
    char *p, *temp;
    strcpy(m_pctl, str.toLatin1().data());
    temp = m_pctl;
    //ctrl如果是大写转化为小写
    while (*temp)
    {
        if (static_cast<int>(*temp) > 64 && static_cast<int>(*temp) < 91)
        {
            (*temp) += 32;
        }
        temp++;
    }
    QString str_(m_pctl);
    return str_;
}

int ConfigIni::strToGreat(QString str)
{
    int ret = 0;
    if (str == "ctrl")
        ret = 2;
    else if (str == "shift")
        ret = 4;
    else if (str == "alt")
        ret = 1;
    else if (str == "win")
        ret = 8;
    else
        ret = -1;
    return ret;
}

int ConfigIni::key()
{
    QString key = m_lists.at(m_lists.count() - 1);
    strcpy(m_pkey, key.toLatin1().data());
    //    qDebug() << "ConfigIni::key" << key << strlen(key.toLatin1().data()) << static_cast<int>('A');
    if (strlen(m_pkey) == 1)
    {
        if (static_cast<int>(*m_pkey) > 96 && static_cast<int>(*m_pkey) < 123)
        {
            return (static_cast<int>(*m_pkey) - 32);
        }
        return static_cast<int>(*m_pkey);
    }
    else
    {
        return (static_cast<int>(*++m_pkey) + 63);
    }

}

bool ConfigIni::setSchemeName(QString str)
{
    QSettings ini("config.ini", QSettings::IniFormat);
    m_schemename = str;
    ini.setValue("/WallConfig/SchemeName", m_schemename);
}

bool ConfigIni::setShowPic(int value)
{
    QSettings ini("config.ini", QSettings::IniFormat);
    m_showpic = value;
    ini.setValue("/WallConfig/ShowPic", (int)m_showpic);
}

bool ConfigIni::setKeyboard(QString str)
{
    QSettings ini("config.ini", QSettings::IniFormat);
    m_keyboard = str;
    ini.setValue("/WallConfig/KeyBoard", m_keyboard);
}
