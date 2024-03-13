import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import DivisionModel 1.0
import DivisionController 1.0

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        Button {
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: DivisionController.add();
        }

        TableView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: DivisionController.model()

            delegate: Rectangle {
                implicitHeight: 100
                implicitWidth: 200
            }

            // delegate: Rectangle {
            //     implicitHeight: 100
            //     implicitWidth: 200

            //     Text {
            //         text: model.code
            //     }

            //     Text {
            //         text: model.name
            //     }

            //     Text {
            //         text: model.jobName
            //     }

            //     Text {
            //         text: model.jobPayment
            //     }
            // }
        }
    }
}

