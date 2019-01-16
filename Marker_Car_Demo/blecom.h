#ifndef BLECOM_H
#define BLECOM_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QLowEnergyCharacteristic>
#include <QBluetoothUuid>
#include <QMap>
#include <QByteArray>

class BLECom : public QObject
{
    Q_OBJECT
public:
    explicit BLECom(QObject *parent = 0);

public slots:
    void devScan();
    void devConnect(const QString &dev, const QString &srvUuid, const QString &charUuid);
    void devDisconnect();

    void writeData(const QByteArray &data);

signals:
    void devDiscovered(const QString &info);
    void devScanFinished();
    void devDisconnected();
    void devConnected();
    void error(const QString &info);

    void dataReady(const QByteArray &data);

private slots:
    void devScanAgentError(QBluetoothDeviceDiscoveryAgent::Error newError);
    void devScanDiscovered(const QBluetoothDeviceInfo &dev);

    void devLeControllerError(QLowEnergyController::Error newError);
    void devLeControllerConnected();
    void devLeServerDiscovered();

    void devLeServerError(QLowEnergyService::ServiceError newError);
    void devLeCharReady(QLowEnergyService::ServiceState newState);

    void devDataReady(const QLowEnergyCharacteristic &characteristic, const QByteArray &value);

private:
    QBluetoothDeviceDiscoveryAgent *m_devScanAgent;
    QMap<QString, QBluetoothDeviceInfo> *m_devices;
    QLowEnergyController *m_leController;
    QLowEnergyService *m_leServer;
    QLowEnergyCharacteristic *m_leChar;
    QBluetoothUuid *m_srvUuid;
    QBluetoothUuid *m_charUuid;

    bool m_ready;
};

#endif // BLECOM_H
