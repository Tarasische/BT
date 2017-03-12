#ifndef MYBLUETOOTH_H
#define MYBLUETOOTH_H
#include<QBluetoothLocalDevice>
#include<QString>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothDeviceInfo>
#include<QDebug>
#include<QObject>
#include<QList>

class MyBluetooth: public QObject
{
    Q_OBJECT

public:
    MyBluetooth();
    void startDeviceDiscovery();
    void startLocalDiscovery();
private:

    QBluetoothLocalDevice localDevice;
    QString localDeviceName;
    QList<QBluetoothDeviceInfo> listofdevice;

public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);

};

#endif // MYBLUETOOTH_H
