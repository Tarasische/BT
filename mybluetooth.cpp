#include "mybluetooth.h"


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
        qDebug() << "connected to" << remotes;
    }
}

void MyBluetooth::startDeviceDiscovery()
{

      // Create a discovery agent and connect to its signals
      QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
      connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
              this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

      // Start a discovery
      discoveryAgent->start();

      //...
  }

  // In your local slot, read information about the found devices
void MyBluetooth::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
   qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
}
