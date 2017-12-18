/*!
 *@file main.cpp
 *@brief 程序主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <zlib.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("SilkPlatform.png");
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    file.close();
    uLong nDataSize = bytes.size();
    unsigned char *cData = new unsigned char[nDataSize];
    memcpy(cData, bytes.data(), nDataSize);
    uLong nCompSize = compressBound(nDataSize);
    unsigned char *cComp = new unsigned char[nCompSize];

    //压缩
    if (compress(cComp, &nCompSize, cData, nDataSize) != Z_OK)
    {
        printf("compress failed!\n");
        return -1;
    }

    //解压
    memset(cData, 0, nDataSize);
    if (uncompress(cData, &nDataSize, cComp, nCompSize) != Z_OK)
    {
        printf("uncompress failed!\n");
        return -1;
    }

    delete[] cComp;

    QFile fileOut("SilkPlatformOut.png");
    fileOut.open(QIODevice::WriteOnly);
    fileOut.write(reinterpret_cast<char*>(cData), nDataSize);
    fileOut.close();

    delete[] cData;

    return(0);
}
