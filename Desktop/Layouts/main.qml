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
    Material.theme: Material.Light

    property string background_color : "#b1f4ff"
    property string accent_color : "#1b5eb5"

    StackView {
        id: stack_view
        anchors.fill: parent
        initialItem: main_page
    }

    Snackbar {
        id: snackbar
    }

    Component {
        id: main_page
        MainPage {
            id: main_page_component
        }
    }
}
