#include "RobotVehicle.h"
#include <iostream>

using namespace std;
using namespace cv;

RobotVehicle::RobotVehicle(const cv::Mat & cameraMatrix, int markerID)
{
	cameraMatrix.copyTo(m_cameraMatrix);
	setTarget(Point2f(0.0f, 0.0f));
}

RobotVehicle::~RobotVehicle()
{
}

void RobotVehicle::setMarkerID(int markerID)
{
	m_markerID = markerID;
}

void RobotVehicle::setTarget(const cv::Point2d & target)
{
	m_lastTarget.x = target.x;
	m_lastTarget.y = target.y;
	m_lastTarget.z = 1.0f;
}

cv::Point3f RobotVehicle::updateDeviation(const std::vector<cv::Point2f>& markerCorners, const cv::Vec3d & rvector, const cv::Vec3d & tvector)
{
	Mat rotationMatrix(3, 3, cv::DataType<double>::type);
	Mat rotationVector = Mat(3, 1, cv::DataType<double>::type);
	rotationVector.at<double>(0, 0) = rvector[0];
	rotationVector.at<double>(1, 0) = rvector[1];
	rotationVector.at<double>(2, 0) = rvector[2];
	Mat invRotationMatrix;
	Rodrigues(rotationVector, rotationMatrix);
	transpose(rotationMatrix, invRotationMatrix);

	Mat targetMatrix = Mat::ones(3, 1, cv::DataType<double>::type);
	targetMatrix.at<double>(0, 0) = this->m_lastTarget.x;
	targetMatrix.at<double>(1, 0) = this->m_lastTarget.y;
	Mat translationVector = Mat(3, 1, cv::DataType<double>::type);
	translationVector.at<double>(0, 0) = tvector[0];
	translationVector.at<double>(1, 0) = tvector[1];
	translationVector.at<double>(2, 0) = tvector[2];
	Mat tempMat, tempMat2;
	double s;

	tempMat = invRotationMatrix * this->m_cameraMatrix.inv() * targetMatrix;
	tempMat2 = invRotationMatrix * translationVector;
	s = 0 + tempMat2.at<double>(2, 0);
	s /= tempMat.at<double>(2, 0);

	//成功将目标点从摄像头坐标系转换成marker坐标系
	Mat markerCoorPoint = invRotationMatrix * (s * this->m_cameraMatrix.inv() * targetMatrix - translationVector);
	Point2f realPoint(markerCoorPoint.at<double>(0, 0), markerCoorPoint.at<double>(1, 0));

	//cout << "RVector:" << rvector << endl;
	//cout << "TVector:" << tvector << endl;
	//cout << "RealPoint:" << realPoint << endl;

	Point2f markerYVec = markerCorners[1] - markerCorners[2];
	float theta = fastAtan2(markerYVec.y, markerYVec.x);

	this->m_lastDeviation.x = sqrt(realPoint.dot(realPoint));
	this->m_lastDeviation.y = fastAtan2(realPoint.x, realPoint.y)>180 ?
							  fastAtan2(realPoint.x, realPoint.y) - 360 :
							  fastAtan2(realPoint.x, realPoint.y);
	this->m_lastDeviation.z = 360 - theta + this->m_lastDeviation.y;

	//cout << this->m_lastDeviation.x << endl;
	//cout << this->m_lastDeviation.y << endl;
	//cout << this->m_lastDeviation.x << endl;

	//更新marker的中心坐标
	cv::Point2f tmp;
	for (auto point : markerCorners) {
		tmp += point;
	}
	tmp = tmp / 4;
	if (tmp.x - m_self.x > 0.5 || m_self.x - tmp.x > 0.5) {
		m_self.x = tmp.x;
	}
	if (tmp.y - m_self.y > 0.5 || m_self.y - tmp.y > 0.5) {
		m_self.y = tmp.y;
	}

	return this->m_lastDeviation;
}

const cv::Point2f & RobotVehicle::position()
{
	return m_self;
}
