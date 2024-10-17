import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Dialogs

Window {
    width: 600
    height: 300

    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    visible: true
    title: qsTr("LightControl")
    Material.theme: Material.Light

    ColumnLayout {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2

        Button {
            objectName: "creator_button"
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.margins: 10
            Material.background: "#b1f4ff"
            text: "Creator"
            font.family: "Arial"
            font.pixelSize: 18
            font.bold: true
        }

        ComboBox {
            id: modes_box
            objectName: "modes_box"
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.topMargin: 30
            Layout.preferredWidth: 150
            Layout.preferredHeight: 40
            Material.accent: "#1b5eb5"
            font.family: "Arial"
            font.pixelSize: 18
            font.bold: true
            model: ListModel {
                id: modes_model
            }
            textRole: "text"
            valueRole: "value"
            onCurrentIndexChanged: {
                var obj = modes_model.get(currentIndex)
                request_handler.selectMode(obj.value.id)
                if("color" in obj.value.options) {
                    color_picker_button.visible = true
                }
            }

        }
        Slider{
            id: brightness_slider
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.bottomMargin: 0
            Material.accent: "#1b5eb5"
            to: 255
            from: 0
            value: 0
            onValueChanged: {
                var brightness = value.toFixed().toString();
                brightness_value.text = brightness
                request_handler.setBrightness(brightness)
            }
        }
        Label {
            id: brightness_value
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.bottomMargin: 20
            font.family: "Arial"
            font.pixelSize: 12
            font.bold: true
            text : brightness_slider.value
        }
        Button {
            id: state_button
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.bottomMargin: 50
            Material.background: "#b1f4ff"
            Material.accent: "#1b5eff"
            text: "State"
            font.family: "Arial"
            font.pixelSize: 18
            font.bold: true
            checkable: true
            onClicked: {
                request_handler.setState(+checked)
            }
        }
    }

    ColumnLayout {
        id: column_layout
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2
        Button {
            id: color_picker_button
            Layout.preferredWidth: 150
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.topMargin: 10
            Material.background: "#b1f4ff"
            Material.accent: "#1b5eff"
            text: "ColorPicker"
            font.family: "Arial"
            font.pixelSize: 18
            font.bold: true
            onClicked: {
                color_dialog.open()
            }
        }

        ColorDialog {
            id: color_dialog
            title: "Color"
            onAccepted: {
                var r = (selectedColor.r * 255).toFixed().toString()
                var g = (selectedColor.g * 255).toFixed().toString()
                var b = (selectedColor.b * 255).toFixed().toString()
                request_handler.setModeColor(r, g, b)
            }
            onRejected: {
                console.log("Color dialog rejected")
            }
        }
    }

    Connections {
        target: request_handler

        function onModesReceived(modes)
        {
            modes_model.clear()
            for (var i = 0; i < modes.length; i++) {
                console.log(modes[i].name, modes[i].id);
                modes_model.append({
                                       "text": modes[i].name,
                                       "value": modes[i]
                                   })
            }
        }
        function onModeSelected(success) {
            if (success) {
                console.log("Mode selected successfully.")
            } else {
                console.log("Failed to select mode.")
            }
        }
        function onInfoReceived(obj) {
            brightness_slider.value = obj.brightness
            state_button.checked = obj.state
            modes_box.currentIndex = obj.mode_id
        }
    }
}
