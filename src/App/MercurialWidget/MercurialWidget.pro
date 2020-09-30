QT += qml quick quickcontrols2 widgets xml network

include( ../../../common.pri )
include( ../../../app.pri )

SOURCES += main.cpp \
    Core.cpp \
    FormController/FormController.cpp \
    HTTPRequestWorker/HTTPRequestWorker.cpp \
    RequestHelper/RequestHelper.cpp \
    XmlParser/XmlParser.cpp

HEADERS += \
    Core.h \
    FormController/FormController.h \
    HTTPRequestWorker/HTTPRequestWorker.h \
    RequestHelper/RequestHelper.h \
    XmlParser/XmlParser.h
