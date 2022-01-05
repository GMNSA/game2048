import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5

import Game2048.Tile 1.0
import Game2048.Board 1.0

import Game2048.BoardScore 1.0


ApplicationWindow {
    id: _root
    width: 400
    height: 600
    visible: true

    maximumHeight: 600
    minimumHeight: 600
    maximumWidth: 400
    minimumWidth: 400

    property int num: 488


    Rectangle {
        id: _image

        height: _wrapperBoards.alScore.height * 0.8 - 2
        width: height

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 5
        anchors.topMargin: 5

        border.color: Qt.lighter(color)
        border.width: 1

        color: "#ECC400"

        Image {
            id: _img
            anchors.fill: parent

            source: "qrc:/2048.jpg"
        }
    }


    Row {
        id: _wrapperBoards
        spacing: 10
        padding: 5

        anchors.right: parent.right

        layoutDirection: Qt.LeftToRight

        property int fwidth: 120
        property int fheight: 100
        readonly property alias alScore: _score

        BoardScore {
            id: _score

            width: _wrapperBoards.fwidth
            height: _wrapperBoards.fheight

            btnName: "MENU"

        }

        BoardScore {
            id: _bestScore

            width: _wrapperBoards.fwidth
            height: _wrapperBoards.fheight

            btnName: "LEADERBOARD"
            nameScore: "BEST SCORE"
        }
    }

    Board {
        id: _board

        height: parent.height * 0.7

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        anchors.bottomMargin: parent.height * 0.1

    }

    Component.onCompleted: {
    }

    // to do board
}
