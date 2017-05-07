#include <QCoreApplication>
#include<QBluetoothLocalDevice>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QString>
#include<QList>
#include"mybluetooth.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyBluetooth localDev;
    localDev.startLocalDiscovery();//
    localDev.startDeviceDiscovery();

    return a.exec();
}
