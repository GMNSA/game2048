import QtQuick 2.9

import Game2048.Button 1.0
import Game2048.Score 1.0

Item {
	id: _root

    property string btnName: "button"
    property string nameScore:"score"
    property string score: "0000"
    property int smallMargins: 2

    property int boardWidth: parent.height * 0.8

    Score {
        id: _score

        anchors.top: parent.top
        anchors.bottom: _btn.top
        anchors.bottomMargin: smallMargins

        height: boardWidth
        width: parent.width

        textName: nameScore
        textScore: score
    }

    Button {
        id: _btn

        anchors.bottom: parent.bottom

        height: 20
        width: parent.width

        text: btnName
    }
}
