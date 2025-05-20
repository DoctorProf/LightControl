import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Page {
    id: main_page
    width: width_win
    height: height_win

    property bool modes_loaded: false
    property bool settings_loaded: false
    property string mode_name: ""

    Timer {
        id: mode_params_delay
        interval: 200
        repeat: false
        onTriggered: request_handler.getModeParams()
    }

    Component.onCompleted: {
        request_handler.getModes()
        request_handler.getSettings()
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width / 2 - 30
            background: Rectangle {
                color: "#2c2c2e"
                radius: 12
            }

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                ComboBox {
                    id: modes_box
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 200
                    font.pixelSize: 16
                    font.bold: true
                    model: ListModel { id: modes_model }
                    textRole: "text"
                    valueRole: "value"
                    Material.accent: Material.accent

                    onCurrentIndexChanged: {
                        var obj = modes_model.get(currentIndex)
                        request_handler.setSettings("mode_name", obj.value)
                        mode_params_delay.restart()
                    }
                }

                Slider {
                    id: brightness_slider
                    Layout.preferredWidth: 250
                    from: 0
                    to: 100
                    Material.accent: Material.accent
                    onValueChanged: request_handler.setSettings("brightness", Math.ceil(value * 2.55))
                }

                Label {
                    text: brightness_slider.value.toFixed() + "%"
                    font.bold: true
                    font.pixelSize: 18
                    Layout.alignment: Qt.AlignHCenter
                }

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.topMargin: 20
                    spacing: 20

                    Switch {
                        id: state_switch
                        width: 80
                        height: 50
                        Material.accent: Material.accent
                        onCheckedChanged: request_handler.setSettings("state", +checked)
                    }

                    Label {
                        text: state_switch.checked ? "ON" : "OFF"
                        font.bold: true
                        font.pixelSize: 20
                        color: state_switch.checked ? "#BB86FC" : "#FF6E83"
                    }
                }
            }
        }

        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width / 2 - 30
            background: Rectangle {
                color: "#2c2c2e"
                radius: 12
            }

            ScrollView {
                anchors.fill: parent
                contentWidth: parent.width
                clip: true
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }

                ColumnLayout {
                    id: properties_container
                    width: parent.width
                    spacing: 15
                    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                }
            }
        }

    }

    Connections {
        target: request_handler

        function onModesReceived(modes) {
            modes_model.clear()
            modes["modes"].forEach(mode => modes_model.append({text: mode, value: mode}))
            modes_loaded = true
            apply_settings_if_ready(mode_name)
        }

        function onSettingsReceived(obj) {
            if (obj.brightness !== undefined) brightness_slider.value = obj.brightness / 2.55
            if (obj.state !== undefined) state_switch.checked = obj.state
            if (obj.mode_name !== undefined) mode_name = obj.mode_name
            settings_loaded = true
            apply_settings_if_ready(mode_name)
        }

        function apply_settings_if_ready(name) {
            if (modes_loaded && settings_loaded) {
                modes_box.currentIndex = get_index(name)
                mode_params_delay.restart()
            }
        }

        function get_index(value) {
            for (let i = 0; i < modes_model.count; ++i)
                if (modes_model.get(i).value === value) return i
            return 0
        }

        function onResponseMessage(message) {
            snackbar.show(message)
        }

        function onParamsModeReceived(params)
        {
            // Очистка старых элементов
            for (let i = properties_container.children.length - 1; i >= 0; --i) {
                const child = properties_container.children[i];
                if (child !== undefined && child !== null && child.destroy !== undefined) {
                    child.destroy();
                }
            }

            function escapeQmlString(str) {
                return str.replace(/\\/g, '\\\\').replace(/"/g, '\\"').replace(/\n/g, '\\n');
            }

            function create_float_slider(key, param) {
                let safeScreenName = escapeQmlString(param.screen_name);
                Qt.createQmlObject(`
                    import QtQuick 2.15
                    import QtQuick.Controls 2.15
                    import QtQuick.Layouts 1.15

                    ColumnLayout {
                        property string screenName: "${safeScreenName}"
                        spacing: 4
                        Layout.alignment: Qt.AlignHCenter

                        Label {
                            text: qsTr(screenName)
                            font.bold: true
                            font.pixelSize: 16
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                        }

                        Slider {
                            id: slider
                            from: ${param.min}
                            to: ${param.max}
                            stepSize: ${param.step}
                            value: ${param.value}
                            Layout.preferredWidth: 200
                            onValueChanged: request_handler.setModeParams("${key}", "value", value)
                        }

                        Label {
                            text: slider.value.toFixed(2)
                            font.pixelSize: 14
                            color: "lightgray"
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                `, properties_container, "dynamic_float_slider_" + key);
            }

            function create_color_picker(key, param) {
                let safeScreenName = escapeQmlString(param.screen_name);
                Qt.createQmlObject(`
                    import QtQuick 2.15
                    import QtQuick.Controls 2.15
                    import QtQuick.Layouts 1.15

                    ColumnLayout {
                        property string screenName: "${safeScreenName}"
                        spacing: 6
                        Layout.alignment: Qt.AlignHCenter

                        Label {
                            text: qsTr(screenName)
                            font.bold: true
                            font.pixelSize: 16
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                        }

                        Rectangle {
                            id: color_preview
                            width: 60
                            height: 30
                            color: "${param.value}"
                            radius: 6
                            border.color: Qt.darker(color, 1.3)
                            border.width: 2
                            Layout.alignment: Qt.AlignHCenter

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    const new_color = color_dialog_helper.getColor(color_preview.color)
                                    if (new_color && new_color !== color_preview.color) {
                                        color_preview.color = new_color
                                        request_handler.setModeParams("${key}", "value", new_color)
                                    }
                                }
                            }
                        }
                    }
                `, properties_container, "dynamic_color_picker_" + key);
            }

            // Создаём элементы
            for (let key in params) {
                const param = params[key];
                if (param.type === "float") {
                    create_float_slider(key, param);
                } else if (param.type === "color") {
                    create_color_picker(key, param);
                }
            }
        }
    }
}
