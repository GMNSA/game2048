import QtQuick 2.9

import "qrc:/Color.js" as Color

Item {
    id: _root

    property string value: ""
    property real animationValue: 100
    property real animationMove: 400
    property bool isAnimationMove: false
    property bool isAnimationValue: false

    function sizeText(value) {
        if (value < 100)
            return Math.max(_root.width, _root.height) / 2;
        else if (value > 100 && value < 1000)
            return Math.max(_root.width, _root.height) / 3;
        else if (value > 1000 && value < 10000)
            return Math.max(_root.width, _root.height) / 4;
        else if (value > 10000 && value < 100000)
            return Math.max(_root.width, _root.height) / 5;
        else if (value > 100000 && value < 1000000)
            return Math.max(_root.width, _root.height) / 6;
        else if (value > 1000000 && value < 10000000)
            return Math.max(_root.width, _root.height) / 7;
    }

    signal clicked

    MouseArea {
        id: _mouse
        anchors.fill: parent

        onClicked: {
            _root.clicked()
        }
    }

    Rectangle {
        id: _tile

        anchors.fill: parent

        border.width: 1
        border.color: Qt.lighter(color)
        radius: 5

        color: Color.color(value)

        Text {
            id: _text
            anchors.centerIn: parent

            text: value
            color: "grey"

            font.pixelSize: sizeText(value)
            font.bold: true

            onTextChanged: {
                _anim.start()
            }
        }

        SequentialAnimation {
            id: _anim
            running: _root.isAnimationValue
            // NumberAnimation {
            //     target: _tile
            //     properties: "opacity,color"
            //     from: 1
            //     to: 0.2
            //     duration: _root.animationValue
            // }
            // NumberAnimation {
            //     target: _tile
            //     properties: "opacity,color"
            //     from: 0.2
            //     to: 1
            //     duration: _root.animationValue
            // }
            NumberAnimation {
                target: _tile
                properties: "scale"
                from: 1
                to: 0.2
                duration: _root.animationValue
            }
            NumberAnimation {
                target: _tile
                properties: "scale"
                from: 0.2
                to: 1
                duration: _root.animationValue
            }
        }
    }

    Behavior on x {
        enabled: isAnimationMove
        NumberAnimation {
            duration: _root.animationMove
        }
    }

    Behavior on y {
        enabled: isAnimationMove
        NumberAnimation {
            duration: _root.animationMove
        }
    }

    Behavior on width {
        enabled: true
        NumberAnimation {
            duration: _root.animationMove
        }
    }

    Behavior on height {
        enabled: true
        NumberAnimation {
            duration: _root.animationMove
        }
    }
}
