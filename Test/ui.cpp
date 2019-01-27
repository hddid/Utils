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

	while (use_img)
	{
		cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
		cvui::checkbox(BaseImg, 0, 25, "use_img", &use_img);
		//cout << "img_while_use_img" << use_img << endl;
		cvui::checkbox(BaseImg, 100, 25, "use_camera", &use_camera);
		//cout << "img_while_use_camera" << endl;
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
	while (use_camera)
	{
		VideoCapture cap(0);	
		bool open_camera = true;
		while (open_camera)
		{
			cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
			cvui::checkbox(BaseImg, 0, 25, "use_img", &use_img);
			//cout << "camera_while_use_img" << use_img << endl;
			cvui::checkbox(BaseImg, 100, 25, "use_camera", &use_camera);
			//cout << "camera_while_use_camera" << use_camera << endl;
			Mat frame;
			cap >> frame;
			
			resize(frame, frame, Size(640, 480));

			bool use_cartoon = false;
			cvui::checkbox(BaseImg, 200, 25, "use_cartoon", &use_cartoon);

			if (use_cartoon == true)
			{
				CartoonFilter(frame);
			}
			//cout << "camera_while_use_cartoon" << use_cartoon << endl;
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

