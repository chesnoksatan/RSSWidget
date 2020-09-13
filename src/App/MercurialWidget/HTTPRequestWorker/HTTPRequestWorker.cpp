#include "HTTPRequestWorker.h"

namespace { constexpr auto MAIN_ADDRESS = "http://hg.asoft/hg/"; }

HTTPRequestWorker::HTTPRequestWorker(QObject *parent)
    : QObject(parent)

{

}

void HTTPRequestWorker::addAddress(const QString &address)
{
    QMutexLocker locker(&m_mutex);
    m_requests.push_back(std::make_unique<RequestHelper>(RequestHelper(MAIN_ADDRESS + address)));
}

void HTTPRequestWorker::removeAddress(const QString &address)
{
    QMutexLocker locker(&m_mutex);

    m_requests.erase(std::remove_if(m_requests.begin(), m_requests.end(), [&](const std::unique_ptr<RequestHelper> &helper)
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
            helper->request();

        m_mutex.unlock();

        QThread::sleep(m_delay);
    }

    emit finished();
}
