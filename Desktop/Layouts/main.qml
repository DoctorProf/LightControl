import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Window
{
    property int width_win: 700
    property int height_win: 500
    width: width_win
    height: height_win

    maximumHeight: height_win
    maximumWidth: width_win
    minimumHeight: height_win
    minimumWidth: width_win
    visible: true
    title: qsTr("LedControl")
    Material.theme: Material.Dark
    Material.primary: "#9c27b0"
    Material.accent: "#e91e63"

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
