import QtQuick
import QtQuick.Window
import QtQuick.Controls
//import "script.js" as Script

ApplicationWindow {
    //Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property alias siwpeView: siwpeView
    property string httpServer: "http://localhost:4444"


    SwipeView {
        id:siwpeView
        anchors.fill: parent
        BooksPage { id:bookPage}
        UserPage {}
        StorePage { id:storePage}
        CommentPage { id:commentPage }
    }

    footer:  ToolBar {
        Row {
            anchors.fill: parent
            ToolButton {
                //                width:
                text: "图书选购"
                onClicked: {
                    siwpeView.currentIndex=0
                    bookPage.initModels()
                }
            }
            ToolButton {
                text: "个人信息"
                onClicked: siwpeView.currentIndex =1
            }
            ToolButton {
                text: "书店信息"
                onClicked:{
                    siwpeView.currentIndex =2
                    storePage.init()
                }
            }
            ToolButton {
                text: "留言反馈"
                onClicked: {
                    siwpeView.currentIndex =3
                    commentPage.init()
                }
            }

        }
    }



    Rectangle {
        width: infoText.contentWidth + 10
        height: infoText.contentHeight + 10
        radius: 10
        color: "lightgray"
        opacity: 0
        z: 10
        visible: toastVisible
        anchors.centerIn: parent

        Text {
            id:infoText
            font.pixelSize: 22
            anchors.centerIn: parent
            text: toastText
        }

        NumberAnimation on opacity {
            to: 1;
            duration: 1000 ;
            easing.type: Easing.InOutQuad
        }
    }

    Timer {
        id: toastTimer
        interval: 1000 // 1秒
        onTriggered: hideToast()
    }

    property bool toastVisible: false
    property string toastText: ""

    function showToast(text) {
        toastText = text;
        toastVisible = true;
        toastTimer.start();
    }

    function hideToast() {
        toastVisible = false;
        toastTimer.stop();
    }

    Component.onCompleted: {
//        showToast("This is a toast message.")
    }

}
