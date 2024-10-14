import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window
{
    width: 800
    height: 500
    visible: true
    title: qsTr("LightControl")
    Rectangle
    {
        anchors.fill: parent
        color: "#61a4fb"
        RowLayout
        {
            anchors.fill: parent
            ColumnLayout
            {
                Layout.alignment: Qt.AlignHCenter
                spacing: 10
                Button
                {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 40
                    background: Rectangle
                    {
                        anchors.fill: parent
                        color: "#b1f4ff"
                        border.color: "#b1f4ff"
                        radius: 10
                        Text
                        {
                            anchors.centerIn: parent
                            text: "Creator"
                            color: "#000000"
                            font.family: "Arial"
                            font.pixelSize: 18
                            font.bold: true
                        }
                    }
                }
                ComboBox
                {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 40
                    font.family: "Arial"
                    font.pixelSize: 18
                    font.bold: true
                    background: Rectangle
                    {
                        anchors.fill: parent
                        color: "#1b5eb5"
                        border.color: "#1b5eb5"
                        radius: 10
                    }
                    model:[]
                }
            }
            ColumnLayout
            {
                Layout.alignment: Qt.AlignHCenter
                spacing: 10
                Button
                {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 40
                    background: Rectangle
                    {
                        anchors.fill: parent
                        color: "#b1f4ff"
                        border.color: "#b1f4ff"
                        radius: 10

                        Text
                        {
                            anchors.centerIn: parent
                            text: "Color"
                            color: "#000000"
                            font.family: "Arial"
                            font.pixelSize: 18
                            font.bold: true;
                        }
                    }
                }
                Slider
                {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 40
                    from: 0
                    to: 255
                    value: 0
                }
            }
        }
    }
}
