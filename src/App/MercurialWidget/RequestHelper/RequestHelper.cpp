#include "RequestHelper.h"

void RequestHelper::getRequest()
{
    const auto &manager = new QNetworkAccessManager();
    manager->get(m_request);

    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, &RequestHelper::managerFinished);
}

void RequestHelper::managerFinished(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();
}
