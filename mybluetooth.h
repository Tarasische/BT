#ifndef MYBLUETOOTH_H
#define MYBLUETOOTH_H
#include<QBluetoothLocalDevice>
#include<QString>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothDeviceInfo>
#include<QDebug>
#include<QObject>
#include<QList>
#include<QBluetoothSocket>
#include<QBluetoothUuid>
#include<QBluetoothAddress>

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
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothSocket * socket;
    QBluetoothDeviceInfo selectedDevice;
public slots:
    void deviceDiscovered();
    void connectedtodevice();
    void SelectDevice();
    void SocketError();
    void SocketConnect();
};

#endif // MYBLUETOOTH_H
