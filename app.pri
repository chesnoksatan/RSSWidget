#Переменная DESTDIR указывает путь, в который будет помещен готовый исполняемый файл
DESTDIR = $${BIN_PATH}/

#определяется путь поиска динамических библиотек по умолчанию
macx:
else: unix: QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../../lib.$${OS_SUFFIX}/

QMAKE_LFLAGS_RPATH=

DISTFILES += \
    $$PWD/export/qml/main.qml \
    $$PWD/export/qml/Notification.qml \
