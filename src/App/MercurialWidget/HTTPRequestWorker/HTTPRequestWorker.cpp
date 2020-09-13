#include "HTTPRequestWorker.h"

namespace { constexpr auto MAIN_ADDRESS = "http://hg.asoft/hg/"; }

HTTPRequestWorker::HTTPRequestWorker(QObject *parent)
    : QObject(parent)

{

}

void HTTPRequestWorker::addAddress(const QString &address)
{
    QMutexLocker locker(&m_mutex);
    m_requests.push_back(address);
}

void HTTPRequestWorker::removeAddress(const QString &address)
{
    QMutexLocker locker(&m_mutex);

    m_requests.erase(std::remove_if(m_requests.begin(), m_requests.end(), [&](const QString &currentAddress)
    {
        return currentAddress == address;
    }), m_requests.end());
}

void HTTPRequestWorker::request()
{
    m_abort = false;

    forever
    {
        QCoreApplication::instance()->processEvents();

        if( m_abort ) { break; }

        QThread::sleep(m_delay);
    }

    emit finished();
}
