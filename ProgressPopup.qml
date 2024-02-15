import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import DownloadController 1.0

Popup {
    id: root

    x: Math.round((parent.width - root.width) / 2)
    y: Math.round((parent.height - root.height) / 2)

    height: 100
    modal: true

    //Component.onCompleted: open();

    contentItem: Item {
        ColumnLayout {
            anchors.fill: parent

            Text {
                text: "Download progress"
            }

            ProgressBar {
                id: progressBar

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 20

                value: DownloadController.progress

                onValueChanged: console.log("value changed: ", value);
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width / 2

                text: "Ok"
                enabled: progressBar.value == 1.0

                onClicked: root.close();
            }
        }
    }
}
