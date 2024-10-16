import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Window {
    width: 600
    height: 300

    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    visible: true
    title: qsTr("LightControl")

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
                id: modesModel
            }
            onCurrentIndexChanged: {
                request_handler.selectMode(modes_box.currentIndex);
            }
            textRole: "text"
            valueRole: "value"
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
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2
    }

    Connections {
        target: request_handler

        function onModesReceived(modes)
        {
            modesModel.clear()
            for (var i = 0; i < modes.length; i++) {
                console.log(modes[i].name, modes[i].id);
                modesModel.append({
                    "text": modes[i].name,
                    "value": modes[i].id
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
