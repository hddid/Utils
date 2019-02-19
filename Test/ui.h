#pragma once
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"

#define CVUI_IMPLEMENTATION
#include "cvui/cvui.h"

#define WINDOW_NAME "CVUI"

bool use_img = true;
bool use_camera = false;

int img(bool &use_img);
int camera(bool &use_camera);

//*****************************************img*****************************************
bool whitebalance = false;

bool Contrast = false;
bool Bright = false;

//�Աȶ�
int g_nContrastValue;

//����
int g_nBrightValue;

//Wavelevel
int g_nlevel;

//OilPaint
int g_ntemplateSize;
int g_nbucketSize;

//*****************************************camera*****************************************
bool CameraFilter = false;
bool SkinDetector = false;

//CameraFilter
bool Cartoon = false;
bool Nostalgic = false;
bool Wave = false;
bool OilPaint = false;

//SkinDetector
bool rgbcolor = false;
bool ellipseskin = false;
bool ycrcbotusskin = false;
bool ycrcbskin = false;
bool hsvskin = false;

Mat BaseImg = Mat::zeros(Size(960, 480), CV_8UC3);