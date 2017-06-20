#include "mybluetooth.h"
#include<iostream>


MyBluetooth::MyBluetooth()
{

}

void MyBluetooth::startLocalDiscovery()
{
    if (localDevice.isValid()) {
        QString str1 ;
        emit SendText("Bluetooth is available on this device");
        localDevice.powerOn();
        QString str2 = localDevice.name();
        QString str3 = localDevice.address().toString().trimmed();
        QString str4 = str2 + " " + str3;
        emit SendText(str4);
        emit SetScanEnable();
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    }
    else
        emit SendText(" Can not find local Bluetooth device");

}


void MyBluetooth::startDeviceDiscovery()
{
      emit SendText("Start devices discovery...");
      discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
      connect(discoveryAgent, SIGNAL(finished()),
              this, SLOT(deviceDiscovered()));
      discoveryAgent->start();
}

void MyBluetooth::deviceDiscovered()
{
   emit SendText("Discovery finished");
   listofdevice = discoveryAgent->discoveredDevices();
   discoveryAgent->stop();
   //delete discoveryAgent;
   if (!(listofdevice.isEmpty())) {
       emit SendText("Found new devices: ");
       for(int i = 0; i < listofdevice.size(); ++i){
           QString str1 =  listofdevice.at(i).name().trimmed();
           QString str2 =  listofdevice.at(i).address().toString().trimmed();
           QString str3 = str1 + "  " + str2;
           emit SendItem(str3);
       }
   }
   else
       emit SendText( "No devices found");
}

void MyBluetooth::SelectDevice(int index)
{
   selectedDevice = listofdevice.at(index);
   listofdevice.clear();
}

void MyBluetooth::ConnectDevice()
{

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol,this);
    emit SendText( "User select  device: " + selectedDevice.name() + " ( "
                + selectedDevice.address().toString().trimmed() + " )");
    connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(SocketError()));
    connect(socket, SIGNAL(connected()), this, SLOT(SocketSuccessfull()));
    socket->connectToService(QBluetoothAddress(selectedDevice.address()),
                                 QBluetoothUuid(QBluetoothUuid::SerialPort));

}

void MyBluetooth::SocketSuccessfull()
{
    emit SendText( "Socket connected succesful ");
    emit SendText( "You connect to name : ");
    emit SendText( socket->peerName() + " adrress :" + socket->peerAddress().toString().trimmed());
    emit OpenInput();
}

void MyBluetooth::SocketError()
{
    emit SendText(" Socket connected error");
}

void MyBluetooth::WriteData(QString text)
{
    if(!text.isEmpty())
    {
        std::string sender_text = text.toStdString();
        char info[text.length()];
        int j = 0;
        for(int i = 0; i < text.length();j++, i++)
        {
            if(!(('a' <= sender_text[i] && sender_text[i] <= 'z') ||
                ('A' <= sender_text[i] && sender_text[i] <= 'Z') ||
                ('0' <= sender_text[i] && sender_text[i] <= '9')))
            {
                --j;
                emit SendText("Valid Symbol in a string");
                continue;
            }
            info[j] = sender_text[i];
        }
        char last[j];
        for(int i = 0; i < j; ++i)
            last[i] = info[i];
        socket->write(last,j);
    }
    else
        emit SendText("Enter symbol");

}

void MyBluetooth::DisconnectDevice()
{
    connect(socket, SIGNAL(disconnected()),this, SLOT(DisconnectSuccessfull()));
    socket->disconnectFromService();
}

void MyBluetooth::DisconnectSuccessfull()
{
    emit CloseInput();
    emit SendText("Disconnect Successfull");

}

