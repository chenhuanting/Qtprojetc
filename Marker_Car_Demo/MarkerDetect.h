#ifndef __MARKER_DETECT_H
#define __MARKER_DETECT_H

#include <string>
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/aruco.hpp"
#include "HkCamera.h"
class MarkerDetect
{
public:
	MarkerDetect(const std::string & camCalFileName, float arucoSquareDimension, int markerID=0);
	~MarkerDetect();

	void updateCameraCalibration(const std::string & filename);
	bool updateMarker();

	const cv::Vec3d& lastRotationVectors();
	const cv::Vec3d& lastTranslationVectors();
	const cv::Mat& cameraMatrix();
	const std::vector<cv::Point2f>& lastMarkerCorners();
	cv::Mat& lastFrame();
    cv::Size videoSize();
protected:
	static cv::VideoCapture m_vid;
	cv::Mat imagesSize;
	cv::Ptr<cv::aruco::Dictionary> m_markerDictionary;
	cv::Mat m_cameraMatrix;
	cv::Mat m_distanceCoefficients;
	float m_arucoSquareDimension;
	int m_markerID;

	cv::Mat m_lastFrame;
	std::vector<cv::Point2f> m_lastMarkerCorner;
	cv::Vec3d m_lastRotationVectors;
	cv::Vec3d m_lastTranslationVectors;
	bool m_ready;
};

#endif
