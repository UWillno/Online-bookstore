import QtQuick
import QtQuick.Controls
Page {
    id: page
    property alias storeProfile: textArea.text
    Column {
        id: columnLayout
        anchors.fill: parent
        spacing: 10
        Text {
            id: text1
            anchors.horizontalCenter: parent.horizontalCenter
            text: "店铺简介"
            font.pixelSize: 17
            font.styleName: "Bold"
        }
        ScrollView{
            width: parent.width
            height:  parent.height/2
            TextArea {
                id: textArea
                placeholderText: qsTr("Text Area")
                textFormat: "RichText"
                readOnly: true
            }
        }

        Text {
            id: text2
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("店铺信息")
            font.pixelSize: 17
            font.styleName: "Bold"
        }

        ListView {
            id: listView
            clip: true
            width:parent.width
            height: parent.height - text1.height - text2.height - textArea.height
            model: newsModel
            delegate: Text{
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                text:content +"\t发布于" + time
                wrapMode: Text.WrapAnywhere
                textFormat: Text.RichText
            }
        }
    }

    ListModel {
        id:newsModel
    }


    function init(){
        const xhr = new XMLHttpRequest()
        xhr.open("GET", httpServer+"/storeInfo")
        xhr.onreadystatechange = function (){
            if(xhr.readyState === XMLHttpRequest.DONE){
                var data = JSON.parse(xhr.responseText)
                storeProfile = data["profile"]
                newsModel.clear()
                data["news"].forEach(function(o){
                    newsModel.append(o)
                })
            }
        }
        xhr.send()


    }

    Component.onCompleted: init()



}
