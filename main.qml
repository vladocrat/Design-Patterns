import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Design Patterns")

    ColumnLayout {
        anchors.fill: parent

        TopBar {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: 30
            Layout.minimumHeight: 30

            Component.onCompleted: console.log(height)
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
