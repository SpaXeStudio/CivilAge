import QtQuick 2.0
import CivilAge.GameWindow 1.0
import CivilAge.GameScreen 1.0

GameWindow {
    id: container

    GameScreen {
        SequentialAnimation on t {
            NumberAnimation { to: 1; duration: 500; easing.type: Easing.InQuad }
            NumberAnimation { to: 0; duration: 500; easing.type: Easing.OutQuad }
            loops: Animation.Infinite
            running: parent
        }
    }

    Rectangle {
        id: topMenus
        anchors.top: parent.top
        height: 60
        width: parent.width
        color: "green"
        visible: false
    }

    Rectangle {
        id: bottomMenus
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        height: 40
        color: "red"
    }

    Text {
        anchors.centerIn: parent
        text: bottomMenus.color
    }

    SelectorArea {
        anchors.fill: parent
    }
}
