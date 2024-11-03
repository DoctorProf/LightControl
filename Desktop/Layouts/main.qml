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

    Snackbar {
        id: snackbar
    }

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
            onClicked: {
                request_handler.getModes();
                request_handler.getSettings()
            }
        }

        ComboBox {
            id: modes_box
            objectName: "modes_box"
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
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
                request_handler.setSettings("mode_id", obj.value.id)
                if("color" in obj.value.options) {
                    color_picker_button.visible = true
                }
            }

        }
        Slider{
            id: brightness_slider
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Material.accent: "#1b5eb5"
            to: 255
            from: 0
            value: 0
            onValueChanged: {
                var brightness = value.toFixed().toString();
                brightness_value.text = brightness
                request_handler.setSettings("brightness", brightness)
            }
        }
        Label {
            id: brightness_value
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
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
            Material.background: "#b1f4ff"
            Material.accent: "#1b5eff"
            text: "State"
            font.family: "Arial"
            font.pixelSize: 18
            font.bold: true
            checkable: true
            onClicked: {
                request_handler.setSettings("state", +checked)
            }
        }
        Button {
            id: delete_button
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Material.background: "#b1f4ff"
            Material.accent: "#1b5eff"
            text: "Delete"
            font.family: "Arial"
            font.pixelSize: 18
            font.bold: true
            onClicked: {
                request_handler.deleteMode();
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
            Material.primary: Material.Dark
            onAccepted: {
                var hex = selectedColor.toString(16).slice(1);
                request_handler.setModeParameter("color", hex)
            }
            onRejected: {

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
        function onSettingsReceived(obj) {
            brightness_slider.value = obj.brightness
            state_button.checked = obj.state
            modes_box.currentIndex = obj.mode_id
        }
        function onResponseMessage(message) {
            snackbar.show(message)
        }
    }
}
