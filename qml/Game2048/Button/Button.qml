import QtQuick 2.9

Item {
	id: _root

    signal clicked;
    property string text: "text"
    property real animationToPresseed: 300
    property real animationFromPressed: 200

    width: 100
    height: 30

    Rectangle {
        id: _btn

        anchors.fill: parent
        // border.color: Qt.lighter(color)
        opacity: 1
        radius: 2

        color: "#ED995B"

        Text {
            id: _text

            anchors.centerIn: parent

            font.pixelSize: sizeText();
            color: "white"

            text: _root.text
        }
    }

    function sizeText() {
        return (Math.min(_btn.height, _btn.width) / 2);
    }

    MouseArea {
        id: _mouseArea
        anchors.fill: parent

        onClicked:  {
            _root.clicked()
        }
    }

    states: State {
        name: "op"
        when: _mouseArea.pressed

        PropertyChanges {
            target: _btn
            opacity: 0.5
            // color: "blue"
        }
    }

    transitions: [
        Transition {
            to: "op"
            OpacityAnimator { duration: _root.animationToPresseed }
            // ColorAnimation { duration: _root.animationToPresseed }
        },
        Transition {
            from: "op"
            OpacityAnimator { duration: _root.animationToPresseed; to: 1 }
            // ColorAnimation { duration: _root.animationToPresseed }
        }
    ]
}
