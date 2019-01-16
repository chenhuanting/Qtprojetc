#ifndef __ROBOT_VEHICLE_H
#define __ROBOT_VEHICLE_H

#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"

class RobotVehicle
{
public:
	RobotVehicle(const cv::Mat &cameraMatrix, int markerID=0);
	~RobotVehicle();
	
	void setMarkerID(int markerID);
	void setTarget(const cv::Point2d & target);

	cv::Point3f updateDeviation(const std::vector<cv::Point2f> & markerCorners, const cv::Vec3d & rvector, const cv::Vec3d & tvector);
	const cv::Point2f& position();
protected:
	cv::Mat m_cameraMatrix;
	//Target是基于摄像头坐标系的坐标，即图像坐标
	cv::Point3d m_lastTarget;
	//Deviation.x是RobotVehicle与Target的误差位移(单位m)
	//Deviation.y是RobotVehicle与Target的误差角度(单位°)
	//Deviation.z是RobotVehicle当前所处的方向(单位是°)
	cv::Point3f m_lastDeviation;
	//标记RobotVehicle的MarkerID
	int m_markerID;
	//marker基于摄像头坐标系的中心坐标
	cv::Point2f m_self;

private:

};

#endif

