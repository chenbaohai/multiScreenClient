#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include <QObject>
#include <QRect>
#include <QList>

class DisPlayInfo : public QObject
{
    Q_OBJECT
public:
    explicit DisPlayInfo(QObject *parent = 0);
    ~DisPlayInfo();
    void setIdienfier(QString displayId);
    QString  Idienfier();
    void setRect(QRect & rect);
    const QRect & getDisPlayRect();
    DisPlayInfo*  clone();
    QList<QString> * OutputList();    
    void expandRect(const QList<QRect>&);

signals:
    
public slots:
private:
    QString m_Idienfier;
    QRect m_Rect;
    QList<QString> m_OutputList;
};

#endif // DISPLAYINFO_H
