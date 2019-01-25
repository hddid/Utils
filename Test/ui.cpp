#include "ui.h"

using namespace cv;
using namespace std;

int main()
{
#if 0
	const int num = 500;
	char img_name [50];
	namedWindow(WINDOW_NAME);
	cvui::init(WINDOW_NAME);
	Mat BaseImg = Mat::zeros(Size(960, 480), CV_8UC3);

	bool use_img = true;
	bool use_camera = false;

	int count = 1;
	
	while (use_img)
	{
		cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");

		cvui::checkbox(BaseImg, 0, 25, "use_img", &use_img);
		cvui::checkbox(BaseImg, 100, 25, "use_camera", &use_camera);

		sprintf(img_name, "D:/workspace//Utils//Test/img//%d.jpg", count);

		Mat img = imread(img_name);
		resize(img, img, Size(640, 480));

		Mat ROI = BaseImg(Rect(320, 0, 640, 480));

		addWeighted(ROI, 0, img, 1, 0, ROI);

		if (cvui::button(BaseImg, 255, 450, 60, 30, "latter"))
		{
			count++;
		}

		if (cvui::button(BaseImg, 5, 450, 60, 30, "previous"))
		{
			count--;
		}
		cvui::printf(BaseImg, 130, 460, 0.4, 0xff0000, "now is:%d", count);

		if (img.empty())
		{
			cerr << "no img in file now" << endl;
			destroyAllWindows();
			use_img = false;
			use_camera = true;
			break;
		}

		cvui::update();
		imshow(WINDOW_NAME, BaseImg);
		waitKey(10);
		
	}

	while (use_camera)
	{
		
		VideoCapture cap(0);
		while (1)
		{

			Mat frame;
			cap >> frame;
			resize(frame, frame, Size(640, 480));

			Mat ROI = BaseImg(Rect(320, 0, 640, 480));
			addWeighted(ROI, 0, frame, 1, 0, ROI);
			imshow(WINDOW_NAME, BaseImg);
			waitKey(30);
		}

	}
	return 0;
#endif 

	bool use_img = true;
	bool use_camera = false;

	img(use_img);
	return 0;
}

int img(bool &use_img)
{
	const int num = 500;
	char img_name[50];
	cv::namedWindow(WINDOW_NAME);
	cvui::init(WINDOW_NAME);
	//Mat BaseImg = Mat::zeros(Size(960, 480), CV_8UC3);
	
	int count = 1;

	while (use_img)
	{
#if 0
		for (int i = 0;i<320;++i)
		{
			uchar *p_Base = BaseImg.ptr<uchar>(i);
			for (int j = 0; j < 480; j++)
			{
				p_Base[j] = 0;
			}
		}
#endif
		cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
		cvui::checkbox(BaseImg, 0, 25, "use_img", &use_img);
		cvui::checkbox(BaseImg, 100, 25, "use_camera", &use_camera);

		sprintf(img_name, "D:/workspace//Utils//Test/img//%d.jpg", count);

		Mat img = imread(img_name);
		resize(img, img, Size(640, 480));

		Mat ROI = BaseImg(Rect(320, 0, 640, 480));

		addWeighted(ROI, 0, img, 1, 0, ROI);

		if (cvui::button(BaseImg, 255, 450, 60, 30, "latter"))
		{
			count++;
		}

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
		while (use_camera)
		{
			use_img = false;
			use_camera = true;
			camera(use_camera);
		}
	}
	return 0;
}

int camera(bool &use_camera)
{
	while (use_camera)
	{
		//use_img = false;
		VideoCapture cap(0);
		bool open_camera = true;
		while (open_camera)
		{
#if 0
			for (int i = 0; i < 320; ++i)
			{
				uchar *p_Base = BaseImg.ptr<uchar>(i);
				for (int j = 0; j < 480; j++)
				{
					p_Base[j] = 0;
				}
			}
#endif
			cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
			cvui::checkbox(BaseImg, 0, 25, "use_img", &use_img);
			cvui::checkbox(BaseImg, 100, 25, "use_camera", &use_camera);

			Mat frame;
			cap >> frame;
			resize(frame, frame, Size(640, 480));

			Mat ROI = BaseImg(Rect(320, 0, 640, 480));
			addWeighted(ROI, 0, frame, 1, 0, ROI);
			cv::imshow(WINDOW_NAME, BaseImg);
			cv::waitKey(30);

			while (!use_camera)
			{
				open_camera = false;
				use_img = true;
				img(use_img);
				break;
			}

		}

	}
	return 0;
}

