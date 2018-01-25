/*!
 *@file main.cpp
 *@brief 程序主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLocalSocket>
#include <QLocalServer>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    //连接LocalServer
    QString serverName = "localserver";
    QLocalSocket socket;
    socket.connectToServer(serverName);
    if(socket.waitForConnected(1000)) return(-1);

    //创建LocalServer
    QLocalServer server;
    if (server.listen(serverName)){
        if(server.serverError()== QAbstractSocket::AddressInUseError &&
                QFile::exists(server.serverName())){
            QFile::remove(server.serverName());
            server.listen(serverName);
        }
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
