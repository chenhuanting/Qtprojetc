#ifndef COMMANAGER_H
#define COMMANAGER_H

#include <QObject>
#include "blecom.h"

class ComManager : public QObject
{
    Q_OBJECT
public:
    explicit ComManager(QObject *parent = nullptr);
signals:

public slots:
    void connectToDevice();
    void devReady();
    void error(const QString& info);

    void start();
    void writeData(const QByteArray& data);
protected:
    BLECom* m_com;

};

#endif // COMMANAGER_H
