import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        spacing: 0

        SplitView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            orientation: Qt.Horizontal

            EditorMenu {
                SplitView.fillHeight: true
                SplitView.preferredWidth: root.width * 0.3
                SplitView.minimumWidth: root.width * 0.1
                SplitView.maximumWidth: root.width * 0.5
            }

            Rectangle {
                SplitView.fillHeight: true
                SplitView.fillWidth: true

                border.width: 1

                MouseArea {
                    id: mouseArea

                    anchors.fill: parent

                    hoverEnabled: true
                }
            }
        }

        Rectangle  {
            Layout.fillWidth: true
            Layout.preferredHeight: 20

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
    }
}
