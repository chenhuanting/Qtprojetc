
#ifndef _HKCAMERA_H
#define _HKCAMERA_H
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <windows.h>
#include <HCNetSDK.h>
/*#include "PlayM4.h"*/
#include <plaympeg4.h>
#include <opencv2\opencv.hpp>
#include <time.h>
//#include "global.h"
//#include "readCamera.h"

#define USECOLOR 1

using namespace cv;
using namespace std;
void yv12toYUV(char *outYuv, char *inYv12, int width, int height, int widthStep);
void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);
void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
void CALLBACK DecCBFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);
void initHkcamera();
void closeHkCamera();
void getMat(Mat &images);
#endif