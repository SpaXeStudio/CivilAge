import QtQuick 2.6

Item {
    id: container
    visible: false
    height: label.height
    width: parent.width - __horisontal_padding * 2

    anchors {
        bottom: parent.bottom
        horizontalCenter: parent.horizontalCenter
        bottomMargin: 50
    }

    property int __close_after: 1000
    property real __horisontal_padding: 10
    property real __vertical_padding: 5

    function open(text, close_after) {
        if (close_after !== undefined) {
            __close_after = close_after
        }

        label.text = text
        container.visible = true
        timer.restart()
    }

    Rectangle {
        id: background
        color: "black"
        opacity: 0.3
        radius: 10
        anchors.centerIn: parent
        height: label.height + __vertical_padding * 2
        width: Math.min(
                   label.contentWidth + __horisontal_padding * 2,
                   parent.width + __horisontal_padding * 2
               )
    }

    Text {
        id: label
        color: "white"
        opacity: 0.75
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: background
        width: parent.width
    }

    Timer {
        id: timer
        running: false
        interval: __close_after
        onTriggered: container.visible = false
    }
}
