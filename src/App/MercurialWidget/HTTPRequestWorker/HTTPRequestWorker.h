#pragma once

#include <QCoreApplication>
#include <QObject>
#include <QMutex>
#include <QThread>

#include <RequestHelper/RequestHelper.h>

class HTTPRequestWorker : public QObject
{
    Q_OBJECT
public:
    explicit HTTPRequestWorker(QObject *parent = nullptr);

    /*!
     * \brief Прекращение работы потока
     */
    void abort();

    /*!
     * \brief addAddress
     * \param address Адрес, на который будем производить запрос
     */
    void addAddress(const QString &address);

    /*!
     * \brief removeAddress
     * \param address Адрес, который необходимо исключить из запросов
     */
    void removeAddress(const QString &address);

signals:

    /*!
     * \brief Сигнал прекращение завершения потока
     */
    void finished();

    /*!
     * \brief Сигнал о получении информации репозитория
     */
    void signalGetSummary(const XmlParser::OutgoingType &summary);
    void signalGetRequestError(const QString &error);

public slots:
    /*!
     * \brief Основная функция класса
     *        Извлекает из очереди запросов элемент и отправляет его на вычисление
     */
    void request();

private:
    // TODO: Вынести в настройки
    const unsigned long int m_delay = 5000; ///< Количество секунд задержки запросов

    std::atomic<bool> m_abort; ///< Флаг прекращения потока

    QMutex m_mutex; ///< Мьютекс для добавления запросов в вектор запросов

    /*!
     * \brief m_requests Контейнер для хранения объектов отвечающих за запросы
     */
    std::vector<std::unique_ptr<RequestHelper>> m_requests;
};
