/*!
 *@file QtAutoStart.h
 *@brief 设置开机启动
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#pragma once
#include <QObject>

class QtAutoStart : public QObject
{
    Q_OBJECT
public:
    explicit QtAutoStart(QObject *parent = nullptr);
    Q_INVOKABLE void setAutoStart(bool bAutoStart);

signals:

public slots:

};
