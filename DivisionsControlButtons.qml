import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import DivisionController 1.0

RowLayout {

    Button {
        Layout.preferredHeight: 40
        Layout.preferredWidth: 80

        text: "- job";

        onClicked:{}
    }

    Button {
        Layout.preferredHeight: 40
        Layout.preferredWidth: 80

        text: "+ job";

        onClicked: {}
    }

    TextField {
        id: divisionCodeSearch

        placeholderText: "Division code"
        validator: IntValidator{}

        Keys.onReturnPressed: DivisionController.getDivision(divisionCodeSearch.text);
    }

    Button {
        Layout.preferredHeight: 40
        Layout.preferredWidth: 80

        text: "+ subdivision";

        onClicked: DivisionController.add();
    }

    Button {
        Layout.preferredHeight: 40
        Layout.preferredWidth: 80

        text: "- subdivision";

        onClicked: DivisionController.removeDivision(divisionCodeSearch.text);
    }
}

