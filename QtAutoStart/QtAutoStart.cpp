/*!
 *@file QtAutoStart.h
 *@brief 设置开机启动
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include "QtAutoStart.h"
#include <QSettings>
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>


QtAutoStart::QtAutoStart(QObject *parent) : QObject(parent)
{

}

void QtAutoStart::setAutoStart(bool bAutoStart)
{
#ifdef Q_OS_WIN32
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                  QSettings::NativeFormat);
    QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    QString strAppName = QFileInfo(strAppPath).baseName();

    reg.setValue(strAppName, bAutoStart ? strAppPath: "");
#endif

#ifdef Q_OS_LINUX
    //写.desktop文件, 到/etc/xdg/autostart目录下
#endif

#ifdef Q_OS_MACOS
    if (bAutoStart){
        LSSharedFileListRef loginItems = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
        CFURLRef url = (CFURLRef)[NSURL fileURLWithPath:QStringToNSString(appPath)];
        LSSharedFileListItemRef item = LSSharedFileListInsertItemURL(loginItems, kLSSharedFileListItemLast, NULL, NULL, url, NULL, NULL);
        CFRelease(item);
        CFRelease(loginItems);
    }else{
        UInt32 seedValue;
        CFURLRef thePath;
        LSSharedFileListRef loginItems = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
        CFArrayRef loginItemsArray = LSSharedFileListCopySnapshot(loginItems, &seedValue);
        for (id item in (NSArray *)loginItemsArray) {
            LSSharedFileListItemRef itemRef = (LSSharedFileListItemRef)item;
            if (LSSharedFileListItemResolve(itemRef, 0, (CFURLRef*) &thePath, NULL) == noErr){
                if ([[(NSURL *)thePath path] hasPrefix:QStringToNSString(appPath)]){
                    LSSharedFileListItemRemove(loginItems, itemRef);
                }
                CFRelease(thePath);
            }
        }
        CFRelease(loginItemsArray);
        CFRelease(loginItems);
    }
#endif
}
