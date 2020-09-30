#include "HTTPRequestWorker.h"

#include <QDebug>

namespace
{
    constexpr auto MAIN_ADDRESS = "http://hg.asoft/hg/";
    constexpr auto RSS_ADDRESS = "/feed/rss";
}

HTTPRequestWorker::HTTPRequestWorker(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<XmlParser::OutgoingType>("XmlParser::OutgoingType");
}

void HTTPRequestWorker::abort()
{
    QMutexLocker locker(&m_mutex);
    m_abort = true;
}

void HTTPRequestWorker::addAddress(const QString &address)
{
    QMutexLocker locker(&m_mutex);

    const auto &mainAddress = MAIN_ADDRESS + address + RSS_ADDRESS;

    const auto it = std::find_if(m_requests.begin(), m_requests.end(), [&mainAddress](const auto &helper)
    {
        return helper->getAddress() == mainAddress;
    });

    if ( it != m_requests.end() && !m_requests.empty() )
        return;

    auto helper = std::make_unique<RequestHelper>(mainAddress);

    QObject::connect(helper.get(), &RequestHelper::signalGetSummary,
                     this, &HTTPRequestWorker::signalGetSummary);
    QObject::connect(helper.get(), &RequestHelper::signalGetRequestError,
                     this, &HTTPRequestWorker::signalGetRequestError);

    m_requests.push_back(std::move(helper));
}

void HTTPRequestWorker::removeAddress(const QString &address)
{
    QMutexLocker locker(&m_mutex);

    m_requests.erase(std::remove_if(m_requests.begin(), m_requests.end(), [&](const auto &helper)
    {
        return helper->getAddress() == address;
    }), m_requests.end());
}

void HTTPRequestWorker::request()
{
    m_abort = false;

    forever
    {
        QCoreApplication::instance()->processEvents();

        if( m_abort ) { break; }

        m_mutex.lock();

        for ( const auto &helper : m_requests )
            helper->getRequest();

        m_mutex.unlock();

        QThread::msleep(m_delay);
    }

    emit finished();
}
