#ifndef __ENGINNER_H
#define __ENGINNER_H

#include <iostream>
#include <string>
#include <QSettings>
#include <QThread>
#include "MarkerDetect.h"
#include "RobotVehicle.h"
#include "pid/PID_v1.h"
#include "opencv2/core.hpp"
#include "commanager.h"
#include "motor.h"
#include "opencv2/videoio.hpp"

class Enginner
{
public:
	Enginner();
	~Enginner();

	void process();
protected:
	std::string m_windowsName;
    QSettings * m_config;
	MarkerDetect* m_markerDetect;
	RobotVehicle* m_vehicle;
	cv::Point2d m_target;

	double m_directController_sp;
	double m_directController_input;
	double m_directController_output;
	PID *m_directController;

    double m_positionController_sp;
    double m_positionController_input;
    double m_positionController_output;
    PID *m_positionController;

    ComManager* m_com;
    Motor* m_motor;
    QThread* m_comThread;

    cv::VideoWriter *m_vwriter;
};

#endif

