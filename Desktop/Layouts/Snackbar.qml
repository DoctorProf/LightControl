import QtQuick 2.15

Rectangle
{
    id: snackbar
    width: parent.width / 2.5
    height: 30
    radius: 20
    color: "white"
    opacity: 1
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottomMargin: 30
    visible: false
    z: 10

    Text
    {
        id: messageText
        anchors.centerIn: parent
        color: "black"
        font.family: "Arial"
        font.pixelSize: 14
        font.bold: true
    }

    Behavior on opacity
    {
        NumberAnimation { duration: 250 }
    }

    Behavior on visible
    {
        NumberAnimation { duration: 250 }
    }

    Timer
    {
        id: timer
        interval: 2000
        running: false
        repeat: false
        onTriggered:
        {
            snackbar.visible = false
            snackbar.opacity = 0
        }
    }

    function show(message)
    {
        messageText.text = message
        snackbar.visible = true
        snackbar.opacity = 1
        timer.start()
    }
}

