#pragma once

#include <QObject>
#include <QString>
#include <QDebug>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class RequestHelper final : public QObject
{
    Q_OBJECT
public:
    RequestHelper(const QString &address, QObject *parent = nullptr)
      : QObject(parent),
        m_address(address),
        m_request(QUrl(m_address)) {}

    ~RequestHelper() {}

public:
    void getRequest();

    const QString &getAddress() const { return m_address; }

public slots:
    void managerFinished(QNetworkReply *reply);

private:
    const QString m_address;
    QNetworkRequest m_request;
};
