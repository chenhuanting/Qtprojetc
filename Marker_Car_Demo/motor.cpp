#include "motor.h"

Motor::Motor(QObject *parent) : QObject(parent)
{

}

void Motor::startConnect()
{
	emit start();
}

void Motor::setPWM(int motorA, int motorB, int motorC)
{
	int orderLength = 16;
	char * orderBuf = new char[orderLength];
	memset(orderBuf, 0, orderLength);

	char temp;
	int payload[3] = { motorA, motorB, motorC };

	int bufBase = 0;
	orderBuf[bufBase++] = 0x55;		//packet起始标志
	orderBuf[bufBase++] = 13;		//传输有效数据的长度
	orderBuf[bufBase++] = 0x00;		//命令字符

	//将motorA,motorB,motorC的值依次按照高8位到低8位的顺序装到orderBuf中
	for (int i = 0; i < 3; i++)
	{
		for (int j = 24; j >= 0; j = j - 8)
		{
			temp = (payload[i] >> j) & unsigned(0xFF);
			orderBuf[orderLength - 1] ^= temp;	//CRC校验码计算
			orderBuf[bufBase++] = temp;			//装载取出的字节
		}
	}
	emit writeData(QByteArray(orderBuf, orderLength));
	//释放内存
	delete orderBuf;
}
