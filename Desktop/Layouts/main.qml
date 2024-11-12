import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Window
{
    property string background_color : "#e0bbe4"
    property string accent_color : "#4b0082"
    property int width_win: 600
    property int height_win: 300
    width: width_win
    height: height_win

    maximumHeight: height_win
    maximumWidth: width_win
    minimumHeight: height_win
    minimumWidth: width_win
    visible: true
    title: qsTr("LightControl")
    Material.theme: Material.Light



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
