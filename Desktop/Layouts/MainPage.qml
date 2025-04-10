import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Dialogs

Page {
    id: main_page
    width: width_win
    height: height_win

    property bool modesLoaded: false
    property bool settingsLoaded: false
    property string mode_name : ""

    Component.onCompleted: {
        request_handler.getModes()
        request_handler.getSettings()
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 30

        // Mode Selection
        ComboBox {
            id: modes_box
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 300
            Layout.topMargin: 15
            font.pixelSize: 16
            font.bold: true
            Material.accent: Material.primary
            model: ListModel { id: modes_model }
            textRole: "text"
            valueRole: "value"

            // Кастомизация отображения текста
            delegate: ItemDelegate {
                width: modes_box.width
                contentItem: Text {
                    text: model.text
                    font: modes_box.font
                    color: Material.foreground
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                highlighted: modes_box.highlightedIndex === index
            }

            // Кастомизация выбранного значения
            contentItem: Text {
                text: modes_box.displayText
                font: modes_box.font
                color: Material.foreground
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }

            onCurrentIndexChanged: {
                var obj = modes_model.get(currentIndex)
                request_handler.setSettings("mode_name", obj.value)
            }
        }

        // Color Picker
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 40
            spacing: 25

            Button {
                id: color_button
                text: "PickColor"
                onClicked: color_dialog.open()
                Material.background: Material.primary
                Material.foreground: "white"
                font.pixelSize: 16
                padding: 15
            }

            Rectangle {
                id: color_preview
                width: 60
                height: 60
                radius: 8
                border.color: Qt.darker(color_preview.color, 1.4)
                border.width: 2
                onColorChanged: {
                    request_handler.setSettings("color", color_preview.color)
                }

                MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            request_handler.setSettings("color", color_preview.color)
                        }
                    }
            }

        }

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 30
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            spacing: 10

            Label {
                text: "Brightness: " + brightness_slider.value.toFixed()
                font.bold: true
                font.pixelSize: 18
                Layout.alignment: Qt.AlignHCenter
            }

            Slider {
                id: brightness_slider
                Layout.preferredWidth: 350
                from: 0
                to: 255
                Material.accent: Material.primary
                onValueChanged: request_handler.setSettings("brightness", value)
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 20
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            spacing: 10

            Label {
                text: "Speed: " + speed_slider.value.toFixed()
                font.bold: true
                font.pixelSize: 18
                Layout.alignment: Qt.AlignHCenter
            }

            Slider {
                id: speed_slider
                Layout.preferredWidth: 350
                from: 0
                to: 1
                Material.accent: Material.primary
                onValueChanged: request_handler.setSettings("speed", value)
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 30
            Layout.bottomMargin: 20
            spacing: 25

            Switch {
                id: state_switch
                width: 80
                height: 50
                Material.accent: Material.primary
                onCheckedChanged: {
                    request_handler.setSettings("state", +checked)
                }
            }

            Label {
                text: state_switch.checked ? "ON" : "OFF"
                font.bold: true
                font.pixelSize: 20
                color: state_switch.checked ? "#4CAF50" : "#F44336"
            }
        }

        Item { Layout.fillHeight: true }
    }

    // HsvColorDialog {
    //        id: color_dialog
    //        initialColor: color_preview.color
    //        onColorSelected: color_preview.color = selectedColor
    //    }

    ColorDialog {
        id: color_dialog
        title: "PickColor"
        options: Dialog.UsePlatformDialog ? 0 : ColorDialog.DontUseNativeDialog

        onAccepted: {
            color_preview.color = selectedColor.toString()
            request_handler.setSettings("color", selectedColor)
        }
    }

    Connections {
        target: request_handler

        function onModesReceived(modes) {
            modes_model.clear()
            modes["modes"].forEach(mode => modes_model.append({text: mode, value: mode}))
            modesLoaded = true
            applySettingsIfReady(mode_name)
        }

        function onSettingsReceived(obj) {
            if (obj.brightness !== undefined) brightness_slider.value = obj.brightness
            if (obj.state !== undefined) state_switch.checked = obj.state
            if (obj.speed !== undefined) speed_slider.value = obj.speed
            if (obj.color !== undefined) color_preview.color = obj.color
            if (obj.led_count !== undefined) speed_slider.to = obj.led_count
            if (obj.mode_name !== undefined) mode_name = obj.mode_name
            settingsLoaded = true
            applySettingsIfReady(mode_name)
        }

        function applySettingsIfReady(mode_name) {
            if (modesLoaded && settingsLoaded) {
                modes_box.currentIndex = getIndex(mode_name)
            }
        }

        function getIndex(value) {
            for (let i = 0; i < modes_model.count; ++i) {
                if (modes_model.get(i).value === value) return i
            }
            return 0
        }

        function onResponseMessage(message) {
            snackbar.show(message)
        }
    }
}
