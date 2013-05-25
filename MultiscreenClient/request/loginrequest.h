#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "restrequest.h"
#include <QDomDocument>

class LoginRequest : public RestRequest
{
public:
    LoginRequest(QObject *parent = 0);
    QString getToken();
    void setUser(QString);
    void setPassword(QString);
protected:
    void fillMap();
    bool analyzeXml(QDomDocument &doc);
    void appendPath();
private:
    QString m_token;
    QString m_user;
    QString m_password;
};

#endif // LOGINREQUEST_H
