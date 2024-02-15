import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

import DownloadController 1.0

Item {
    id: root

    QtObject {
        id: internal

        property string path: ""
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50

                text: "-"

                onClicked: {
                    if (layout.children.length >  0) {
                        layout.children[layout.children.length -  1].destroy();
                    }
                }
            }

            Button {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50

                text: "+"

                onClicked: {
                    var component = Qt.createComponent("InputField.qml");
                    if (component.status === Component.Ready) {
                        var inputField = component.createObject(layout, {
                                                                    "Layout.preferredHeight": 35,
                                                                    "Layout.fillWidth": true});
                    } else {
                        console.error("Error loading component:", component.errorString());
                    }
                }
            }

            TextField {
                id: threadNum

                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50

                validator: RegExpValidator {
                    regExp: /^[-+]?\d+$/
                }
            }
        }

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true

            ColumnLayout {
                id: layout

                anchors.fill: parent
                anchors.rightMargin: 50
                anchors.leftMargin: 50
                anchors.topMargin: 10
                anchors.bottomMargin: 10
            }
        }

        FileDialog {
            id: fileDialog

            selectFolder: true
            folder: shortcuts.home
            visible: false

            onAccepted: internal.path = fileDialog.folder;
        }

        Button {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 50
            Layout.preferredWidth: 150
            Layout.bottomMargin: 10

            text: "Choose path"

            onClicked: fileDialog.open();
        }

        ProgressPopup {
            id: progressScreen
        }

        Button {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 50
            Layout.preferredWidth: 150
            Layout.bottomMargin: 10

            text: "Download"

            onClicked: {
                var texts = [];
                for (var i =  0; i < layout.children.length; ++i) {
                    console.log(layout.children[i].text);
                    texts.push(layout.children[i].text);
                }

                progressScreen.open();
                DownloadController.download(texts, internal.path, threadNum.text);
            }
        }
    }
}

