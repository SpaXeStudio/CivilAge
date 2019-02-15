import QtQuick 2.0
import QtQuick.Controls 2.4
import QtMultimedia 5.8

import CivilAge.MainMenuWindow 1.0

MainMenuWindow {
    id: container

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    Image {
        anchors.fill: parent
        opacity: 0.5
        source: "qrc:/images/Diagram.png"
    }

    Column {
        anchors.leftMargin: 20
        anchors.topMargin: 80
        anchors.top: parent.top
        anchors.left: parent.left

        spacing: 10

        MainMenuButton {
            text: qsTr("New Game")
            onClicked: {
                toast.open("TODO: new game")
            }
        }

        MainMenuButton {
            text: qsTr("Load Game")
            onClicked: {
                toast.open("TODO: load game")
            }
        }

        MainMenuButton {
            text: qsTr("Multiplayer / test long toast")
            onClicked: {
                toast.open("TODO: multiplayer aaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaa hi")
                //toast.open("Clicked multiplayer")
            }
        }

        MainMenuButton {
            text: qsTr("About")
            onClicked: {
                toast.open("TODO: about page")
            }
        }

        MainMenuButton {
            text: qsTr("Quit Game")
            onClicked: Qt.quit()
        }
    }

    Slider {
        id: slider
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        onValueChanged: musicController.setVolume(value * 100)

        Component.onCompleted: {
            slider.value = musicController.volume / 100 // avoid binding loop
        }
    }

    MainMenuButton {
        text: qsTr("Press to skip (volume: %1%)\nPlaying: %2").arg((slider.value * 100).toFixed(0)).arg(musicController.currentSong)
        fontSize: 12
        anchors.bottom: slider.top
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            musicController.skip()
        }
    }

    Toast {
        id: toast
    }

    Connections {
        target: musicController
        onCurrentSongChanged: {
            toast.open("Playing: " + musicController.currentSong)
        }
    }
}
