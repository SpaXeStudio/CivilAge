import QtQuick 2.12
import QtGraphicalEffects 1.12

MouseArea {
    id: container

    property real __initial_mouse_x: NaN
    property real __initial_mouse_y: NaN

    Rectangle {
        id: background
        color: "white"
        visible: false

        states: [
            State {
                name: "active"; when: container.pressed && !(isNaN(__initial_mouse_x) || isNaN(__initial_mouse_y))
                PropertyChanges {
                    target: background
                    x: (container.mouseX > __initial_mouse_x)? __initial_mouse_x: container.mouseX
                    y: (container.mouseY > __initial_mouse_y)? __initial_mouse_y: container.mouseY
                    width:
                        (container.mouseX > __initial_mouse_x)? container.mouseX - __initial_mouse_x: __initial_mouse_x - container.mouseX
                    height:
                        (container.mouseY > __initial_mouse_y)? container.mouseY - __initial_mouse_y: __initial_mouse_y - container.mouseY
                }
            }
        ]
    }

    Item {
        id: mask
        anchors.fill: background
        visible: false

        Rectangle {
            anchors.fill: parent
            anchors.margins: 1
        }
    }

    OpacityMask {
        anchors.fill: background
        source: background
        maskSource: mask
        invert: true
    }

    onReleased: {
        __initial_mouse_x = NaN
        __initial_mouse_y = NaN
    }

    onPressed: {
        __initial_mouse_x = mouse.x
        __initial_mouse_y = mouse.y
    }
}
