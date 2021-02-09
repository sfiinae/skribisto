import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import ".."

SkrTabButtonForm {
    id: control
    Material.background: SkrTheme.buttonBackground
    Material.foreground: SkrTheme.buttonForeground
    Material.accent: SkrTheme.accent

    Rectangle {
        parent: control.background
        anchors.fill: control.background
        color: "transparent"
        border.color: SkrTheme.accent
        border.width: control.activeFocus ? 1 : 0
        radius: 4

    }

    property string tip
    hoverEnabled: true

    SkrToolTip {
        text: control.tip ? control.tip : control.text
        visible: control.hovered && text.length !== 0
    }


    property string pageType : "undefined"
    property int projectId : -2
    property int paperId : -2
    readonly property string tabId: {return pageType + "_" +  projectId + "_" + paperId }

    function setTitle(newTitle) {

        control.text = newTitle
    }

    Accessible.name: control.text === "" ? action.text : control.text


    signal onCloseCalled(int index)
    closeButton.onClicked:  onCloseCalled(TabBar.index)



    readonly property bool isCurrent:  {
        if (TabBar.tabBar !== null) {
            return TabBar.index === TabBar.tabBar.currentIndex
        }
        return false
    }


    property bool textVisible: true
    onTextVisibleChanged: {
        tabLabel.visible = textVisible
    }


}
