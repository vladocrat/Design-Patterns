import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import FigureType 1.0

RadioButton {
    id: root

    property alias source: img.source
    property alias caption: caption.text
    property int type: -1

    implicitHeight: 90

    indicator: Rectangle {
        anchors.centerIn: parent

        color: "transparent"
    }

    background: Rectangle {
        anchors.fill: parent

        color: root.checked ? "light grey" : "white"
        border.width: 1
    }

    contentItem: Item {
        anchors.centerIn: parent
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
