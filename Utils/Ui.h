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

int UI_Img(bool &use_img);
int UI_Camera(bool &use_camera);

bool CameraFilter = false;
bool SkinDetector = false;

bool rgbcolor = false;
bool ellipseskin = false;
bool ycrcbotusskin = false;
bool ycrcbskin = false;
bool hsvskin = false;

Mat BaseImg = Mat::zeros(Size(960, 480), CV_8UC3);