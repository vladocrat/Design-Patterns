import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import DivisionController 1.0

Item {
    id: root

    //property alias model: listView.model

    ColumnLayout {
        anchors.fill: parent

        TableView {
            id: listView

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter

            clip: true

            model: DivisionController.model()

            flickableDirection: Flickable.VerticalFlick

            ScrollBar.vertical: ScrollBar {
                active: true
                policy: ScrollBar.AlwaysOn
            }


            delegate: Rectangle {
                implicitHeight: 50
                implicitWidth: 100

                Text {
                    text: model.display
                }

            }
                /*TimetableDelegate {
                anchors {
                    leftMargin: 50
                    rightMargin: 50
                }

                width: parent.width
                height: 50

                codeTxt: model.code
                nameTxt: model.name
                jobNameTxt: model.jobName
                jobPaymentTxt: model.jobPayment
            }*/
        }
    }
}
