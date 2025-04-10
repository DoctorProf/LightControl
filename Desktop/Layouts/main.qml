import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Window
{
    property int width_win: 400
    property int height_win: 600
    width: width_win
    height: height_win

    maximumHeight: height_win
    maximumWidth: width_win
    minimumHeight: height_win
    minimumWidth: width_win
    visible: true
    title: qsTr("LightControl")
    Material.theme: Material.Dark
    Material.primary: "#1766db"

    StackView
    {
        id: stack_view
        anchors.fill: parent
        initialItem: main_page
    }

    Snackbar
    {
        id: snackbar
    }

    Component
    {
        id: main_page
        MainPage
        {
            id: main_page_component
        }
    }
}
