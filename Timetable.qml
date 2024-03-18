import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import DivisionController 1.0

Item {
    id: root

    QtObject {
        id: internal

        property int topMargin: 50

        property int leftMargin: {
            var middle = root.width / 2;
            return middle - 100 * 2
        }
    }

    ColumnLayout {
        anchors.fill: parent

        spacing: 0

        Row {
            id: tableHeader

            Layout.leftMargin: internal.leftMargin
            Layout.topMargin: internal.topMargin

            z: 2
            spacing: 0

            Repeater {
                model: tableView.columns

                Label {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    width: 100
                    height: 50

                    text: tableView.model.headerData(model.index, Qt.Horizontal, 0)
                    font.bold: true
                    background: Rectangle {color: "#bbbbbb"; border.width: 1}
                }
            }
        }

        TableView {
            id: tableView

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: internal.leftMargin

            clip: true

            model: DivisionController.model()

            flickableDirection: Flickable.VerticalFlick

            ScrollBar.vertical: ScrollBar {
                active: true
                policy: ScrollBar.AlwaysOn
            }

            delegate: Rectangle {
                implicitHeight: 100
                implicitWidth: 100

                border.width: 1

                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: model.display
                }
            }
        }
    }
}
