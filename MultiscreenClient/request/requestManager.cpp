#include <QDebug>
#include <QThread>

//#include "entity_const.h"
#include "request_const.h"
#include "requestManager.h"
#include "dvr.h"
#include "organization.h"
#include "grouprequest.h"
#include "get_rest.h"
#include "http.h"

RequestManager* RequestManager::s_requestManager = NULL;

RequestManager::RequestManager(QObject *parent):
    QObject(parent),
    m_bXml(false),
    m_bGroup(false)
{
    initializeWinsockIfNecessary();
}

RequestManager::~RequestManager()
{
    uninitializeWinsockIfNecessary();
}

RequestManager* RequestManager::instance()
{
    if (s_requestManager == NULL)
    {
        s_requestManager = new RequestManager;
    }
    return s_requestManager;
}

void RequestManager::release()
{
    if (s_requestManager)
        delete s_requestManager;
    s_requestManager = NULL;
}

bool RequestManager::token(LoginRequest *request)
{
    if (this->sendGetRequest(request))
    {
        setToken(request->getToken());
        return true;
    }
    return false;
}

void RequestManager::setToken(const QString& token)
{
    m_token = token;
}

bool RequestManager::visitGetRest(QUrl& url,QByteArray& data, QString &result, int timeout)
{
//    bool res;
//    QByteArray response;
//    QMap<QString,QString> cookies;
//    if (!m_token.isEmpty())
//        cookies.insert("csst_token",m_token);
//    res = Http::get(url,data,response,cookies,timeout);
//    if (res) {
////        result = QString(response);
//        result = QString::fromUtf8(response);
//    }
//    return res;

    if (url.isEmpty() && data.isEmpty())
        return false;

    std::string urlstr;
    if (!data.isEmpty())
    {
        QString tmp;
        tmp.append(url.toEncoded());
        tmp.append('?');
        QUrl tmpUrl(data);
        tmp.append(tmpUrl.toEncoded());
        urlstr = tmp.toStdString();
    }
    else
    {
        urlstr = QString(url.toEncoded()).toStdString();
    }

    std::string res;
    std::string token = m_token.toStdString();
//    qDebug()<<"GET URL: " << QString::fromStdString(urlstr)<<"Params:"<< data;

    int state = sky_rest::get_rest(urlstr, res,5,token);
//    qDebug() << "Result:" << QString::fromStdString(res);
    if (state != 0)
    {
//        qDebug() << "get_rest error, error code is" << state;
        return false;
    }
    result = QString::fromStdString(res);
    return true;
}

bool RequestManager::visitPostRest(QUrl& url,QByteArray& data, QString &result, int timeout)
{
    bool res;
    QByteArray response;
    QMap<QString,QString> cookies;
    if (!m_token.isEmpty())
        cookies.insert("csst_token",m_token);
    res = Http::post(url,data,response,cookies,timeout);
    if (res) {
        result = QString::fromUtf8(response);
    }
    return res;

//    if (url.isEmpty() && data.isEmpty())
//        return false;

//    std::string urlstr = QString(url.toEncoded()).toStdString();
//    std::string datastr = QString(QUrl(data).toEncoded()).toStdString();
//    std::string res;
////    qDebug()<<"POST URL: " << QString::fromStdString(urlstr)<<"Params:"<< data;
//    int state = sky_rest::post_rest(urlstr,datastr,res,5,m_token.toStdString());
//    //qDebug() << "Result:" << QString::fromStdString(res);
//    if (state != 0)
//    {
////        qDebug() << "post_rest error, error code is" << state;
//        return false;
//    }
//    result = QString::fromStdString(res);
//    return true;
}

int RequestManager::errorCode()
{
    int threadId = (int)QThread::currentThreadId();
    if (m_error.contains(threadId)) {
        return m_error.value(threadId).errorCode;
    }
    return 0;
}

QString RequestManager::errorMessage()
{
    int threadId = (int)QThread::currentThreadId();
    if (m_error.contains(threadId)) {
        return m_error.value(threadId).errorMessage;
    }
    return "";
}

void RequestManager::fillError(int errorCode, QString errorMessage)
{
    RequestErrorInfo errorInfo;
    errorInfo.errorCode = errorCode;
    errorInfo.errorMessage = errorMessage;
    m_error.insert((int)QThread::currentThreadId(),errorInfo);

    qDebug() << "Send http request error, error code is"
             << errorCode
             << ". error message is"
             << errorMessage
             << ".";

    emit error(errorCode,errorMessage);
}

bool RequestManager::getOrgInfo(OrgList *list)
{
    OrganizationRequest request;
    m_bXml = true;
    request.setToken(m_token);
    request.setOrgList(list);
    return this->sendGetRequest(&request);
}


bool RequestManager::getGroupInfo(GroupList *list)
{
    GroupRequest request;
    m_bGroup = true;
    request.setToken(m_token);
    request.setGroupList(list);
    return this->sendGetRequest(&request);
}

bool RequestManager::sendGetRequest(RestRequest *request, int timeout)
{
    if (request == NULL)  {
        fillError(-1,QObject::tr(ERROR_NO_REQUEST));
        return false;
    }

    QUrl url = request->url();
    QByteArray data = request->data();
    QString result;
    if (visitGetRest(url,data,result,timeout))
    {
//        qDebug() << result;
        bool res = request->analyzeResult(result);
        if (!res) {
            fillError(request->errorCode(),request->errorMessage());
        }
        if (m_bXml)
        {
            m_restXml = result;
            m_bXml = false;
        }

        if (m_bGroup)
        {
            m_groupXml = result;
            m_bGroup = false;
        }
        return res;
    }
    else
    {
        fillError(-1,QObject::tr(ERROR_SEND_REQUEST));
    }

    return false;
}

bool RequestManager::sendPostRequest(RestRequest *request, int timeout)
{
    if (request == NULL) {
        fillError(-1,QObject::tr(ERROR_NO_REQUEST));
        return false;
    }

    QUrl url = request->url();
    QByteArray data = request->data();
    QString result;
    if (visitPostRest(url,data,result,timeout))
    {
        bool res = request->analyzeResult(result);
        if (!res) {
            fillError(request->errorCode(),request->errorMessage());
        }
        return res;
    }
    else
    {
        fillError(-1,QObject::tr(ERROR_SEND_REQUEST));
    }
    return false;
}

QString RequestManager::getXml()
{
    return m_restXml;
}

QString RequestManager::getToken()
{
    return m_token;
}

QString RequestManager::getGroupXml()
{
    return m_groupXml;
}
