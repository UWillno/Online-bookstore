import QtQuick
//import Qt.labs.platform
import QtQuick.Controls
import "script.js" as Script
Rectangle {
    //    visible: false
    id: dialog
    property alias row1: row1
    width: 184
    height: 144
    //    anchors.centerIn: parent
    color: "#f5f5f5"
    radius: 10
    border.width: 2
    state: "login"
    states: [
        State {
            name: "login"
            PropertyChanges {
                target: row1
                visible:false
            }
            PropertyChanges {
                target: buttonBack
                visible: false
            }
            //            PropertyChanges {
            //                target: buttonSignUp
            //                visible: false
            //            }
            PropertyChanges {
                target: buttonLogin
                visible: true
            }
        },
        State {
            name: "signup"
            PropertyChanges {
                target: row1
                visible: true
            }
            PropertyChanges {
                target: buttonLogin
                visible: false
            }
            //            PropertyChanges {
            //                target: buttonSignUp
            //                visible: true
            //            }
            PropertyChanges {
                target: buttonBack
                visible: true
            }
        }
    ]
    Column {
        id: column
        width: 157
        height: 103
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.horizontalCenter: parent.horizontalCenter
        anchors.centerIn: parent
        spacing: 5


        Row {
            id: row
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                id: text1
                text: qsTr("手机号")
                font.pixelSize: 14
            }
            Rectangle {
                width: parent.width - text1.width - 10
                height: 20
                clip: true
                border.width: 1
                color: "lightgray"
                TextInput {
                    id: textInputId
                    anchors.fill: parent
                    font.pixelSize: 12
                    maximumLength: 11
                }
            }
        }

        Row {
            id: row1
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                id: text2
                text: qsTr("昵  称")
                font.pixelSize: 14
            }
            Rectangle {
                width: parent.width - text2.width - 10
                height: 20
                clip: true
                border.width: 1
                color: "lightgray"
                TextInput {
                    id: textInputName
                    anchors.fill: parent
                    //                    text: qsTr("")
                    font.pixelSize: 14
                }
            }
        }

        Row {
            id: row2
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                id: text3
                text: qsTr("密  码")
                font.pixelSize: 14
            }
            Rectangle {
                width: parent.width - text3.width - 10
                height: 20
                clip: true
                border.width: 1
                color: "lightgray"

                TextInput {
                    id: textInputPwd
                    font.pixelSize: 12
                    anchors.fill: parent
                    echoMode:TextInput.Password
                    //                textFormat:

                }
            }
        }

        Row {
            id: row3
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 20

            Item {
                width: 1
            }
            Button {
                id: buttonLogin
                width: 50
                height: 20
                text: qsTr("登录")
                onClicked:login(Number(textInputId.text),Script.hex_md5(textInputPwd.text))
            }

            Button {
                id: buttonSignUp
                width: 50
                height: 20
                text: qsTr("注册")
                onClicked:  {
                    if(dialog.state !== "signup"){
                        dialog.state ="signup"
                    }
                    else{
                        console.log("ok")
                        enabled = false
                        signUp(Number(textInputId.text),textInputName.text,textInputPwd.text)


                    }
                }
            }

            Button {
                id: buttonBack
                width: 50
                height: 20
                text: qsTr("返回")
                onClicked: {
                    dialog.state = "login"
                }
            }
        }
    }
    function login(id,password){
        buttonLogin.enabled = false
        const xhr = new XMLHttpRequest()
        xhr.open("POST", httpServer+"/login")
        var obj = {
            "id":id,
            "password":password
        }
        console.log(JSON.stringify(obj))
        xhr.onreadystatechange = function (){
            if(xhr.readyState === XMLHttpRequest.DONE){
                if(xhr.responseText !== ""){
                    showToast("登录成功！")
                    ss.id = id
                    ss.name = xhr.responseText
                    ss.password = password
//                    dialog.visible = false
                }else{
                    showToast("登录失败！")
                }
                buttonLogin.enabled = true
            }

        }
        xhr.send(JSON.stringify(obj));
    }


    function signUp(id,name,password){
        const xhr = new XMLHttpRequest()
        xhr.open("POST", httpServer+"/signUp")
        var obj = {
            "id":id,
            "name":name,
            "password":password
        }
        console.log(JSON.stringify(obj))
        xhr.onreadystatechange = function (){
            if(xhr.readyState === XMLHttpRequest.DONE){
                if(xhr.responseText === "success"){
                    showToast("注册成功！")
                }else{
                    showToast("注册失败！")
                }
                buttonSignUp.enabled = true
            }

        }
        xhr.send(JSON.stringify(obj));
    }


    //            text: "The document has been modified."



}



