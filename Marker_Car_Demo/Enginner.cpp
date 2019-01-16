#include "Enginner.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <cstdio>
#include <thread>
#include <chrono>
#include <QObject>
#include <QDebug>

using namespace std;
using namespace cv;
using namespace std::this_thread;
using namespace std::chrono;

bool g_ready = false;
bool g_targetReady = false;
bool g_record = false;
Point2f g_target = Point2f(0.0f, 0.0f);
double g_targetPosition = 0;

void onMouse(int event, int x, int y, int flags, void * param)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		g_target.x = (float)x;
		g_target.y = (float)y;
		break;
	case CV_EVENT_RBUTTONDOWN:
		g_targetReady = true;
		break;
	case CV_EVENT_MBUTTONDOWN:
		g_ready = !g_ready;
		break;
	}
}

Enginner::Enginner()
{
    cvNamedWindow(m_windowsName.c_str());
    setMouseCallback(m_windowsName, onMouse, NULL);

    m_com = new ComManager;
    m_motor = new Motor;
    QObject::connect(m_motor, SIGNAL(start()), m_com, SLOT(start()));
    QObject::connect(m_motor, SIGNAL(writeData(QByteArray)), m_com, SLOT(writeData(QByteArray)));
    m_comThread = new QThread;
    m_com->moveToThread(m_comThread);
    m_comThread->start();
    qDebug() << "Waitting Connect";
    m_motor->startConnect();
    sleep_for(seconds(10));
    qDebug() << "Connected";

    m_config = new QSettings(":/config.ini", QSettings::IniFormat);
    m_markerDetect = new MarkerDetect(m_config->value("MarkerDetect/CameraCalibration").toString().toStdString(),
                                      m_config->value("MarkerDetect/ArucoSquareDimension").toFloat());
    m_vehicle = new RobotVehicle(m_markerDetect->cameraMatrix());

    m_target = Point2d(50.0f, 50.0f);

    m_directController_input = 0.0;
    m_directController_output = 0.0;
    m_directController_sp = 0.0;
    m_directController = new PID(&m_directController_input, &m_directController_output, &m_directController_sp,
                                 m_config->value("DirectController/Kp").toDouble(),
                                 m_config->value("DirectController/Ki").toDouble(),
                                 m_config->value("DirectController/Kd").toDouble(), REVERSE);
    m_directController->SetSampleTime(m_config->value("DirectController/SampleTime").toInt());
    m_directController->SetOutputLimits(m_config->value("DirectController/Min").toDouble(),
        m_config->value("DirectController/Max").toDouble());

    m_positionController_sp = 0.0;
    m_positionController_input = 0.0;
    m_positionController_output = 0.0;
    m_positionController = new PID(&m_positionController_input, &m_positionController_output, &m_positionController_sp,
                                   m_config->value("PositionController/Kp").toDouble(),
                                   m_config->value("PositionController/Ki").toDouble(),
                                   m_config->value("PositionController/Kd").toDouble(), DIRECT);
      m_positionController->SetSampleTime(m_config->value("PositionController/SampleTime").toInt());
      m_positionController->SetOutputLimits(m_config->value("PositionController/Min").toDouble(),
          m_config->value("PositionController/Max").toDouble());

    qDebug().noquote() << QString("DirectController:Kp=%1,Ki=%2,Ki=%3,SampleTime=%4,Outlmits_Min=%5,Outlimts_Max=%6")
                .arg(m_directController->GetKp()).arg(m_directController->GetKi()).arg(m_directController->GetKd())
                .arg(m_directController->GetSampleTime()).arg(m_directController->GetOutMin()).arg(m_directController->GetOutMax());


    qDebug().noquote() << QString("PositionController:Kp=%1,Ki=%2,Ki=%3,SampleTime=%4,Outlmits_Min=%5,Outlimts_Max=%6")
                .arg(m_positionController->GetKp()).arg(m_positionController->GetKi()).arg(m_positionController->GetKd())
                .arg(m_positionController->GetSampleTime()).arg(m_positionController->GetOutMin()).arg(m_positionController->GetOutMax());

    m_vwriter = new VideoWriter;
    m_vwriter->open("demo.avi", CV_FOURCC('P', 'I', 'M', '1'), 25, m_markerDetect->videoSize());
}


Enginner::~Enginner()
{
	delete m_config;
	delete m_markerDetect;
	delete m_vehicle;
}

void Enginner::process()
{
	char ch;
	char deviationBuf[128];
	Point3f deviation;
	while (true)
	{
        if (m_markerDetect->updateMarker() && g_ready)
        {
			
            if (g_targetReady)
            {
                m_vehicle->setTarget(g_target);
            }
            deviation = m_vehicle->updateDeviation(m_markerDetect->lastMarkerCorners(),
                                                   m_markerDetect->lastRotationVectors(),
                                                   m_markerDetect->lastTranslationVectors());
            if (g_targetReady)
            {
                g_targetReady = false;
                //方向控制器设置定点输入
                m_directController_sp = deviation.y;
                //方向控制器启动
                m_directController->SetMode(AUTOMATIC);

                m_positionController_sp = deviation.x * 100;
                m_positionController->SetMode(AUTOMATIC);
            }
            //画出与target的连线,标出target所在位置
            cv::line(m_markerDetect->lastFrame(), m_vehicle->position(), g_target, Scalar(0, 0, 0), 2, 8);
            cv::circle(m_markerDetect->lastFrame(), g_target, 2, CV_RGB(20, 150, 20), -1);
            putText(m_markerDetect->lastFrame(), "Target", g_target, CV_FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0, 255, 168), 1, 8);
            //动态显示与目标的距离以及方向误差
            memset(deviationBuf, 0, 128);
            sprintf(deviationBuf, "p = %4.2f, alpha = %4.2f, beta = %4.2f", deviation.x, deviation.y, deviation.z);
            putText(m_markerDetect->lastFrame(), deviationBuf, Point2f(200, 100), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 255, 168), 1, 8);

            //方向控制器的输入
            m_directController_input = m_directController_sp - deviation.y;
            m_directController->Compute();

            m_positionController_input = m_positionController_sp - (deviation.x*100);
            m_positionController->Compute();

            if (m_directController->GetMode() && m_positionController->GetMode())
            {
//                cout << "direct controller setpoint:" << m_directController_sp << endl;
//                cout << "direct controller input:" << m_directController_input << endl;
//                cout << "direct controller output:" << m_directController_output << endl;

                if(deviation.y > 10.0 || deviation.y < -10.0)
                    m_motor->setPWM(m_directController_output, m_directController_output, m_directController_output);
                else
                    m_motor->setPWM(0, -m_positionController_output, m_positionController_output);

            }
            else
            {
                m_motor->setPWM(0, 0, 0);
            }
        }
        imshow(m_windowsName, m_markerDetect->lastFrame());
        if(g_record)
        {
            m_vwriter->write(m_markerDetect->lastFrame());
        }
        ch = waitKey(30);
        switch (ch)
        {
        case 27:
            return;
        case ' ':
            g_record = !g_record;
            if(g_record)
            {
                qDebug() << "Start Record";
            }
            else
            {
                qDebug() << "Stop Record";
            }
            break;
        }
//        cout << "Input:";
//        int pwm;
//        cin >> pwm;
//        m_motor->setPWM(0, pwm, 0);
	}
}


