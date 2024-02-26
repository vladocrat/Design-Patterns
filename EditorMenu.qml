import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import FigureType 1.0
import FigureController 1.0

Item {
    id: root

    property alias chosenType: buttonGroup.chosenIx

    ButtonGroup {
        id: buttonGroup

        property int chosenIx: FigureType.None

        onClicked: {
            chosenIx = button.type;
        }
    }

    ColumnLayout {
        anchors.fill: parent

        spacing: 1

        RowLayout {
            Layout.fillWidth: true
            Layout.maximumHeight: 60
            Layout.minimumHeight: 60
            implicitHeight: 30

            spacing: 0

            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true

                text: "<-"

                onClicked: {
                    FigureController.undo();
                }
            }

            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true

                text: "->"

                onClicked: {
                    FigureController.redo();
                }
            }
        }

        EditorMenuButton {
            Layout.fillWidth: true

            ButtonGroup.group: buttonGroup

            source: "qrc:/static/rectangle.svg"
            caption: "rectangle"
            type: FigureType.Rectangle
        }

        EditorMenuButton {
            Layout.fillWidth: true

            ButtonGroup.group: buttonGroup

            source: "qrc:/static/circle.svg"
            caption: "circle"
            type: FigureType.Circle
        }

        EditorMenuButton {
            Layout.fillWidth: true

            ButtonGroup.group: buttonGroup

            source: "qrc:/static/triangle.svg"
            caption: "triangle"
            type: FigureType.Triangle
        }

        EditorMenuButton {
            Layout.fillWidth: true

            ButtonGroup.group: buttonGroup

            source: "qrc:/static/pencil.svg"
            caption: "edit"
            type: FigureType.None
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
