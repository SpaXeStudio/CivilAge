import QtQuick 2.0
import QtQuick.Controls 2.0

ApplicationWindow {
    id: root

    visible: true
    width: 640
    height: 480

    flags: Qt.Window || Qt.FramelessWindowHint

    Component {
        id: menuWindow
        MainMenuWindowForm {  }
    }

    Component {
        id: gameWindow
        GameWindowForm {  }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: menuWindow
    }

    Rectangle {
        id: topBar
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.margins: 10
        color: "blue"
        height: 40

        TextArea {
            id: screenName
            anchors.centerIn: parent
            text: "screen " + stack.currentItem
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (stack.depth === 1) {
                    stack.push(gameWindow)
                } else {
                    stack.pop()
                }
            }
        }
    }

    Toast {
        id: toast
    }

    // android specific
    property bool __close_timer_triggered: false
    property int __close_delay: 2000

    Timer {
        id: closeTimer
        interval: __close_delay
        onTriggered: __close_timer_triggered = false
    }
    // android specific

    onClosing: {
        if (Qt.platform.os === "android") {
            if (stack.depth > 1) {
                stack.pop()
                close.accepted = false
                return
            }

            if (__close_timer_triggered) {
                return
            } else {
                close.accepted = false

                toast.open(qsTr("Press back again to quit"), __close_delay)
                __close_timer_triggered = true
                closeTimer.restart()
            }
        } else {
            // TODO: leave dialog
        }
    }

    Component.onCompleted: {
        //root.showFullScreen()
    }
}
