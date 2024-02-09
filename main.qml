import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import AuthController 1.0

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Design Patterns")

    ColumnLayout {
        anchors.fill: parent

        TopBar {
            id: topbar

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 30
            Layout.minimumHeight: 30

            Component.onCompleted: console.log(height)

            Connections {
                target: AuthController

                function onDataChanged(username, password) {
                    topbar.loggedIn = true;
                    topbar.username = username;
                    topbar.password = password;
                }

                function onLoggedOut() {
                    topbar.loggedIn = false;
                    topbar.username = "";
                    topbar.password = "";
                }
            }

            onLoginClicked: {
                AuthController.login("user", "user"); //! TODO placeholder
            }

            onLogoutClicked: {
                AuthController.logout();
            }
        }

        TabBar {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TabButton {
                text: "FTP file downloader"

                onClicked: main.currentIndex = 0;
            }
        }

        MainPage {
            id: main

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
