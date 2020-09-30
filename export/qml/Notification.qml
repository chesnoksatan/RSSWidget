import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

ApplicationWindow {
    id: notification

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.SplashScreen
    visible: true

    x: Screen.desktopAvailableWidth - width - 10
    y: 10

    width: 200
    height: 50

    color: "Transparent"

    background: Rectangle {
        radius: 4
        color: "#00ced1"

        SequentialAnimation on opacity {
            id: animation
            running: false
            NumberAnimation { from: 0; to: 1; duration: 2000 }
            NumberAnimation { duration: 5000}
            NumberAnimation { from: 1; to: 0; duration: 2000 }
        }
    }

    Component.onCompleted: {
        animation.start()
        alive.start()
    }

    Timer {
        id: alive
        running: false
        repeat: false
        interval: 9000

        onTriggered: notification.close()
    }
}
