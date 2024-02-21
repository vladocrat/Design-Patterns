import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import FigureType 1.0

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
