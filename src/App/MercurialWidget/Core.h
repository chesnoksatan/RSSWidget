#pragma once

#include <QObject>
#include <QMap>
#include <QThread>

#include "FormController/FormController.h"
#include "HTTPRequestWorker/HTTPRequestWorker.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

private:
    FormController *m_mainWindow;
    HTTPRequestWorker *m_requestWorker;

    QThread *m_thread;

private slots:
    void addRequest(const QString &reqName);
    void removeRequest(const QString &reqName);

private:
    void startThread();
    void initConnections();
};
