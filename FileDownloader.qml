import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50
                text: "-"

                onClicked: {
                    if (layout.children.length >  0) {
                        layout.children[layout.children.length -  1].destroy();
                    }
                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50

                text: "+"

                onClicked: {
                    var component = Qt.createComponent("Rect.qml");
                    if (component.status === Component.Ready) {
                        var inputField = component.createObject(layout, {width: 20, height: 20});
                    } else {
                        console.error("Error loading component:", component.errorString());
                    }
                }
            }
        }

        ColumnLayout {
            id: layout

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

