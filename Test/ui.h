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

int Img(bool &use_img);
int Camera(bool &use_camera);

int TrackbarWindow(bool &Trackbar_Window);
int ButtonWindow(bool &Button_Window);

bool trackbar_window = false;
bool button_window = true;

//*****************************************img*****************************************
bool whitebalance = false;

bool Contrast = false;
bool Bright = false;

//对比度
int g_nContrastValue = 0;

//亮度
int g_nBrightValue = 0;

//Wavelevel
int g_nlevel = 0;

//OilPaint
int g_ntemplateSize = 0;
int g_nbucketSize = 0;

//*****************************************camera*****************************************
bool camerafilter = false;
bool skindetector = false;

//CameraFilter
bool cartoon = false;
bool nostalgic = false;
bool wave = false;
bool oilpaint = false;

//SkinDetector
bool rgbcolor = false;
bool ellipseskin = false;
bool ycrcbotusskin = false;
bool ycrcbskin = false;
bool hsvskin = false;

Mat BaseImg = Mat::zeros(Size(960, 480), CV_8UC3);