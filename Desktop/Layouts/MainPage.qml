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

    Component.onCompleted:
    {
        request_handler.getModes()
        request_handler.getSettings()
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
                    request_handler.setSettings("mode_name", obj.value)
                }
            }
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
            modes_model.clear();
            for (var i = 0; i < modes["modes"].length; ++i) {
                modes_model.append({
                    "text": modes["modes"][i],
                    "value": modes["modes"][i]
                });
            }
            modesLoaded = true;
        }

        function onSettingsReceived(obj)
        {
            brightness_slider.value = obj.brightness;
            state_switch.checked = obj.state;
            settingsLoaded = true;
            applySettingsIfReady(obj);
        }

        function applySettingsIfReady(obj)
        {
            if (modesLoaded && settingsLoaded) {
                modes_box.currentIndex = getIndex(obj.mode_name);
            }
        }
        function onResponseMessage(message)
        {
            snackbar.show(message)
        }
        function getIndex(value)
        {
            for (var i = 0; i < modes_model.count; ++i) {
                var item = modes_model.get(i);

                if (value === item.value) {
                    return i;
                }
            }
            return 0;
        }
    }
}
