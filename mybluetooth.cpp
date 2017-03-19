#include "mybluetooth.h"
#include<iostream>


MyBluetooth::MyBluetooth()
{

}

void MyBluetooth::startLocalDiscovery()
{
    if (localDevice.isValid()) {
        qDebug() << "Bluetooth is available on this device";
        // Turn Bluetooth on
        localDevice.powerOn();

        // Read local device name
        localDeviceName = localDevice.name();
        qDebug() << "Local device: " << localDeviceName << " ("
                         << localDevice.address().toString().trimmed() << ")";
        // Make it visible to others
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        // Get connected devices
        QList<QBluetoothAddress> remotes;
        remotes = localDevice.connectedDevices();
    }
}

//void MyBluetooth::startDeviceDiscovery()
//{

//      // Create a discovery agent and connect to its signals
//      QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
//      connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
//              this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

//      // Start a discovery
//      discoveryAgent->start();

//      //...
//  }

void MyBluetooth::startDeviceDiscovery()
{

      // Create a discovery agent and connect to its signals
      discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
      connect(discoveryAgent, SIGNAL(finished()),
              this, SLOT(deviceDiscovered()));

      // Start a discovery
      discoveryAgent->start();

      //...
  }
void MyBluetooth::deviceDiscovered()
{
   qDebug() << "discovery finished";
   listofdevice = discoveryAgent->discoveredDevices();
   discoveryAgent->stop();
   if (!(listofdevice.isEmpty())) {
       qDebug() << "Found new services:";
       for(int i = 0; i < listofdevice.size(); ++i)
           qDebug() << "Device: "
                    << listofdevice.at(i).name().trimmed()
                    << " ("
                    << listofdevice.at(i).address().toString().trimmed() << ")"
                    << listofdevice.at(i).deviceUuid();
   }
   else
       qDebug() << "No services found";
   std::cout << "enter integer ";
   int a;
   std::cin >> a;
   selectedDevice = listofdevice.at(a);
   SelectDevice();
//   socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
//    connect(socket,SIGNAL(connected()),this,SLOT(connectedtodevice())) ;
//    socket->connectToService(listofdevice.at(a).address(),
//                                 QBluetoothUuid(QBluetoothUuid::SerialPort));
//    //socket->connectToService(listofdevice.at(a).address(),listofdevice.at(a).deviceUuid());
//   qDebug() << "discover finished" ;
}

void MyBluetooth::SelectDevice()
{
    QBluetoothUuid MyUuid (QString("5afb2136-47ab-45f8-8c2a-891bbe76454a"));
    selectedDevice.setDeviceUuid(MyUuid);
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "User select a device: " << selectedDevice.name() << " ("
                << selectedDevice.address().toString().trimmed() << ")"
                << selectedDevice.deviceUuid() ;
    connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(SocketError()));
    connect(socket, SIGNAL(connected()), this, SLOT(SocketConnect()));
    //socket->connectToService(QBluetoothAddress(selectedDevice.address()),QBluetoothUuid());

    socket->connectToService(QBluetoothAddress(selectedDevice.address()), QBluetoothUuid(MyUuid));
}

void MyBluetooth::SocketConnect()
{
    qDebug() << " Socket connected succesful";
}

void MyBluetooth::SocketError()
{
    qDebug() << " Socket connected error";
}

void MyBluetooth::connectedtodevice()
{
    qDebug() << " conneced to dsevice succesfull";
}

  // In your local slot, read information about the found devices
//void MyBluetooth::deviceDiscovered(const QBluetoothDeviceInfo &device)
//{
//   qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
//}
