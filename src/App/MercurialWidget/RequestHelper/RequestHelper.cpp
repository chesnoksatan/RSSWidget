#include "RequestHelper.h"

#include "XmlParser/XmlParser.h"

void RequestHelper::getRequest()
{
    const auto &manager = new QNetworkAccessManager();
    manager->get(m_request);

    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, &RequestHelper::managerFinished);
}

void RequestHelper::managerFinished(QNetworkReply *networkReply)
{
    if (networkReply->error()) {
        qDebug() << networkReply->errorString();
        return;
    }

    QString answer = networkReply->readAll();

    const auto &reply = XmlParser::parse(answer);
}
