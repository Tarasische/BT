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
#include<QTextStream>


class MyBluetooth: public QObject
{
    Q_OBJECT

public:
    MyBluetooth();
private:

    QBluetoothLocalDevice  localDevice;
    QList<QBluetoothDeviceInfo> listofdevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothSocket * socket;
    QBluetoothDeviceInfo selectedDevice;
public slots:
    void startDeviceDiscovery();
    void startLocalDiscovery();
    void deviceDiscovered();
    void SelectDevice(int index);
    void ConnectDevice();
    void SocketError();
    void SocketSuccessfull();
    void WriteData(QString text);
    void DisconnectDevice();
    void DisconnectSuccessfull();
signals:
    void SendText(QString text);
    void SendItem(QString item);
    void OpenInput();
    void CloseInput();
    void SetScanEnable();

};

#endif // MYBLUETOOTH_H
