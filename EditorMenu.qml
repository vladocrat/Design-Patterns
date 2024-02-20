import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        spacing: 1

        EditorMenuButton {
            Layout.fillWidth: true

            source: "qrc:/static/rectangle.svg"
            caption: "rectangle"
        }

        EditorMenuButton {
            Layout.fillWidth: true

            source: "qrc:/static/circle.svg"
            caption: "circle"
        }

        EditorMenuButton {
            Layout.fillWidth: true

            source: "qrc:/static/triangle.svg"
            caption: "triangle"
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
