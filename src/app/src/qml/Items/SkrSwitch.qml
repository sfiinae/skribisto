import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import ".."

Switch {
    id: control

    Material.background: SkrTheme.buttonBackground
    Material.foreground: SkrTheme.buttonForeground
    Material.accent: SkrTheme.accent



    SkrFocusIndicator {
        parent: control
        anchors.fill: control
        visible: control.activeFocus & Globals.focusVisible

    }
    Keys.onPressed: function(event) {
        if (event.key === Qt.Key_Tab){
            Globals.setFocusTemporarilyVisible()
        }
        if (event.key === Qt.Key_Backtab) {
            Globals.setFocusTemporarilyVisible()
        }
    }


    property string tip
    hoverEnabled: true

    SkrToolTip {
        text: control.tip ? control.tip : control.text
        visible: control.hovered && text.length !== 0
    }
}
