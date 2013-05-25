#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QDomDocument>

class Entity : public QObject
{
    Q_OBJECT
public:
    explicit Entity(QObject *parent = 0);
    virtual void clear();
    virtual bool validates();
    virtual void fromXml(QDomElement);

signals:

public slots:

};

#endif // ENTITY_H
