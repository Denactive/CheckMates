import QtQuick 2.0
import Chess 1.0

GridView {
    id: root
    model: ChessBoardModel {
    }

//    interactive: false;
//    model: ChessBoardModel {

//    }

    cellHeight: height / root.model.size
    cellWidth: width / root.model.size

    delegate: Cell {
//        internalText.text: display;
//        visible: display != "Horse"
        displayText: display.toString();
        width: root.cellWidth
        height: root.cellHeight

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.model.move(index);
            }
        }
    }

//    GameController_qml{
//            id: _gameController
//    }

//    Component.onCompleted: {
//            root.model =  _gameController.getModel();
//    }
}
