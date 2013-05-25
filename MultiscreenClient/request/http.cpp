#include <QTcpSocket>
#include <QHostAddress>

#include "http.h"

Http::Http()
{
}

//bool Http::get(QUrl url, QMap<QString, QString> data, QByteArray &result, QMap<QString, QString> cookies, int timeout)
//{
//    QByteArray body;
//    QByteArray cookiesData = convertData(cookies);
//    QByteArray paramsData = convertData(data);

//    QString urlstr;
//    if (!data.isEmpty()) {
//        urlstr.append(url.toEncoded());
//        urlstr.append('?');
//        urlstr.append(QUrl(paramsData).toEncoded());
//    } else {
//        urlstr = url.toEncoded();
//    }

//    body.append(QString("GET %1 HTTP/1.1\r\n").arg(urlstr));
//    body.append(QString("Host: %1:%2\r\n").arg(url.host()).arg(url.port()));
//    body.append("Connection: close\r\n");
//    if (!cookies.isEmpty()) {
//        body.append("Cookie: ");
//        body.append(cookiesData);
//        body.append("\r\n");
//    }
//    body.append("\r\n");
//    return send(url.host(),url.port(),body,result,timeout);
//}

bool Http::get(QUrl url, QByteArray data, QByteArray &result, QMap<QString, QString> cookies, int timeout)
{
    QByteArray body;
    QByteArray cookiesData = convertData(cookies);

    QString urlstr;
    if (!data.isEmpty()) {
        urlstr.append(url.toEncoded());
        urlstr.append('?');
        urlstr.append(data);
    } else {
        urlstr = url.toEncoded();
    }

    body.append(QString("GET %1 HTTP/1.1\r\n").arg(urlstr));
    body.append(QString("Host: %1:%2\r\n").arg(url.host()).arg(url.port()));
    body.append("Connection: close\r\n");
    if (!cookies.isEmpty()) {
        body.append("Cookie: ");
        body.append(cookiesData);
        body.append("\r\n");
    }
    body.append("\r\n");
    return send(url.host(),url.port(),body,result,timeout);
}

//bool Http::post(QUrl url, QMap<QString, QString> data, QByteArray &result, QMap<QString, QString> cookies, int timeout)
//{
//    QByteArray body;
//    QByteArray cookiesData = convertData(cookies);
//    QByteArray paramsData = convertData(data);
//    QString urlstr = url.toEncoded();

//    body.append(QString("POST %1 HTTP/1.1\r\n").arg(urlstr));
//    body.append(QString("Host: %1:%2\r\n").arg(url.host()).arg(url.port()));
//    body.append(QString("Content-Length: %1\r\n").arg(paramsData.length()));
//    body.append("Content-Type: application/x-www-form-urlencoded\r\n");
//    body.append("Connection: close\r\n");
//    if (!cookies.isEmpty()) {
//        body.append("Cookie: ");
//        body.append(cookiesData);
//        body.append("\r\n");
//    }
//    body.append("\r\n");
//    body.append(paramsData);
//    return send(url.host(),url.port(),body,result,timeout);
//}

bool Http::post(QUrl url, QByteArray data, QByteArray &result, QMap<QString, QString> cookies, int timeout)
{
    QByteArray body;
    QByteArray cookiesData = convertData(cookies);
    QString urlstr = url.toEncoded();

    body.append(QString("POST %1 HTTP/1.1\r\n").arg(urlstr));
    body.append(QString("Host: %1:%2\r\n").arg(url.host()).arg(url.port()));
    body.append(QString("Content-Length: %1\r\n").arg(data.length()));
    body.append("Content-Type: application/x-www-form-urlencoded\r\n");
    body.append("Connection: close\r\n");
    if (!cookies.isEmpty()) {
        body.append("Cookie: ");
        body.append(cookiesData);
        body.append("\r\n");
    }
    body.append("\r\n");
    body.append(data);
    return send(url.host(),url.port(),body,result,timeout);
}

QByteArray Http::convertData(QMap<QString, QString> data)
{
    QString key;
    QString value;
    QUrl url;
    QList<QPair<QString, QString> > list;
    QMap<QString, QString>::const_iterator i = data.constBegin();
    while(i != data.constEnd()) {
        key = i.key();
        value = i.value();
        list.append(QPair<QString,QString>(key,value));
        i++;
    }
    url.setQueryItems(list);
    return url.encodedQuery() ;
}

bool Http::send(QString host, int port, QByteArray data, QByteArray &result, int timeout)
{
    QByteArray response;
    QTcpSocket socket;
    int numRead = 0;
    int numReadTotal = 0;
    char buffer[50];

    socket.connectToHost(QHostAddress(host),port);
    if (!socket.waitForConnected(timeout)) {
        return false;
    }

    socket.write(data);
    if (!socket.waitForBytesWritten(timeout))
    {
        return false;
    }

    forever {
        numRead  = socket.read(buffer, 50);
        numReadTotal += numRead;
        response.append(buffer,numRead);
        if (numRead == 0 && !socket.waitForReadyRead(timeout))
            break;
    }
    socket.disconnectFromHost();

    int header = response.indexOf("\r\n\r\n");
    if (header != -1) {
        result = response.mid(header+4);
    }
    return true;
}
