import QtQuick 2.9

Item {
	id: _root

    property string textName: "score"
    property string textScore: "00"

    Rectangle {
        id: _board

        anchors.fill: parent

        color: "#BBADA0"
        border.width: 1
        border.color: Qt.lighter(color)


            Text {
                id: _name

                height: parent.height * 0.4
                width: parent.width

                anchors.top: parent.top

                text: textName
                font.pixelSize: Math.min(parent.height, parent.width) / 5
                font.bold: true

                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter

                color: "white"
            }



            Text {
                id: _score

                height: parent.height * 0.7
                width: parent.width

                anchors.bottom: parent.bottom

                text: textScore
                font.pixelSize: Math.min(parent.height, parent.width) / 3
                font.bold: true

                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter

                color: "white"
            }

    }
}
