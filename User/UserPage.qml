import QtQuick
import QtQuick.Controls
import "script.js" as Script
Page {

    LoginDialog {
        id:loginDialog
        anchors.centerIn: parent
        visible: ss.id===0
        scale: 2
    }


    Column{
        anchors.centerIn: parent
        visible: !loginDialog.visible
        spacing: 10
        Text {
            id: idText
            text: "手机号："+ ss.id
        }
        Text {
            id: nameText
            text: "姓名："+ ss.name
        }
        Row {
            spacing: 20
            Button {
                text: "修改姓名"
                onClicked: changeNameDialog.open()
            }
            Button {
                text: "修改密码"
                onClicked: changePasswordDialog.open()
            }
            Button {
                text: "登出"
                onClicked: {
                    ss.reset();
                    //                   loginDialog.visible = true;
                }
            }
        }
    }

    Dialog {
        id:changeNameDialog
        title: "修改姓名"
        anchors.centerIn: parent
        property alias newName: newNameTextInput.text
        contentItem: Row {
            spacing:10
            Text {
                id:newNameText
                text:"新姓名"
            }
            Rectangle {
                width: 200
                height:newNameText.height
                color:"#f5f5f5"
                clip: true
                border.width: 1
                TextInput {
                    id:newNameTextInput
                anchors.fill: parent

                }

            }


        }
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            changeName(newName)
            newName = ""
        }
    }
    function changeName(name){
        const xhr = new XMLHttpRequest()
        xhr.open("POST", httpServer+"/changeName")
        var obj = {
            "id":ss.id,
            "password":ss.password,
            "name":name
        }
        console.log(JSON.stringify(obj))
        xhr.onreadystatechange = function (){
            if(xhr.readyState === XMLHttpRequest.DONE){
                if(xhr.responseText === "success"){
                    showToast("修改成功！")
                    ss.name = name
                }else{
                    showToast("修改失败！")
                }
            }
        }
        xhr.send(JSON.stringify(obj))
    }

    Dialog {
        id:changePasswordDialog
        title: "修改密码"
        anchors.centerIn: parent
        property alias oldPassword: oldPasswordInputText.text
        property alias newPassword: newPasswordInputText.text
        contentItem: Column{
            spacing: 10
            Row{
                id:row1
                spacing: 10
                Text {
                    id: text1
                    text: qsTr("当前密码")
                }
                Rectangle {
                    color:"#f5f5f5"
                    width: 200
                    height: text1.height
                    clip: true
                    border.width: 1
                    TextInput{
                        id:oldPasswordInputText
                        anchors.fill: parent
                        echoMode: TextInput.Password
                    }
                }

            }
            Row{
                spacing: 10
                Text {
                    text: qsTr("新密码")
                }
                Rectangle {
                    width: row1.width - text1.width
                    height: text1.height
                    clip: true
                    color:"#f5f5f5"
                    border.width: 1
                    //                    clip:true
                    TextInput{
                        id:newPasswordInputText
                        anchors.fill: parent
                        echoMode: TextInput.Password
                    }
                }

            }

        }
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            changePassword(oldPassword,newPassword)
            oldPassword = ""
            newPassword = ""
        }

    }

    function changePassword(oldPassword,newPassword){
        const xhr = new XMLHttpRequest()
        xhr.open("POST", httpServer+"/changPassword")
        var obj = {
            "id":ss.id,
            "oldPassword":Script.hex_md5(oldPassword),
            "newPassword":newPassword
        }
        console.log(JSON.stringify(obj))
        xhr.onreadystatechange = function (){
            if(xhr.readyState === XMLHttpRequest.DONE){
                if(xhr.responseText === "success"){
                    showToast("修改成功！")
                    ss.password = Script.hex_md5(newPassword)
                }else{
                    showToast("修改失败！")
                }
            }
        }
        xhr.send(JSON.stringify(obj))

    }
}
