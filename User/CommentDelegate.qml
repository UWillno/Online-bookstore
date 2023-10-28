import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
ColumnLayout {
    //    width: parent.width
    id:col
    spacing: 10
    property real rheight
    height: !cswitch.checked ? comment1Row.height : rheight
    clip: true
    Behavior on height {
        NumberAnimation { duration: 1000 }
    }

    RowLayout {
        width: parent.width
        id:comment1Row
        Text {
            id: comment1
            Layout.fillWidth: true
            font.bold: true
            text: content
        }
        Switch {
            id:cswitch
            text: "反馈"
            visible: reply.count!==0
            onClicked:{
                console.log(checked)
                console.log(comment1Row.height)
                console.log(rheight)
            }
        }
    }
    Component {
        id:comment2Component
        Text {
            width: parent.width
            id:comment2
        }

    }


    Component.onCompleted: {
        rheight = comment1Row.height
        for (var i = 0; i < reply.count; i++) {
            var item = reply.get(i);
            comment2Component.createObject(col,{text:item.content})
            rheight = rheight + comment1Row.height
        }

    }


}
