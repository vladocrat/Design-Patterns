import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle  {
    id: root

    border.width: 1

    RowLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true

        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: 10
        }

        Text {
            Layout.alignment: Qt.AlignVCenter
            Layout.fillHeight: true
            text: "x: " + mouseArea.mouseX
        }

        Text {
            Layout.alignment: Qt.AlignVCenter
            Layout.fillHeight: true

            text: "y: " + mouseArea.mouseY
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
