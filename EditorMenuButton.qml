import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Button {
    id: root

    property alias source: img.source
    property alias caption: caption.text

    implicitHeight: 80

    background: Rectangle {
        anchors.fill: parent

        border.width: 1
    }

    contentItem: Rectangle {
        anchors.fill: parent
        anchors.margins: 10

        ColumnLayout {
            anchors.fill: parent

            Image {
                id: img

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 40
                Layout.preferredHeight: 40
            }

            Text {
                id: caption

                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 20
            }
        }
    }
}
