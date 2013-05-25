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

///REST�ӿڵĻ���
/** @class  RestRequest
 *
 */
class RestRequest : public QObject
{
public:
    explicit RestRequest(QObject *parent = 0);
    ~RestRequest();

    ///��ȡ�����URL
    /**
     * @return �����URL
     */
    const QUrl& url();
    ///��ȡ������
    /**
     * @return ������
     */
    const QByteArray data();

    const QMap<QString,QString> & params() const;

    int errorCode();
    const QString& errorMessage();

    ///��������ķ���
    /**
     * @param result ����ķ���
     * @return ����true�������ͳɹ�������false��������ʧ��
     */
    bool analyzeResult(const QString& result);
protected:
    ///���URL��ַ
    /**
     * ÿ���������URL�г�IP��ַ��˿ں�֮��Ĳ���
     */
    virtual void appendPath();
    ///�������Ĳ���
    virtual void fillMap();
    ///����XML
    virtual bool analyzeXml(QDomDocument& doc);
    ///URL�г�IP��ַ��˿ں�֮��Ĳ���
    QString  m_path;
    ///����Ĳ����б�
    /**
     * @return �����б�
     */
    QMap<QString,QString> m_UrlParameter;
private:
    bool analyzeErrorNode(QDomDocument &doc);
    QByteArray convertData(QMap<QString, QString> data);
private:
    ///�����
    int      m_errorCode;
    ///������Ϣ
    QString  m_errorMessage;
    ///�����URL��ַ
    QUrl     m_url;
};

/**
*  @}
*/

#endif
