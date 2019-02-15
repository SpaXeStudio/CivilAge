import QtQuick 2.0

Item {
    id: container
    height: label.height + 20
    width: Math.max(height * 2, label.width + 50)

    property string text: "Button"
    property int fontSize: 17
    property double animationSpeed: 1

    signal clicked()

    Rectangle {
        id: shadow
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: parent.height - parent.height * 0.06
        width: parent.width - parent.height * 0.06
        opacity: 0.5
        color: "black"
        radius: container.height / 6
    }

    Rectangle {
        id: buttonTop
        radius: shadow.radius
        height: shadow.height
        width: shadow.width

        Behavior on color {
            ColorAnimation {  }
        }

        Text {
            id: label
            text: container.text
            font.pointSize: container.fontSize
            anchors.centerIn: parent
        }

        MouseArea {
            id: mouseArea
            property date heldFrom

            anchors.fill: parent
            onPressed: mouseArea.heldFrom = new Date()
            onReleased: {
                if (
                    mouseArea.containsMouse && new Date() - mouseArea.heldFrom > anchorAnimation.duration
                ) container.clicked()
            }
        }

        states: [
            State {
                name: "down"; when: mouseArea.pressed
                AnchorChanges {
                    target: buttonTop
                    anchors { bottom: container.bottom; right: container.right; top: undefined; left: undefined }
                }
                PropertyChanges {
                    target: buttonTop
                    color: "darkblue"
                }
            },
            // not necessary needed, but button can stuck in pressed state with broken color and anchors
            State {
                name: "up"; when: !mouseArea.pressed
                AnchorChanges {
                    target: buttonTop
                    anchors { bottom: undefined; right: undefined; top: container.top; left: container.left }
                }
                PropertyChanges {
                    target: buttonTop
                    color: "blue"
                }
            }
        ]

        transitions: Transition {
            AnchorAnimation { id: anchorAnimation; duration: 130; easing.type: Easing.OutQuad }
        }
    }
}
