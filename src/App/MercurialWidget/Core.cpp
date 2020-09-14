#include "Core.h"

Core::Core(QObject *parent)
    : QObject(parent),
      m_mainWindow(new FormController()),
      m_requestWorker(new HTTPRequestWorker()),
      m_thread(new QThread())
{
    startThread();

    QObject::connect(m_mainWindow, &FormController::signalAddRequest,
                     this, &Core::addRequest);

    QObject::connect(m_mainWindow, &FormController::signalRemoveRequest,
                     this, &Core::removeRequest);
}

Core::~Core()
{
    if (m_thread->isRunning())
    {
        m_requestWorker->abort();
        m_thread->quit();
        m_thread->wait();
    }

    delete m_thread;
    delete m_requestWorker;

    delete m_mainWindow;
}

void Core::addRequest(const QString &reqName)
{
    m_requestWorker->addAddress(reqName);
}

void Core::removeRequest(const QString &reqName)
{
    m_requestWorker->removeAddress(reqName);
}

void Core::startThread()
{
    m_requestWorker->moveToThread(m_thread);

    //! В момент запуска второстепенного потока вызвается функция calculate
    QObject::connect(m_thread, &QThread::started,
                     m_requestWorker, &HTTPRequestWorker::request);

    //! При завершении работы функции calculate потоку передается сигнал finished,
    //! который вызывает срабатывание слота quit
    QObject::connect(m_requestWorker, &HTTPRequestWorker::finished,
                     m_thread, &QThread::quit);

    m_thread->start();
}
