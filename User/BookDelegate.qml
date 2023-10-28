import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

RowLayout {
    property alias source: bookImage.source
    id:rowLayout
    width: parent.width
    height: profileText.contentHeight > 100 ? profileText.contentHeight : 100
    clip:true

    Image {
        id: bookImage
        Layout.alignment: Qt.AlignVCenter
        Layout.maximumWidth: 40
        Layout.maximumHeight: 40
        fillMode: Image.PreserveAspectFit
        //        source: "qrc:/qbook.png"
    }

    Text {

        Layout.maximumWidth: 100
        //        Layout.maximumHeight: 40
        //        Layout.alignment: Qt.AlignCenter
        wrapMode: Text.WrapAnywhere
        id: nameText
        text: name
        font.bold: true
    }

    Text {
        Layout.maximumWidth: contentWidth
        Layout.maximumHeight: 40
        id: authorText
        text: author
        wrapMode: Text.WrapAnywhere
    }

    Text {
        id: profileText
        text: profile
        Layout.fillWidth: true
        //        Layout.maximumHeight: 40
        wrapMode: Text.WrapAnywhere

        Component.onCompleted: {
            if(width < 20){
                visible =false
                rowLayout.height = 100
            }
        }
    }

    Text {
        Layout.maximumWidth: contentWidth
        //        Layout.maximumHeight: 40
        Layout.alignment: Qt.AlignCenter
        id: timeText
        text: time
    }
    Button {
        text: "购买"
        Layout.alignment: Qt.AlignRight
        onClicked: {
            //            console.log(count)
            if(ss.id ===0 ){
                showToast("请先登录！")
                siwpeView.currentIndex =1
            }
            else{
                buyDialog.to = count
                buyDialog.price = price
                buyDialog.isbn = ISBN
                buyDialog.open()
            }
        }
    }


}

