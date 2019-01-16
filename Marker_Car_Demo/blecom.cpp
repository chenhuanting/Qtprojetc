#include "blecom.h"
#include <QList>
#include <QDebug>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

//ui->devSrvUuid->setText("0000ffe0-0000-1000-8000-00805f9b34fb");
//ui->devCharUuid->setText("0000ffe1-0000-1000-8000-00805f9b34fb");
BLECom::BLECom(QObject *parent) : QObject(parent)
{
    m_devScanAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_devScanAgent->setLowEnergyDiscoveryTimeout(5000);
    connect(this->m_devScanAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(devScanAgentError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(this->m_devScanAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(devScanDiscovered(QBluetoothDeviceInfo)));
    connect(this->m_devScanAgent, SIGNAL(finished()),
            this, SIGNAL(devScanFinished()));

    this->m_devices = new QMap<QString, QBluetoothDeviceInfo>;

    this->m_leController = NULL;
    this->m_leServer = NULL;
    this->m_leChar = NULL;
    this->m_srvUuid = NULL;
    this->m_charUuid = NULL;

    this->m_ready = false;
}

/**
 * @brief BLECom::devScan
 * 用于启动查找周围的低功耗蓝牙(BLE)设备，启动设备查找的行为是异步的，调用该函数后不会立即返回结果;
 * 调用该函数后，外部需要关联devDiscovered(QString)信号，用来接收查找到的周围BLE设备;
 * 接收到的的QString的格式是:DeviceName(DeviceAddress)，如:WOL(12-12-12-12-12).
 */
void BLECom::devScan()
{
    this->m_devScanAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

/**
 * @brief BLECom::devConnect
 * 使用本地的蓝牙设备适配器(hci0)连接指定的远程设备(dev)，跟远程设备上的服务(srvUuid)的Characteristic(charUuid)建立通信；
 * 连接远程设备的行为是异步的，调用该函数后不会立即返回结果，外部需要关联信号devConnected()才能知道蓝牙适配器是否已经正确建立通信；
 * 如果蓝牙适配器已经跟远程设备上的服务的Characteristic建立正确的连接，则会发出devConnected()信号；
 * 在连接过程中，如果蓝牙适配器发生任何连接错误，都会发出信号error()。
 *
 * @param dev
 * dev参数包含了指定的远程设备的信息，dev里设备信息的格式是：DeviceName(DeviceAddress)，如：WOL(12-12-12-12-12)；
 * dev的获取可以通过调用devScan()函数后，关联信号devDiscovered(QString)得到。
 *
 * @param srvUuid
 * srvUuid(server UUID)指的是远程设备上的要建立连接的服务的UUID;
 * UUID的格式：xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx，其中x是十六进制符号.
 *
 * @param charUuid
 * charUuid(Characteristic UUID)指的是远程设备要建立的服务的Characteristic的UUID;
 * UUID的格式：xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx，其中x是十六进制符号.
 *
 * @note
 * 在调用该函数前，必须调用devScan()函数进行设备的查找后，才能够正确的连接到指定的远程设备
 */
void BLECom::devConnect(const QString &dev, const QString &srvUuid, const QString &charUuid)
{
    //检测设备列表是否有指定的设备
    if(!this->m_devices->contains(dev))
    {
        emit error(QString("BLEController: No such device \"%1\"").arg(dev));
        return;
    }

    //检测srvUuid,charUuid格式的正确性

    //格式正确后，创建Uuid对象
    if(this->m_srvUuid != NULL)
        delete this->m_srvUuid;
    this->m_srvUuid = new QBluetoothUuid(QString("{%1}").arg(srvUuid));
    if(this->m_charUuid != NULL)
        delete this->m_charUuid;
    this->m_charUuid = new QBluetoothUuid(QString("{%1}").arg(charUuid));

    QBluetoothDeviceInfo device = this->m_devices->value(dev);
    if(this->m_leController != NULL)
        delete this->m_leController;
    this->m_leController = QLowEnergyController::createCentral(device, this);
    connect(this->m_leController, SIGNAL(error(QLowEnergyController::Error)),
            this, SLOT(devLeControllerError(QLowEnergyController::Error)));
    connect(this->m_leController, SIGNAL(connected()),
            this, SLOT(devLeControllerConnected()));
    connect(this->m_leController, SIGNAL(disconnected()),
            this, SIGNAL(devDisconnected()));
    connect(this->m_leController, SIGNAL(discoveryFinished()),
            this, SLOT(devLeServerDiscovered()));

    this->m_leController->connectToDevice();
}

void BLECom::writeData(const QByteArray &data)
{
    //确保已经建立连接
    if(!this->m_ready)
        return;

    this->m_leServer->writeCharacteristic(*this->m_leChar, data);
}

void BLECom::devDisconnect()
{
    if(this->m_ready)
    {
        this->m_ready = false;
        this->m_leController->disconnectFromDevice();
    }
}


void BLECom::devScanAgentError(QBluetoothDeviceDiscoveryAgent::Error)
{
    emit error(QString("LocalBluetoothAdapter(hci0):%1").arg(this->m_devScanAgent->errorString()));
}

void BLECom::devScanDiscovered(const QBluetoothDeviceInfo &dev)
{
    QString devInfo = QString("%1(%2)").arg(dev.name()).arg(dev.address().toString());
    this->m_devices->insert(devInfo, dev);

    emit devDiscovered(devInfo);
}

void BLECom::devLeControllerError(QLowEnergyController::Error)
{
    emit error(QString("BLEController:%1").arg(this->m_leController->errorString()));
}

void BLECom::devLeControllerConnected()
{
    this->m_leController->discoverServices();
}

void BLECom::devLeServerDiscovered()
{
    //取出远程设备上所有的服务UUID
    QList<QBluetoothUuid> devs = this->m_leController->services();
    for(int i=0; i<devs.count(); i++)
    {
        if(devs.at(i) == *(this->m_srvUuid))
        {
            if(this->m_leServer != NULL)
                delete this->m_leServer;
            //找到服务后创建一个服务对象并进行初始化信号槽
            this->m_leServer = this->m_leController->createServiceObject(devs.at(i), this);
            connect(this->m_leServer, SIGNAL(error(QLowEnergyService::ServiceError)),
                    this, SLOT(devLeServerError(QLowEnergyService::ServiceError)));
            connect(this->m_leServer, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
                    this, SLOT(devLeCharReady(QLowEnergyService::ServiceState)));
            connect(this->m_leServer, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),
                    this, SLOT(devDataReady(QLowEnergyCharacteristic,QByteArray)));

            //开始查找服务上全部的Characteristic
            this->m_leServer->discoverDetails();
            return;
        }
    }

    emit error(QString("BLEController: Remote device No such serve \"%1\"").arg(this->m_srvUuid->toString()));
}

void BLECom::devLeServerError(QLowEnergyService::ServiceError)
{
    emit error("BLEServe error");
}

void BLECom::devLeCharReady(QLowEnergyService::ServiceState newState)
{
    if(newState != QLowEnergyService::ServiceDiscovered)
        return;

    if(this->m_leChar != NULL)
        delete this->m_leChar;
    this->m_leChar = new QLowEnergyCharacteristic(this->m_leServer->characteristic(*this->m_charUuid));

    this->m_ready = true;
    emit devConnected();
}

void BLECom::devDataReady(const QLowEnergyCharacteristic &characteristic, const QByteArray &value)
{
    //判断是否对应的characteristic
    if(characteristic.uuid() != this->m_leChar->uuid())
        return;

    emit dataReady(value);
}

