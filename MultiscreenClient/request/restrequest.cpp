#include <QDebug>
#include <QUrl>

#include "restrequest.h"
#include "configini.h"
#include "request_const.h"

RestRequest::RestRequest(QObject *parent)
	:QObject(parent),
	m_errorCode(0),
	m_errorMessage("")
{
//    Config::instance()->setServerHost("192.168.208.41");
//    Config::instance()->setServerPort(8380);
//    Config::instance()->setProjectName("sc");



//    Config::instance()->save();
}
RestRequest::~RestRequest()
{

}

const QUrl& RestRequest::url()
{
    m_path.clear();
    appendPath();
    m_url.setScheme("http");
    m_url.setHost(ConfigIni::instance()->restIp());
    m_url.setPort(ConfigIni::instance()->restPort());
    m_path = "/sc/"+m_path;

//    m_url.setHost(Config::instance()->serverHost());
//    m_url.setPort(Config::instance()->serverPort());
//    m_path = "/"+ Config::instance()->projectName()+"/"+m_path;

    m_url.setPath(m_path);

//    qDebug()<<"RestRequest:"<<m_url;
    return m_url;
}

const QByteArray RestRequest::data()
{
	fillMap();
//	QStringList datastr;
//	QMap<QString,QString>::iterator it;
//	for ( it = m_UrlParameter.begin(); it != m_UrlParameter.end(); ++it )
//	{
//		QString key;
//		QString value;
//		key = it.key();
//		value =it.value();
//        datastr << key+"="+value;
//	}
    return convertData(m_UrlParameter);
}

int RestRequest::errorCode()
{
	return m_errorCode;
}

const QString& RestRequest::errorMessage()
{
	return m_errorMessage;
}

bool RestRequest::analyzeResult(const QString& result)
{
    QDomDocument doc;
    QString errstr;
    int row,column;
    bool ret = doc.setContent(result,&errstr,&row,&column);
    if (ret)
    {
        if (analyzeErrorNode(doc))
        {            
            return analyzeXml(doc);
        }
    }
    else
    {
        m_errorCode = -1;
        m_errorMessage = QObject::tr(ERROR_PARSE_XML);
    }
    return false;
}

void RestRequest::appendPath()
{
    return;
}

void RestRequest::fillMap()
{
    return;
}

bool RestRequest::analyzeXml(QDomDocument &doc)
{
    return false;
}
bool RestRequest::analyzeErrorNode(QDomDocument &doc)
{
    m_errorCode = 0;
	QDomElement element = doc.documentElement();
	if (element.isNull() ) { //|| element.nodeName() != "result"
        m_errorCode = -1;
        m_errorMessage = tr(ERROR_NO_REQUEST);
		return false;
	}
	QDomNode errorNode = element.namedItem("error");
	if (!errorNode.isNull()) {
		QDomNode errorCodeNode = errorNode.namedItem("code");
		if (!errorCodeNode.isNull()) {
			m_errorCode = errorCodeNode.firstChild().nodeValue().trimmed().toInt();
		}
		QDomNode errorMessageNode = errorNode.namedItem("message");
		if (!errorMessageNode.isNull()) {
			m_errorMessage = errorMessageNode.firstChild().nodeValue().trimmed();
        }
    }
    return 0 == m_errorCode;
}

const QMap<QString, QString> & RestRequest::params() const
{
    return m_UrlParameter;
}

QByteArray RestRequest::convertData(QMap<QString, QString> data)
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
    return url.encodedQuery().replace("+", "%2B");
}
