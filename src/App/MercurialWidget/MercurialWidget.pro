QT += qml quick quickcontrols2 widgets

include( ../../../common.pri )
include( ../../../app.pri )

SOURCES += main.cpp \
    Core.cpp \
    FormController/FormController.cpp \
    HTTPRequestWorker/HTTPRequestWorker.cpp \

HEADERS += \
    Core.h \
    FormController/FormController.h \
    HTTPRequestWorker/HTTPRequestWorker.h \

DISTFILES += \
    ../../../export/qml/main.qml \
