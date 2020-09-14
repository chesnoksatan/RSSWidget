#ifndef REQUESTHELPER_H
#define REQUESTHELPER_H

#include <QObject>
#include <QString>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class RequestHelper final : public QObject
{
    Q_OBJECT
public:
    RequestHelper(const QString &address, QObject *parent = nullptr);
    ~RequestHelper();

    // base class should be explicitly initialized in the copy constructor
    RequestHelper(const RequestHelper& other) : QObject(), m_address(other.m_address) { }

public:
    void getRequest();

    const QString &getAddress() const { return m_address; }

public slots:
    void managerFinished(QNetworkReply *reply);

private:
    const QString m_address;
    QNetworkRequest m_request;
    QNetworkAccessManager *m_manager;

};

#endif // REQUESTHELPER_H
