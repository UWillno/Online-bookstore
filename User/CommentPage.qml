import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Page {
    property alias commentText: commentTextArea.text
    header:Text {
        font.pointSize: 20
        text: "历史留言"
    }

    contentItem: ListView {
        id:listview
        //                model: commentsModel
        model: commentsModel
        delegate: CommentDelegate{
            width: parent.width

            onHeightChanged: listview.forceLayout()
        }
    }

    ListModel {
        id:commentsModel
    }

    footer: RowLayout{
        spacing: 10
        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#f5f5f5"
            clip:true
            TextArea {
                anchors.fill: parent
                id: commentTextArea
                placeholderText: "请输入留言"
            }
        }
        Button{
            Layout.fillHeight: true
            text:"留言"
            onClicked:submitComment(commentText)
        }

    }
    function submitComment(content){
        if(ss.id ===0){
            showToast("请先登录！")
            siwpeView.currentIndex =1
        }else if(commentText == "")
        {
            showToast("留言不能为空！")
        }
        else{
            const xhr = new XMLHttpRequest()
            xhr.open("POST", httpServer+"/insertComment")
            var obj = {
                "content":content,
                "id":ss.id,
                "password":ss.password
            }
            console.log(JSON.stringify(obj))
            xhr.onreadystatechange = function (){
                if(xhr.readyState === XMLHttpRequest.DONE){
                    if(xhr.responseText === "success"){
                        showToast("留言成功！")
                        commentText = ""
                        init()
                    }else{
                        showToast("留言失败！")
                    }
                }
            }
            xhr.send(JSON.stringify(obj))
        }

    }

    function init(){
        const xhr = new XMLHttpRequest()
        xhr.open("GET", httpServer+"/selectComments/"+ss.id)
        //        console.log(JSON.stringify(obj))
        xhr.onreadystatechange = function (){
            if(xhr.readyState === XMLHttpRequest.DONE){
                commentsModel.clear()
                JSON.parse(xhr.responseText).forEach(function(o){
                    commentsModel.append(o);
                });

            }
        }
        xhr.send()
    }

    Component.onCompleted: init()
}
