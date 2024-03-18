import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import DivisionModel 1.0


Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        DivisionsControlButtons {
           Layout.alignment: Qt.AlignCenter
           Layout.preferredHeight: 50
           Layout.fillWidth: true
        }

        Timetable {
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

