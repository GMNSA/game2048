import QtQuick 2.9

import Game2048.Tile 1.0
import Game2048Model 1.0

Item {
    id: _root
    focus: true

    property int col: 4
    property int row: 4

    Grid {
        id: _grid

        columns: _root.col
        rows: _root.row

        width: parent.width < parent.height ? parent.width :
                                              parent.height
        height: width
        anchors.centerIn: parent

        Repeater {
            model: parent.columns * parent.rows

            Rectangle {
                width: _grid.width / _grid.rows
                height: _grid.height / _grid.columns

                color: "#bbada0"

                Rectangle {
                    color: "#ccc0b2"
                    radius: 3
                    anchors.fill: parent
                    anchors.margins: 5
                }
            }
        }
    }


        GridView {
            id: _gridView

            width: _grid.width
            height: _grid.height
            anchors.centerIn: parent
            interactive: false

            cellHeight: _grid.width / _grid.rows
            cellWidth: _grid.height/ _grid.columns

            move: Transition {
                NumberAnimation { properties: "x,y"; duration: 200 }
     }

            model: Game2048Model {
                id: _model
            }

            delegate: Item {
                id: _wrapper

                visible: display == 0 ? false : true

                width: _gridView.width / _root.row
                height: _gridView.height / _root.col

                Tile {
                    anchors.margins: 7
                    anchors.fill: parent

                    value: display
                }
            }
        }

        Flickable {
            id: _swipeArea

            width: _grid.width
            height: _grid.height

            anchors.centerIn: parent

            flickableDirection: Flickable.HorizontalAndVerticalFlick

            onFlickStarted: {
                if (horizontalVelocity < 0) {
                    print("right")
                } else if (horizontalVelocity > 0) {
                    print("left")
                } else if (verticalVelocity < 0) {
                    print("down")
                } else if (verticalVelocity > 0) {
                    print("up")
                }

                boundsMovement: Flickable.StopAtBounds
                pressDelay: 0
            }
        }

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Up:
                _model.moveUp()
                print("up")
                break;
            case Qt.Key_Down:
                _model.moveDown()
                print("down")
                break;
            case Qt.Key_Right:
                _model.moveRight()
                print("right")
                break;
            case Qt.Key_Left:
                _model.moveLeft()
                print("left")
                break;
            case Qt.Key_R:
                _model.reset()
                break;
            case Qt.Key_Space:
                print("add")
                _model.add();
                break;
            }
        }

        Component.onCompleted: {
            _model.init();
        }
}
