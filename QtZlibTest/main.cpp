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

int zlibCompress(char *dest,   int &destLen,
                 char *source, int sourceLen)
{
    unsigned char* dest1 = reinterpret_cast<unsigned char*>(dest);
    unsigned long destLen1 = static_cast<unsigned long>(destLen);
    unsigned char* source1 = reinterpret_cast<unsigned char*>(source);
    unsigned long sourceLen1 = static_cast<unsigned long>(sourceLen);

    return(compress(dest1, &destLen1, source1, sourceLen1));
}

int zlibUncompress(char *dest,   int &destLen,
                   char *source, int sourceLen)
{
    unsigned char* dest1 = reinterpret_cast<unsigned char*>(dest);
    unsigned long destLen1 = static_cast<unsigned long>(destLen);
    unsigned char* source1 = reinterpret_cast<unsigned char*>(source);
    unsigned long sourceLen1 = static_cast<unsigned long>(sourceLen);

    return(uncompress(dest1, &destLen1, source1, sourceLen1));
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("SilkPlatform.png");
    file.open(QIODevice::ReadOnly);
    QByteArray bytes = file.readAll();
    file.close();
    int nDataSize = bytes.size();
    char *cData = new char[nDataSize];
    memcpy(cData, bytes.data(), nDataSize);
    int nCompSize = compressBound(nDataSize);
    char *cComp = new char[nCompSize];

    //压缩
    if (zlibCompress(cComp, nCompSize, cData, nDataSize) != Z_OK)
    {
        printf("compress failed!\n");
        return -1;
    }

    //解压
    memset(cData, 0, nDataSize);
    if (zlibUncompress(cData, nDataSize, cComp, nCompSize) != Z_OK)
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
