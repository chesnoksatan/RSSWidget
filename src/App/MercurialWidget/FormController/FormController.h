#ifndef FORMCONTROLLER_H
#define FORMCONTROLLER_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QObject>
#include <QSettings>

#include <XmlParser/XmlParser.h>

class FormController : public QObject
{
    Q_OBJECT
public:
    explicit FormController(QObject *parent = nullptr);

private:
    QQmlApplicationEngine* _engine;
    QObject* _mainWindow;

    QSettings _settings;

public slots:
    /*!
     * \brief Вызов происходит в момент закрытия окна программы,
     *        чтобы сохранить последние настройки
     */
    Q_INVOKABLE void writeSettings();

    Q_INVOKABLE void addRequest(const QString &reqName);
    Q_INVOKABLE void removeRequest(const QString &reqName);

    void getRepositorySummary(const XmlParser::OutgoingType &summary);
    void getRequestError(const QString &error);

signals:
    void signalAddRequest(const QString &reqName);
    void signalRemoveRequest(const QString &reqName);
    void getNewCommit(const QJsonObject &commit);
    void getError(const QString &errorString);

private:

    /*!
     * \brief Считывает сохраненые настройки и устанавливает из в форму
     */
    void readSettings();
};

#endif // FORMCONTROLLER_H
