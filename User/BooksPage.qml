import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "script.js" as Script

Page {
    header: Row { MenuBar{
            id:menuBar
            Menu {
                id: typeMenu
                title: qsTr("分级浏览")
                MenuItem {
                    text: "计算机"
                    onClicked: {
                        bookListView.delegate = delegateJ
                        bookListView.model = jBooks

                    }
                }
                MenuItem {
                    text:"英语"
                    onClicked: {
                        bookListView.delegate = delegateY
                        bookListView.model = yBooks
                    }
                }
                MenuItem {
                    id:miq
                    text:"其它"
                    onClicked: {
                        bookListView.delegate = delegateQ
                        bookListView.model = qBooks
                    }
                }
            }
        }
        ToolButton{
            text: "刷新"
            onClicked: {
                initModels()
            }
        }
        //        TextInput {
        //            width: 400

        //        }
        //        Button{
        //            text:"搜索"
        //        }
    }
    contentItem: ListView {
        //        anchors.fill: parent
        //        anchors.bottom: menuBar.bottom
        id:bookListView
        //        delegate:

    }
    ListModel {
        id: jBooks;
    }
    ListModel {
        id: yBooks;
    }
    ListModel {
        id: qBooks;
    }
    function initModels(){
        jBooks.clear();
        yBooks.clear();
        qBooks.clear();
        let request = new XMLHttpRequest();
        //                request.withCredentials = false
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                console.log(request.responseText)
                //                    bookListView.model =JSON.parse(request.responseText)["其它"]
                const object = JSON.parse(request.responseText)
                object["计算机"].forEach(function(o){
                    jBooks.append(o);
                })
                object["英语"].forEach(function(o){
                    yBooks.append(o);
                })
                object["其它"].forEach(function(o){
                    qBooks.append(o);
                })
                console.log(jBooks.count)
                console.log(yBooks.count)
                console.log(qBooks.count)
            }
        }

        request.open("GET", httpServer+"/allBooks");
        request.send();
    }
    Component.onCompleted: {
        initModels()
        miq.clicked()



    }
    Component {
        id:delegateJ
        BookDelegate {
            source: "qrc:/jbook.png"
        }
    }
    Component {
        id:delegateY
        BookDelegate {
            source: "qrc:/ybook.png"
        }
    }
    Component {
        id:delegateQ
        BookDelegate {
            source: "qrc:/qbook.png"
        }
    }
    Dialog {
        id: buyDialog
        anchors.centerIn: parent
        title: "购买数量"
        property string isbn
        property alias to: spinbox.to
        property real price : 0
        contentItem: Column{
            SpinBox {
                id:spinbox
                from:1
                value: 1
                stepSize: 1
                //                to:9
            }
            Text {
                text: "价格："+ spinbox.value * buyDialog.price
            }

        }
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            if(to < spinbox.value){
                    showToast("库存不足！")
            }else{
                buyBook(isbn,spinbox.value)
                spinbox.value = 1
            }
        }
    }
    function buyBook(isbn,count){
        console.log("Ok clicked")
        const xhr = new XMLHttpRequest()
        xhr.open("POST", httpServer+"/buyBook")
        var obj = {
            "isbn":isbn,
            "count":Math.abs(count)*(-1),
            "id":ss.id,
            "password":ss.password
        }
        console.log(JSON.stringify(obj))
        xhr.onreadystatechange = function (){
            if(xhr.readyState === XMLHttpRequest.DONE){
                if(xhr.responseText === "success"){
                    showToast("购买成功！")
                }else{
                    showToast("购买失败！")
                }
            }
        }
        xhr.send(JSON.stringify(obj))

    }
}

