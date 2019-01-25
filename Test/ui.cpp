#include <iostream>
#include <opencv2/opencv.hpp>

#include "Utils.h"
#include <string>

#define CVUI_IMPLEMENTATION
#include "cvui/cvui.h"

using namespace cv;
using namespace std;

#define WINDOW_NAME "CVUI"

int main()
{
	const int num = 500;
	char img_name[50];
	namedWindow(WINDOW_NAME);
	cvui::init(WINDOW_NAME);
	Mat BaseImg = Mat::zeros(Size(960, 480), CV_8UC3);

	int count = 1;

	while (true)
	{
		sprintf(img_name, "D:/workspace//Utils//Test/img//%d.jpg", count);
		//cout << "img_name" << img_name << endl;

		Mat img = imread(img_name);
		resize(img, img, Size(640, 480));

		Mat ROI = BaseImg(Rect(320, 0, 640, 480));

		//img.copyTo(ROI, img);
		addWeighted(ROI, 0, img, 1, 0, ROI);

		cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
		
		if (cvui::button(BaseImg, 255, 450, 60, 30, "latter"))
		{
			count++;
		}

		if (cvui::button(BaseImg, 5, 450, 60, 30, "previous"))
		{
			count--;
		}
		cvui::printf(BaseImg, 130, 460, 0.4, 0xff0000, "now is:%d", count);
		if (img.empty()||count < 0)
		{
			cerr << "no img in file now" << endl;
			destroyAllWindows();
			break;
		}
		cvui::update();
		imshow(WINDOW_NAME, BaseImg);
		waitKey(10);
	}
	return 0;

}

//latter
//previous