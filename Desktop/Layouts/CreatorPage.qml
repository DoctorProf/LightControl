import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Dialogs

Page
{
    id: creator_page
    width: width_win
    height: height_win

    ColorDialog
    {
        id: color_dialog
        title: "Color"
        Material.primary: Material.Dark
        onAccepted:
        {
            var hex = selectedColor.toString(16).slice(1);
            color_hex.text = hex
        }
        onRejected:
        {
            static_box.checked = false
        }
    }
    ColumnLayout
    {
        id: column
        Button
        {
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.preferredWidth: 100
            Layout.preferredHeight: 40
            Layout.margins: 10
            Material.background: background_color
            text: "Back"
            font.family: "Arial"
            font.pixelSize: 16
            font.bold: true
            onClicked:
            {
                stack_view.push(Qt.resolvedUrl("qrc:/Layouts/MainPage.qml"))
            }
        }
        TextField
        {
            id: name_field
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Material.accent: accent_color
            Layout.alignment: Qt.AlignCenter
        }

        CheckBox
        {
            id: static_box
            text: "Static"
            Material.accent: accent_color
            Layout.alignment: Qt.AlignCenter
            onClicked:
            {
                staticMode()
            }
        }
        Label
        {
            id: color_hex
            Material.accent: "#1b5eb5"
            Layout.alignment: Qt.AlignCenter
        }
        Button
        {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.margins: 10
            Material.background: background_color
            text: "Save"
            font.family: "Arial"
            font.pixelSize: 16
            font.bold: true
            onClicked:
            {
                var mode =
                    {
                        "static" : static_box.checked,
                        "name" : name_field.text,
                        "options" :
                            {
                                "color" : color_hex.text
                            }
                    }
                request_handler.addMode(mode)

            }
        }
    }
    function staticMode()
    {
        if(static_box.checked)
        {
            color_dialog.open()
        }
    }
}
