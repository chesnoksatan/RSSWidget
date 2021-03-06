import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2

ApplicationWindow {
    id: root

    visible: true

    onClosing: FormController.writeSettings()

    width: 500
    height: 500

    Connections {
        target: FormController
        onGetNewCommit: {
//            for ( var i in commit )
//                console.debug(i, commit[i])

            var comnponent = Qt.createComponent('Notification.qml');
            var object = comnponent.createObject(root, { 'title': commit["title"]});
        }

        onGetError: console.debug(errorString)
    }
}
