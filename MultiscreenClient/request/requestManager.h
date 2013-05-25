#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

/** @file requestManager.h
*  @addtogroup Request_Library
*  @{
*/

#include <QString>
#include <QMap>
#include <QDateTime>
#include <QUrl>
#include "request_global.h"
#include "dvr.h"
#include "organizationrequest.h"
#include "loginrequest.h"
#include "interactdata.h"
#include "organization.h"
#include "group.h"

class SkyFSConfig;

///错误信息
/** @struct RequestErrorInfo
 * 用于保存请求的错误信息，包括错误号与错误内容
 */
struct RequestErrorInfo {
    int errorCode;
    QString errorMessage;
};

///请求管理类
/** @class RequestManager
 * 用于组装请求，发送请求，获得返回数据
 */
class RequestManager : public QObject
{
    Q_OBJECT
public:
    RequestManager(QObject *parent = 0);
    virtual ~RequestManager();

    static RequestManager* instance();
    static void release();

    bool token(LoginRequest*);
    int errorCode();
    QString errorMessage();

    void setToken(const QString& token);
    bool getOrgInfo(OrgList *list);
    bool getGroupInfo(GroupList *list);
    QString getXml();
    QString getToken();
    QString getGroupXml();
signals:
    void error(int errorCode, QString errorMsg);
private:
    virtual bool visitGetRest(QUrl& url,QByteArray& data, QString &result, int timeout = 30000);
    virtual bool visitPostRest(QUrl& url,QByteArray& data, QString &result, int timeout = 30000);

    bool sendGetRequest(RestRequest *request, int timeout = 30000);
    bool sendPostRequest(RestRequest *request, int timeout = 30000);

    void fillError(int errorCode, QString errorMessage);
private:
    QString  m_token;
    QString  m_restXml;
    QString  m_groupXml;
    bool m_bXml, m_bGroup;
    static RequestManager*     s_requestManager;
    QMap<int,RequestErrorInfo> m_error;    
};

/**
*  @}
*/

#endif
