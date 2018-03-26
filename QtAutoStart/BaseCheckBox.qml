/*!
 *@file BaseCheckBox.qml
 *@brief 自定义复选框
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

CheckBox {
    property string imgChecked: "qrc:/images/checked.png"
    property string imgUnchecked: "qrc:/images/unchecked.png"
    property string txtText: qsTr("")

    id: chk
    text: txtText
    font.family: "Microsoft YaHei"
    font.pixelSize: 15
    indicator:
        Image {
        id: img
        height: 16
        width: 16
        anchors.verticalCenter: parent.verticalCenter
        source: chk.checked ? imgChecked : imgUnchecked
    }

    contentItem: Text {
        id: text
        text: chk.text
        font: chk.font
        opacity: enabled ? 1.0 : 0.3
        color: chk.down ? "#AA0000" : "#148014"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        leftPadding: chk.indicator.width
    }
}

