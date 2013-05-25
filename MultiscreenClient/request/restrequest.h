#ifndef	REST_REQUEST_H
#define REST_REQUEST_H

/** @file restrequest.h
*  @addtogroup Request_Library
*  @{
*/

#include <QObject>
#include <QUrl>
#include <QByteArray>
#include <QDomDocument>
#include <QMap>
#include <QStringList>

///REST接口的基类
/** @class  RestRequest
 *
 */
class RestRequest : public QObject
{
public:
    explicit RestRequest(QObject *parent = 0);
    ~RestRequest();

    ///获取请求的URL
    /**
     * @return 请求的URL
     */
    const QUrl& url();
    ///获取请求体
    /**
     * @return 请求体
     */
    const QByteArray data();

    const QMap<QString,QString> & params() const;

    int errorCode();
    const QString& errorMessage();

    ///分析请求的返回
    /**
     * @param result 请求的返回
     * @return 返回true则请求发送成功，返回false则请求发送失败
     */
    bool analyzeResult(const QString& result);
protected:
    ///填充URL地址
    /**
     * 每个子类填充URL中除IP地址与端口号之外的部分
     */
    virtual void appendPath();
    ///填充请求的参数
    virtual void fillMap();
    ///解析XML
    virtual bool analyzeXml(QDomDocument& doc);
    ///URL中除IP地址与端口号之外的部分
    QString  m_path;
    ///请求的参数列表
    /**
     * @return 参数列表
     */
    QMap<QString,QString> m_UrlParameter;
private:
    bool analyzeErrorNode(QDomDocument &doc);
    QByteArray convertData(QMap<QString, QString> data);
private:
    ///错误号
    int      m_errorCode;
    ///错误信息
    QString  m_errorMessage;
    ///请求的URL地址
    QUrl     m_url;
};

/**
*  @}
*/

#endif
