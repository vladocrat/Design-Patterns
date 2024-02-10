import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    TextField {
        anchors.fill: parent

        placeholderText: "Your FTP URI"

        validator: RegExpValidator {
            regExp: /^ftp:\/\/(localhost|\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})(:(\d{1,5}))?(\/[^\s]*)?$/
        }
    }
}
