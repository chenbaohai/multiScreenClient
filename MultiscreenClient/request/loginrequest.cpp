#include "loginrequest.h"
#include <QDebug>

LoginRequest::LoginRequest(QObject *parent ):
    RestRequest(parent),
    m_user(""),
    m_password("")
{

}

void LoginRequest::fillMap()
{
    this->m_UrlParameter.insert("_type","ws");
    this->m_UrlParameter.insert("loginName", m_user);
    this->m_UrlParameter.insert("password", m_password);
}

void LoginRequest::appendPath()
{
    m_path = "login";
}

bool LoginRequest::analyzeXml(QDomDocument &doc)
{
    QDomElement root = doc.documentElement();
//    qDebug() << "LoginRequest::analyzeXml" << root.childNodes().count();
    for (int j = 0,i = 0; i < root.childNodes().count(); i++)
    {
        if (root.childNodes().at(i).nodeName() == "Token")
        {
            m_token = root.childNodes().at(i).toElement().text();
            if (m_token == "")
            {
                return false;
            }
            return true;
        }
    }
    return false;
}

QString LoginRequest::getToken()
{
    return m_token;
}

void LoginRequest::setUser(QString user)
{
    m_user = user;
}

void LoginRequest::setPassword(QString password)
{
    m_password = password;
}
