import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Popup {
    id: root

    property alias username: username.text
    property alias password: password.text

    signal loginClicked();

    x: Math.round((parent.width - root.width) / 2)
    y: Math.round((parent.height - root.height) / 2)

    modal: true

    contentItem: Item {
        ColumnLayout {
            anchors.fill: parent

            TextField {
                id: username

                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.fillWidth: true

                placeholderText: "Username"
            }

            TextField {
                id: password

                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.fillWidth: true

                placeholderText: "Password"
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.fillWidth: true

                text: "Login"

                onClicked: root.loginClicked();
            }
        }
    }
}
