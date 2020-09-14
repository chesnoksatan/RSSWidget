#include "RequestHelper.h"

RequestHelper::RequestHelper(const QString &address, QObject *parent)
    : QObject(parent),
      m_address(address),
      m_request(QUrl(m_address)),
      m_manager(new QNetworkAccessManager())

{
    QObject::connect(m_manager, &QNetworkAccessManager::finished,
                     this, &RequestHelper::managerFinished);
}

RequestHelper::~RequestHelper()
{
    delete m_manager;
}

void RequestHelper::getRequest()
{
    // WARNING: Возможно эта хуйня в потоках не работает
    m_manager->get(m_request);
}

void RequestHelper::managerFinished(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();
}
