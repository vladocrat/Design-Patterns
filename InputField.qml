import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property alias text: textField.text

    RowLayout {
        anchors.fill: parent

        Text {
            text: "Your FTP URI:"
        }

        TextField {
            id: textField

            Layout.fillHeight: true
            Layout.fillWidth: true

            placeholderText: "ftp://localhost:8082/"

            validator: RegExpValidator {
                regExp: /^ftp:\/\/(localhost|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(:(\d{1,5}))?(\/[^\s]*)?$/
            }
        }
    }
}
