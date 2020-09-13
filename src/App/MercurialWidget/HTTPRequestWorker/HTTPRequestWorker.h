#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QObject>
#include <QMutex>
#include <QCoreApplication>
#include <QThread>

class HTTPRequestWorker : public QObject
{
    Q_OBJECT
public:
    explicit HTTPRequestWorker(QObject *parent = nullptr);

    /*!
     *   \brief Прекращение работы потока
     */
    void abort() { m_abort = true; }

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
     *   \brief Сигнал прекращение завершения потока
     */
    void finished();

public slots:
    /*!
     * \brief Основная функция класса
     *        Извлекает из очереди запросов элемент и отправляет его на вычисление
     */
    void request();

private:
    int m_delay = 1; ///< Количество секунд задержки запросов

    std::atomic<bool> m_abort; ///< Флаг прекращения потока

    QMutex m_mutex; ///< Мьютекс для добавления запросов в вектор запросов

    QVector<QString> m_requests;
};

#endif // CALCULATORCONTROLLER_H
