/*!
 *@file main.qml
 *@brief 主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: qsTr("Qt设置开机启动")

    BaseCheckBox {
        id: checkBox
        text: qsTr("开机自动启动")
        checked: false
        anchors.centerIn: parent
        onClicked: {
            autostart.setAutoStart(checked);
        }
    }
}
