import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import ".."

RoundButton {
    id: control
    icon.color: control.activeFocus ? SkrTheme.accent : control.action === null ? (enabled ? SkrTheme.buttonIcon : SkrTheme.buttonIconDisabled) :
                                          (control.action.icon.color === "transparent" ?
                                               (enabled ? control.action.icon.color: SkrTheme.buttonIconDisabled) :
                                               (enabled ? SkrTheme.buttonIcon : SkrTheme.buttonIconDisabled))

    Material.background: SkrTheme.buttonBackground
    Material.foreground: SkrTheme.buttonForeground
    Material.accent: SkrTheme.accent


    property string tip
    hoverEnabled: true

    SkrToolTip {
        text: control.tip ? control.tip : control.text
        visible: control.hovered && text.length !== 0
    }

}
