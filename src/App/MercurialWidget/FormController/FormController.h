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
    void writeSettings();

    void getRepositorySummary(const XmlParser::OutgoingType &summary);
    void getRequestError(const QString &error);

signals:
    void signalAddRequest(const QString &reqName);
    void signalRemoveRequest(const QString &reqName);

private:

    /*!
     * \brief Считывает сохраненые настройки и устанавливает из в форму
     */
    void readSettings();

    void addRequest(const QString &reqName);
    void removeRequest(const QString &reqName);
};

#endif // FORMCONTROLLER_H
