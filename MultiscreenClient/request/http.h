#ifndef HTTP_H
#define HTTP_H

/** @file http.h
*  @addtogroup Request_Library
*  @{
*/

#include <QUrl>
#include <QByteArray>
#include <QMap>
#include <QStringList>

///发送REST请求的类
/** @class Http
 *
 */
class Http
{
public:
    Http();

//    static bool get(QUrl url, QMap<QString, QString> data, QByteArray &result, QMap<QString, QString> cookies, int timeout = 1000);
    static bool get(QUrl url, QByteArray data, QByteArray &result, QMap<QString, QString> cookies, int timeout = 30000);
//    static bool post(QUrl url, QMap<QString, QString> data, QByteArray &result, QMap<QString, QString> cookies, int timeout = 1000);
    static bool post(QUrl url, QByteArray data, QByteArray &result, QMap<QString, QString> cookies, int timeout = 30000);
private:
    static QByteArray convertData(QMap<QString, QString> data);
    static QByteArray convertRequest();
    static bool send(QString host, int port, QByteArray data, QByteArray &result, int timeout = 30000);
};

/**
*  @}
*/

#endif // HTTP_H
