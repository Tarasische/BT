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


void MyBluetooth::startDeviceDiscovery()
{
      discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
      connect(discoveryAgent, SIGNAL(finished()),
              this, SLOT(deviceDiscovered()));
      discoveryAgent->start();
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
                    << listofdevice.at(i).address().toString().trimmed() << ")";
   }
   else
       qDebug() << "No services found";
   std::cout << "enter integer ";
   int a;
   std::cin >> a;
   selectedDevice = listofdevice.at(a);
   SelectDevice();
}

void MyBluetooth::SelectDevice()
{
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol,this);
    qDebug() << "User select a device: " << selectedDevice.name() << " ("
                << selectedDevice.address().toString().trimmed() << ")";
    connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(SocketError()));
    connect(socket, SIGNAL(connected()), this, SLOT(SocketConnect()));
    socket->connectToService(QBluetoothAddress(selectedDevice.address()),
                                 QBluetoothUuid(QBluetoothUuid::SerialPort));

}

void MyBluetooth::SocketConnect()
{
    qDebug() << " Socket connected succesful ";
    qDebug() << " You connect to name : " << socket->peerName() << " adrress :" << socket->peerAddress().toString().trimmed();
    WriteData();
}

void MyBluetooth::SocketError()
{
    qDebug() << " Socket connected error";
}

void MyBluetooth::connectedtodevice()
{
    qDebug() << " conneced to dsevice succesfull";
}

void MyBluetooth::WriteData()
{
    std::cout << " Write data, to exit tap <<Q>> " << std::endl;
    char arr[20];
    std::cin.getline(arr,3,'\n');
    while(arr[0] != 'Q'){
    std::cin.getline(arr,3,'\n');
    socket->write(arr,20);
    }
}
