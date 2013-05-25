#ifndef CONFIGINI_H
#define CONFIGINI_H
#include <QSettings>
#include <QStringList>

class ConfigIni
{
public:
    ConfigIni();
    ~ConfigIni();
    static ConfigIni *instance();
    void clear();
    bool createfile();
    bool load(QString filename = "config.ini");

    //获取ini中的数据
    QString schemeName();
    QString cardType();
    QStringList keyBoard();
    int serverPort();
    QString serverIp();
    int restPort();
    QString restIp();
    void setServerPort(int);
    void setServerIp(QString);
    void setRestPort(int);
    void setRestIp(QString);
    int control();
    int key();
    bool showPic();
    bool isUsingCard();
    int grabInterval();

    int strToGreat(QString);
    QString capToLow(QString);

    bool setSchemeName(QString);
    bool setShowPic(int);
    bool setKeyboard(QString);
protected:
    QString m_schemename;
    QString m_cardtype;
    QString m_keyboard;
    QStringList m_lists;
    bool    m_showpic;
    bool    m_using;
    int     m_grabinterval;
    int     m_serverPort;
    QString m_serverIp;
    int     m_restPort;
    QString m_restIp;
    char    *m_pctl;
    char    *m_pkey;
    QString m_path;
};

#endif // CONFIGINI_H
