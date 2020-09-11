#ifndef FORMCONTROLLER_H
#define FORMCONTROLLER_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QObject>
#include <QSettings>

class FormController : public QObject
{
    Q_OBJECT
public:
    explicit FormController(QObject *parent = nullptr);

private:
    QQmlApplicationEngine* _engine;
    QObject* _mainWindow;

    QSettings _settings;

    /*!
     * \brief Считывает сохраненые настройки и устанавливает из в форму
     */
    void readSettings();

public slots:
    /*!
     * \brief Вызов происходит в момент закрытия окна программы,
     *        чтобы сохранить последние настройки
     */
    void writeSettings();
};

#endif // FORMCONTROLLER_H
