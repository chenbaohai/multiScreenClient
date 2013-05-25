#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include <QObject>
#include <QStringList>
#include <QStringList>
#include <QPixmap>

class SkinManager : public QObject
{
    Q_OBJECT
public:
    SkinManager();
    ~SkinManager();

    static SkinManager * instance();
    static void release();

    void init();

    QStringList skins();
    QString defaultSkin();

    void changeSkin(QString skinName);
    QString currentSkin();
    QString getPicture(QString name);
    QPixmap getPixmap(QString name);
    QString getStyleFile(QString skin);

signals:
    void skinChanged();
private:    
    void skinSearch(QString);

    static SkinManager *m_skinManager;
    QString m_currentSkin;
    QStringList m_skinlist;
    QString m_path;
    QString m_defaultSkin; 

};

#endif // SKINMANAGER_H
