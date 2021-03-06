#include "FormController.h"

#include <QDebug>

FormController::FormController(QObject *parent)
    : QObject(parent)
{
    _engine = new QQmlApplicationEngine;

    _engine->rootContext()->setContextProperty("FormController", this);

    QQmlComponent component(_engine, QUrl("../../../export/qml/main.qml"));
    _mainWindow = component.create();

    readSettings();
}

void FormController::readSettings()
{
    _settings.beginGroup("/Settings");

        _settings.beginGroup("/Size");
            _mainWindow->setProperty("width", _settings.value("/width",400).toInt());
            _mainWindow->setProperty("height", _settings.value("/height",600).toInt());
        _settings.endGroup();

        _settings.beginGroup("/Position");
            _mainWindow->setProperty("x", _settings.value("/x",0).toInt());
            _mainWindow->setProperty("y", _settings.value("/y",0).toInt());
        _settings.endGroup();

        _settings.endGroup();
}

void FormController::addRequest(const QString &reqName)
{
    emit signalAddRequest(reqName);
}

void FormController::removeRequest(const QString &reqName)
{
    emit signalRemoveRequest(reqName);
}

void FormController::writeSettings()
{
    _settings.beginGroup("/Settings");

        _settings.beginGroup("/Size");
            _settings.setValue("/width", _mainWindow->property("width"));
            _settings.setValue("/height", _mainWindow->property("height"));
        _settings.endGroup();

        _settings.beginGroup("/Position");
            _settings.setValue("/x", _mainWindow->property("x"));
            _settings.setValue("/y", _mainWindow->property("y"));
        _settings.endGroup();

    _settings.endGroup();
}

void FormController::getRequestError(const QString &error)
{
    emit getError(error);
}

void FormController::getRepositorySummary(const XmlParser::OutgoingType &summary)
{
    for ( const auto &commit : summary)
        emit getNewCommit(commit.toJson());
}
