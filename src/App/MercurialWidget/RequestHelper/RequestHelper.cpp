#include "RequestHelper.h"

void RequestHelper::getRequest()
{
    const auto &manager = new QNetworkAccessManager();
    manager->get(m_request);

    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, &RequestHelper::managerFinished);

    manager->deleteLater();
}

void RequestHelper::managerFinished(QNetworkReply *networkReply)
{
    if (networkReply->error())
    {
        emit signalGetRequestError(networkReply->errorString());
        return;
    }

    emit signalGetSummary(XmlParser::parse(networkReply->readAll()));
}
