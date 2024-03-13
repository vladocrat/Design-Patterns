import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property alias currentIndex: stack.currentIndex

    StackLayout {
        id: stack

        anchors.fill: parent

        FileDownloader {
           Layout.fillHeight: true
           Layout.fillWidth: true
        }

        IndustryStructure {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Editor {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
