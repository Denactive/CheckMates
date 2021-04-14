import QtQuick 2.0

Rectangle {
    id: root
    property string displayText: "1"
//    property alias internalText: _firstText

    color: "blue"
    border {
        color: "black"
        width: 1
    }

//    radius: 10

    Text {
        id: _firstText
        anchors.centerIn: root
//        anchors.left: root.left
//        anchors.leftMargin: 10

//        x: root.width / 2 - width / 2
//        y: root.height / 2 - height / 2
        text: root.displayText
        font {
            pointSize: Math.min(root.width, root.height) / 3
            bold: true
        }
    }
}
