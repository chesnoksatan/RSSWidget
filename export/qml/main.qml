import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: root

    visible: true

    onClosing: FormController.writeSettings()

    width: 500
    height: 500
}
