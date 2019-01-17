#include "MarkerDetect.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

//VideoCapture MarkerDetect::m_vid = VideoCapture(1);
MarkerDetect::MarkerDetect(const std::string & camCalFileName, float arucoSquareDimension, int markerID)
	:m_arucoSquareDimension(arucoSquareDimension), m_markerID(markerID), m_ready(false)
{
	m_markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
	updateCameraCalibration(camCalFileName);
	initHkcamera();
	getMat(imagesSize);
}

MarkerDetect::~MarkerDetect()
{
	closeHkCamera();
}

void MarkerDetect::updateCameraCalibration(const std::string & filename)
{
	ifstream inStream(filename);
	if (!inStream)
	{
        //对配置文件读取错误进行处理
		return;
	}

	uint16_t rows;
	uint16_t columns;
	inStream >> rows;
	inStream >> columns;

	this->m_cameraMatrix = Mat(Size(columns, rows), CV_64F);
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			double read = 0.0f;
			inStream >> read;
			this->m_cameraMatrix.at<double>(r, c) = read;
			cout << m_cameraMatrix.at<double>(r, c) << endl;
		}
	}

	inStream >> rows;
	inStream >> columns;

	this->m_distanceCoefficients = Mat::zeros(rows, columns, CV_64F);
	for (int r = 0; r < rows; r++) 
	{
		for (int c = 0; c < columns; c++) 
		{
			double read = 0.0f;
			inStream >> read;
			this->m_distanceCoefficients.at<double>(r, c) = read;
			cout << m_distanceCoefficients.at<double>(r, c) << endl;
		}
	}
	inStream.close();
}

bool MarkerDetect::updateMarker()
{
	//Mat frame;

	
	//getMat(frame );
	if (imagesSize.empty())
	{
		return false;

	}

	
	/*
	if (!m_vid.read(frame))
	{
		return false;
	}
	*/
	vector<Vec3d> rotationVectors;
	vector<Vec3d> translationVectors;
	vector<vector<Point2f>> markerCorners;
	vector<int> markerIds;

    aruco::detectMarkers(imagesSize, m_markerDictionary, markerCorners, markerIds);
    aruco::estimatePoseSingleMarkers(markerCorners, m_arucoSquareDimension, m_cameraMatrix, m_distanceCoefficients, rotationVectors, translationVectors);

	if (markerIds.size() != 0)
	{
		//暂时处理为只认第一个检测到的marker
        m_lastRotationVectors = rotationVectors[0];
        m_lastTranslationVectors = translationVectors[0];
        m_lastMarkerCorner = markerCorners[0];
        aruco::drawAxis(imagesSize, m_cameraMatrix, m_distanceCoefficients, rotationVectors[0], translationVectors[0], m_arucoSquareDimension/2.0f);
        m_ready = true;
	}

	imagesSize.copyTo(m_lastFrame);

	return m_ready;
}

const cv::Vec3d & MarkerDetect::lastRotationVectors()
{
	m_ready = false;
	return m_lastRotationVectors;
}

const cv::Vec3d & MarkerDetect::lastTranslationVectors()
{
	m_ready = false;
	return m_lastTranslationVectors;
}

const std::vector<cv::Point2f>& MarkerDetect::lastMarkerCorners()
{
	m_ready = false;
	return m_lastMarkerCorner;
}

Mat & MarkerDetect::lastFrame()
{
	return m_lastFrame;
}

const cv::Mat & MarkerDetect::cameraMatrix()
{
	return m_cameraMatrix;
}

cv::Size MarkerDetect::videoSize()
{
    //return Size(int(m_vid.get(CAP_PROP_FRAME_WIDTH)), int(m_vid.get(CAP_PROP_FRAME_HEIGHT)));
	return Size(int(imagesSize.cols), int(imagesSize.rows));
}

