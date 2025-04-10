import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: 300
    height: 300

    property color currentColor: Qt.hsva(hueValue, saturationValue, brightnessValue, 1)
    property real hueValue: 0.0
    property real saturationValue: 1.0
    property real brightnessValue: 1.0

    signal hueChanged(real hue)
    signal saturationChanged(real saturation)
    signal brightnessChanged(real brightness)

    Canvas {
        id: hueWheel
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            var centerX = width/2
            var centerY = height/2
            var radius = Math.min(centerX, centerY) - 15

            ctx.clearRect(0, 0, width, height)

            for(var i = 0; i < 360; i++) {
                ctx.beginPath()
                ctx.arc(centerX, centerY, radius,
                       (i - 90) * Math.PI/180,
                       (i - 89) * Math.PI/180)
                ctx.strokeStyle = Qt.hsla(i/360, 1, 0.5, 1)
                ctx.lineWidth = 20
                ctx.stroke()
            }
        }

        Rectangle {
            id: hueSelector
            width: 20
            height: 20
            radius: 10
            border.width: 2
            border.color: "white"
            color: "transparent"

            x: {
                var centerX = parent.width/2
                var radius = Math.min(centerX, parent.height/2) - 25
                return centerX + radius * Math.cos(root.hueValue * 2 * Math.PI - Math.PI/2) - width/2
            }
            y: {
                var centerY = parent.height/2
                var radius = Math.min(parent.width/2, centerY) - 25
                return centerY + radius * Math.sin(root.hueValue * 2 * Math.PI - Math.PI/2) - height/2
            }
        }

        MouseArea {
            anchors.fill: parent
            function updateHue(x, y) {
                var centerX = parent.width/2
                var centerY = parent.height/2
                var dx = x - centerX
                var dy = y - centerY
                var angle = (Math.atan2(dy, dx) + Math.PI*2.5) % (Math.PI*2)
                root.hueValue = angle/(Math.PI*2)
                root.hueChanged(root.hueValue)
            }
            onPositionChanged: (mouse) => updateHue(mouse.x, mouse.y)
            onClicked: (mouse) => updateHue(mouse.x, mouse.y)
        }
    }

    Rectangle {
        id: svSquare
        anchors.centerIn: parent
        width: parent.width * 0.6
        height: width
        radius: width/2
        color: "transparent"

        Rectangle {
            anchors.fill: parent
            anchors.margins: 10
            radius: width/2
            gradient: Gradient {
                GradientStop { position: 0.0; color: "white" }
                GradientStop { position: 1.0; color: Qt.hsla(root.hueValue, 1, 0.5, 1) }
            }

            Rectangle {
                anchors.fill: parent
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "transparent" }
                    GradientStop { position: 1.0; color: "black" }
                }
            }
        }

        Rectangle {
            id: svSelector
            width: 16
            height: 16
            radius: 8
            border.width: 2
            border.color: "white"
            color: "transparent"

            x: parent.width * root.saturationValue - width/2
            y: parent.height * (1 - root.brightnessValue) - height/2

            Rectangle {
                anchors.centerIn: parent
                width: 12
                height: 12
                radius: 6
                color: root.currentColor
            }
        }

        MouseArea {
            anchors.fill: parent
            function updateSV(x, y) {
                var center = parent.width/2
                var dx = x - center
                var dy = y - center
                var dist = Math.sqrt(dx*dx + dy*dy)

                if(dist > center) return

                root.saturationValue = Math.min(1, Math.max(0, (dx + center)/parent.width))
                root.brightnessValue = 1 - Math.min(1, Math.max(0, (dy + center)/parent.height))
                root.saturationChanged(root.saturationValue)
                root.brightnessChanged(root.brightnessValue)
            }
            onPositionChanged: (mouse) => updateSV(mouse.x, mouse.y)
            onClicked: (mouse) => updateSV(mouse.x, mouse.y)
        }
    }
}
