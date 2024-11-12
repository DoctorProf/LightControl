import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Dialogs

Page {
    id: main_page
    width: width_win
    height: height_win

    Component.onCompleted:
    {
        request_handler.getModes()
        request_handler.getSettings()
    }

    ColorDialog
    {
        id: color_dialog
        title: "Color"
        onAccepted:
        {
            var hex = selectedColor.toString(16);
            color_picker.color = hex
            request_handler.setModeParameter("color", hex.slice(1))
        }
        onRejected:
        {
        }
    }

    ColumnLayout
    {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width *  0.6
        spacing: 20

        RowLayout
        {
            id: modes_row
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 50
            Layout.topMargin: 20
            Layout.leftMargin: 20
            spacing: 10
            ComboBox
            {
                id: modes_box
                width: 150
                height: 40
                Layout.preferredWidth: width
                Layout.preferredHeight: height
                Material.accent: accent_color
                font.family: "Arial"
                font.pixelSize: 16
                font.bold: true
                model: ListModel
                {
                    id: modes_model
                }
                textRole: "text"
                valueRole: "value"
                onCurrentIndexChanged:
                {
                    var obj = modes_model.get(currentIndex)
                    request_handler.setSettings("mode_id", obj.value.id)
                    if("color" in obj.value.options)
                    {
                        color_picker.visible = true
                        color_picker.color = "#" + obj.value.options.color
                    }
                }
            }
            Rectangle
            {
                id: add_button
                color: background_color
                Material.accent: accent_color
                radius: 10
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30

                Text
                {
                    anchors.centerIn: parent
                    text: "+"
                    font.family: "Arial"
                    font.pixelSize: 18
                    font.bold: true
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        stack_view.push(Qt.resolvedUrl("qrc:/Layouts/CreatorPage.qml"))
                    }
                    onPressed:
                    {
                        add_button.color = accent_color
                    }
                    onReleased:
                    {
                        add_button.color = background_color
                    }
                }
            }
            Rectangle
            {
                id: delete_button
                color: background_color
                Material.accent: accent_color
                radius: 10
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30

                Text
                {
                    anchors.centerIn: parent
                    text: "-"
                    font.family: "Arial"
                    font.pixelSize: 18
                    font.bold: true
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        request_handler.deleteMode();
                    }
                    onPressed:
                    {
                        delete_button.color = accent_color
                    }
                    onReleased:
                    {
                        delete_button.color = background_color
                    }
                }
            }
            Rectangle
            {
                id: color_picker
                color: background_color
                Material.accent: accent_color
                radius: 10
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30
                visible: false

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        color_dialog.open()
                    }
                    onPressed:
                    {
                        color_picker.color = accent_color
                    }
                    onReleased:
                    {
                        color_picker.color = background_color
                    }
                }
            }
            Item {Layout.fillWidth: true}
        }
        RowLayout
        {
            id: brightness_row
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 50
            Layout.leftMargin: 20

            Slider
            {
                id: brightness_slider
                Layout.preferredWidth: 200
                Layout.preferredHeight: 40
                Material.accent: accent_color
                to: 255
                from: 0
                value: 0
                onValueChanged:
                {
                    var brightness = value.toFixed().toString();
                    brightness_value.text = brightness
                    request_handler.setSettings("brightness", brightness)
                }
            }
            Label
            {
                id: brightness_value
                Layout.rightMargin: 100
                font.family: "Arial"
                font.pixelSize: 16
                font.bold: true
                text : brightness_slider.value
            }
        }
        RowLayout
        {
            id: switch_row
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 50
            Layout.leftMargin: 20

            Switch
            {
               id: state_switch
               Layout.preferredWidth: 150
               Layout.preferredHeight: 40
               Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
               Material.background: background_color
               Material.accent: accent_color
               text: "off"
               font.family: "Arial"
               font.pixelSize: 16
               font.bold: true
               onCheckedChanged:
               {
                   request_handler.setSettings("state", +checked)
                   if(checked) text = "on"
                   else text = "off"
               }
           }
        }
        Item {Layout.fillHeight: true }
    }

    ColumnLayout
    {
        id: column_layout
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width * 0.4
    }

    Connections
    {
        target: request_handler
        function onModesReceived(modes)
        {
            modes_model.clear()
            for (var i = 0; i < modes.length; i++)
            {
                modes_model.append({
                                       "text": modes[i].name,
                                       "value": modes[i]
                                   })
            }
        }
        function onSettingsReceived(obj)
        {
            brightness_slider.value = obj.brightness
            state_switch.checked = obj.state
            modes_box.currentIndex = obj.mode_id
        }
        function onResponseMessage(message)
        {
            snackbar.show(message)
        }
    }
}
