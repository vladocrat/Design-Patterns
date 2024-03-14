import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property int codeTxt
    property string nameTxt
    property string jobNameTxt
    property double jobPaymentTxt

    RowLayout {
        anchors.fill: parent

        spacing: 0

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text {
            text: root.codeTxt
            Layout.preferredWidth: root / 4
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text {
            text: root.nameTxt
            Layout.preferredWidth: root / 4
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text {
            text: root.jobNameTxt
            Layout.preferredWidth: root / 4
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text {
            text: root.jobPaymentTxt
            Layout.preferredWidth: root / 4
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

