import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    id: root

    property bool loggedIn: false
    property string username: "username"
    property string password: "password"

    signal loginClicked();
    signal logoutClicked();

    RowLayout {
        anchors.fill: parent

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: root.loggedIn
        }

        Text {
            Layout.alignment: Qt.AlignRight

            text: root.username
            visible: root.loggedIn
        }

        Text {
            Layout.alignment: Qt.AlignRight

            text: root.password
            visible: root.loggedIn
        }

        Button {
            Layout.alignment: Qt.AlignRight
            Layout.fillHeight: true
            Layout.preferredWidth: 50

            text: "Logout"
            visible: root.loggedIn

            onClicked: root.logoutClicked();
        }

        Button {
            Layout.alignment: Qt.AlignRight
            Layout.fillHeight: true
            Layout.preferredWidth: 50

            text: "Login"
            visible: !root.loggedIn

            onClicked: root.loginClicked();
        }
    }
}
