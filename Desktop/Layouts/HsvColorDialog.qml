import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: root
    modal: true
    title: "Select Color"
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: parent

    property color selectedColor: Qt.hsva(hue, saturation, brightness, 1)
    property color initialColor: "white"

    property real hue: 0.0
    property real saturation: 1.0
    property real brightness: 1.0

    signal colorSelected(color selectedColor)

    onAccepted: colorSelected(selectedColor)
    onRejected: selectedColor = initialColor

    onVisibleChanged: if(visible) {
        hue = initialColor.hsvHue
        saturation = initialColor.hsvSaturation
        brightness = initialColor.hsvValue
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        ColorPicker {
            id: colorPicker
            width: 300
            height: 300
            hueValue: hue
            saturationValue: saturation
            brightnessValue: brightness

            onHueChanged: (hue) => root.hue = hue
            onSaturationChanged: (sat) => root.saturation = sat
            onBrightnessChanged: (val) => root.brightness = val
        }

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 60
            height: 30
            color: selectedColor
            border.color: "gray"
            radius: 4
        }
    }
}
