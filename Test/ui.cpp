#include "ui.h"

using namespace cv;
using namespace std;

int main()
{
	img(use_img);
	//camera(use_camera);
	return 0;
}

int img(bool &use_img)
{
	const int num = 500;
	char img_name[50];
	cv::namedWindow(WINDOW_NAME);
	cvui::init(WINDOW_NAME);
	
	int count = 1;
	bool whitebalance = false;
	while (use_img)
	{
		//img按键窗口
		cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
		cvui::checkbox(BaseImg, 50, 25, "img", &use_img);	
		cvui::checkbox(BaseImg, 200, 25, "camera", &use_camera);
		cvui::printf(BaseImg, 0, 40, "*************************************************");
		cvui::checkbox(BaseImg, 0, 70, "whitebalance", &whitebalance);

		sprintf(img_name, "D://workspace//Utils//Test//img//%d.jpg", count);

		Mat img = imread(img_name);
		if (whitebalance == true)
			WhiteBalance(img);
		resize(img, img, Size(640, 480));

		Mat ROI = BaseImg(Rect(320, 0, 640, 480));

		addWeighted(ROI, 0, img, 1, 0, ROI);
		//下一张图片
		if (cvui::button(BaseImg, 255, 450, 60, 30, "latter"))
		{
			count++;
		}
		//上一张图片
		if (cvui::button(BaseImg, 5, 450, 60, 30, "previous"))
		{
			count--;
		}
		cvui::printf(BaseImg, 130, 460, 0.4, 0xff0000, "now is:%d", count);
		
		if (img.empty())
		{
			cerr << "no img in file now" << endl;
			destroyAllWindows();
			break;
		}

		cvui::update();
		cv::imshow(WINDOW_NAME, BaseImg);
		cv::waitKey(10);
		if (use_camera && !use_img)
		{
			img.release();
			camera(use_camera);
			break;
		}
	}
	return 0;
}

int camera(bool &use_camera)
{
	use_img = false;
	while (use_camera)
	{
		VideoCapture cap(0);	
		bool open_camera = true;
		while (open_camera)
		{
			cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
			cvui::checkbox(BaseImg, 0, 25, "img", &use_img);
			cvui::checkbox(BaseImg, 100, 25, "camera", &use_camera);
			Mat frame;
			cap >> frame;
			
			resize(frame, frame, Size(640, 480));

			bool cartoon = false;
			cvui::checkbox(BaseImg, 200, 25, "cartoon", &cartoon);

			if (cartoon == true)
			{
				CartoonFilter(frame);
			}

			Mat ROI = BaseImg(Rect(320, 0, 640, 480));
			addWeighted(ROI, 0, frame, 1, 0, ROI);
			
			cv::imshow(WINDOW_NAME, BaseImg);
			
			cv::waitKey(30);
			
			if (!use_camera && use_img)
			{
				open_camera = false;
				//use_camera为false的时候关闭camera
				cap.release();				
				img(use_img);		
				cvui::update();
				
			}		
		}
	}
	return 0;
}

