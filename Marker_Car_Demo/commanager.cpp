#include "commanager.h"
#include <QDebug>

ComManager::ComManager(QObject *parent) : QObject(parent)
{
    m_com = new BLECom(this);
    connect(m_com, SIGNAL(devScanFinished()), this, SLOT(connectToDevice()));
    connect(m_com, SIGNAL(devConnected()), this, SLOT(devReady()));
    connect(m_com, SIGNAL(error(QString)), this, SLOT(error(QString)));
}
//ui->devSrvUuid->setText("0000ffe0-0000-1000-8000-00805f9b34fb");
//ui->devCharUuid->setText("0000ffe1-0000-1000-8000-00805f9b34fb");
//void devConnected();
//void error(const QString &info);
void ComManager::connectToDevice()
{
    m_com->devConnect("WOL(00:15:83:00:86:F9)",
                      "0000ffe0-0000-1000-8000-00805f9b34fb",
                      "0000ffe1-0000-1000-8000-00805f9b34fb");
}
void ComManager::devReady()
{
    qDebug() << "Dev Ready";
}

void ComManager::error(const QString& info)
{
    qDebug() << info;
}

void ComManager::start()
{
    m_com->devScan();
}

void ComManager::writeData(const QByteArray& data)
{
    m_com->writeData(data);
}
