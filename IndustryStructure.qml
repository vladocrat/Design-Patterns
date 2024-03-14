import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import DivisionModel 1.0
import DivisionController 1.0

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        Timetable {
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            //model: DivisionController.model()
        }

        Button {
            Layout.fillHeight: true
            Layout.maximumHeight: parent.height / 5
            Layout.fillWidth: true

            onClicked: DivisionController.add();
        }
    }
}

