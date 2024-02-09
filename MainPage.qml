import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root

    property alias currentIndex: stack.currentIndex

    StackLayout {
        id: stack

        Item {
            // Content for the first tab
        }
        Item {
            // Content for the second tab
        }
    }
}
