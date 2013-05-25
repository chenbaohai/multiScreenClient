#ifndef RESTDATA_H
#define RESTDATA_H

#include "basedata.h"

class InteractData : public BaseData
{
    Q_OBJECT
public:
    explicit InteractData(QObject *parent = 0);

    virtual const QByteArray* getSendData();
    void setSendData(int cmd, QString data);
    QString buildUpData(int cmd, QString data);
signals:

public slots:

private:
    QByteArray m_restSendData;
};

#endif // RESTDATA_H
