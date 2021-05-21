import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../Items"
import "../Commons"
import ".."

Item {

    property alias userManualToolButton: userManualToolButton
    property alias faqToolButton: faqToolButton

    ColumnLayout{

        anchors.fill: parent
        anchors.topMargin: 10
        spacing: 5

        SkrButton {
            id: userManualToolButton
            text: qsTr("User manual")

            icon.height: 90
            icon.width: 90

            Layout.minimumHeight: 100
            Layout.minimumWidth: 200
            Layout.fillWidth: true
            Layout.maximumWidth: 500
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        }



        SkrButton {
            id: faqToolButton
            text: qsTr("Frequently Asked Questions")

            icon.height: 90
            icon.width: 90

            Layout.minimumHeight: 100
            Layout.minimumWidth: 200
            Layout.fillWidth: true
            Layout.maximumWidth: 500
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        }

        Item {
            id: stretcher
            Layout.fillWidth: true
            Layout.fillHeight: true

        }
    }
}
