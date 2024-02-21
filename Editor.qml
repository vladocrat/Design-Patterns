import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import FigureController 1.0
import FigureType 1.0

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
                id: objMenu

                SplitView.fillHeight: true
                SplitView.preferredWidth: root.width * 0.3
                SplitView.minimumWidth: root.width * 0.1
                SplitView.maximumWidth: root.width * 0.5
            }

            Item {
                SplitView.fillHeight: true
                SplitView.fillWidth: true

                MouseArea {
                    id: mouseArea

                    anchors.fill: parent

                    //enabled: objMenu.chosenType != FigureType.None
                    hoverEnabled: true

                    onClicked: {
                        FigureController.addItem(objMenu.chosenType, mouseX, mouseY);
                    }
                }

                Item {
                    anchors.fill: parent

                    data: FigureController.objects
                }
            }
        }

        EditorBottomBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 20
        }
    }
}
