#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>

class Motor : public QObject
{
	Q_OBJECT
public:
	explicit Motor(QObject *parent = nullptr);
	void startConnect();
	void setPWM(int motorA, int motorB, int motorC);
signals:
	void start();
	void writeData(const QByteArray&);
public slots:
};

#endif // MOTOR_H
