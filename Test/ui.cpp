#include "Ui.h"

using namespace cv;
using namespace std;

int main()
{
	img(use_img);
	return 0;
}

int img(bool &use_img)
{
	const int num = 500;
	char img_name[50];
	cvui::init(WINDOW_NAME);

	int count = 1;
	//bool whitebalance = false;
	while (use_img)
	{
		//img按键窗口
		cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
		cvui::checkbox(BaseImg, 50, 25, "img", &use_img);
		cvui::checkbox(BaseImg, 200, 25, "camera", &use_camera);
		cvui::printf(BaseImg, 0, 40, "*************************************************");

		cvui::checkbox(BaseImg, 0, 70, "whitebalance", &whitebalance);
		cvui::checkbox(BaseImg, 0, 100, "contrastAndbright", &contrastAndbright);
		

		sprintf(img_name, "D://workspace//Utils//Test//img//%d.jpg", count);

		Mat img = imread(img_name);

		if (img.empty())
		{
			cerr << "no img in file now" << endl;
			waitKey(1000);
			destroyAllWindows();
			break;
		}
		if (whitebalance == true)
			WhiteBalance(img);

		resize(img, img, Size(640, 480));

		if (contrastAndbright == true)
		{
			cvui::trackbar(BaseImg, 0, 130, 220, &g_nBrightValue, 5, 150);
			cvui::printf(BaseImg, 220, 150, "BrightValue");
			cvui::trackbar(BaseImg, 0, 190, 220, &g_nContrastValue, 5, 150);
			cvui::printf(BaseImg, 220, 210, "ContrastValue");

			for (int i = 0; i <= img.rows; i++)		
			{
				for (int j = 0; j <= img.cols; j++)			
				{
					img.at<Vec3b>(i, j)[0] = saturate_cast<uchar>((g_nContrastValue * 0.01)*img.at<Vec3b>(i, j)[0] + g_nBrightValue);
					img.at<Vec3b>(i, j)[1] = saturate_cast<uchar>((g_nContrastValue * 0.01)*img.at<Vec3b>(i, j)[1] + g_nBrightValue);
					img.at<Vec3b>(i, j)[2] = saturate_cast<uchar>((g_nContrastValue * 0.01)*img.at<Vec3b>(i, j)[2] + g_nBrightValue);

				}
			}
		}
		//resize(img, img, Size(640, 480));
		
		//Mat ROI = BaseImg(Rect(320, 0, 640, 480));
		//addWeighted(ROI, 0, img, 1, 0, ROI);
		//替代上面两行代码
		cvui::image(BaseImg, 320, 0, img);
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

		cvui::update();
		cv::imshow(WINDOW_NAME, BaseImg);

		cv::waitKey(10);
		if (use_camera && !use_img)
		{
			img.release();
			camera(use_camera);
			//break;
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

		cvui::init(WINDOW_NAME);
		while (open_camera)
		{
			cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
			cvui::checkbox(BaseImg, 50, 25, "img", &use_img);
			cvui::checkbox(BaseImg, 200, 25, "camera", &use_camera);
			cvui::printf(BaseImg, 0, 40, "*************************************************");

			cvui::checkbox(BaseImg, 5, 60, "SkinDetector", &SkinDetector);
			cvui::checkbox(BaseImg, 110, 60, "CameraFilter", &CameraFilter);
			cvui::printf(BaseImg, 0, 80, "*************************************************");
			
			Mat frame;
			cap >> frame;
			resize(frame, frame, Size(640, 480));

			//bool puppet  = false;
			//puppet = (SkinDetector == true && CameraFilter == false);		
			while (SkinDetector == true && CameraFilter == false)
			{
				cvui::checkbox(BaseImg, 20, 90, "RGBSkin", &rgbcolor);
				cvui::checkbox(BaseImg, 20, 110, "EleSkin", &ellipseskin);
				cvui::checkbox(BaseImg, 190, 90, "YOSkin", &ycrcbotusskin);
				cvui::checkbox(BaseImg, 100, 90, "YCrSkin", &ycrcbskin);
				cvui::checkbox(BaseImg, 100, 110, "HSVSkin", &hsvskin);

				if (rgbcolor == true)
					RGBSkin(frame);
				if (ellipseskin == true)
					EllipseSkin(frame);
				if (ycrcbotusskin == true)
					YCrCbOtusSkin(frame);
				if (ycrcbskin == true)
					YCrCbSkin(frame);
				if (hsvskin == true)
					HSVSkin(frame);
				break;
			}

			while (CameraFilter == true && SkinDetector == false)
			{
				cvui::checkbox(BaseImg, 10, 90, "Cartoon", &Cartoon);
				cvui::checkbox(BaseImg, 10, 120, "Nostalgic", &Nostalgic);
				if (Cartoon == true)
					CartoonFilter(frame);
				if (Nostalgic == true)
					NostalgicFilter(frame);
				break;
			}

			cvui::update();
		
			//添加摄像头遮挡
			/*Mat mask = Mat::zeros(Size(640, 480), CV_8UC3);
			frame = mask.clone();*/

			//Mat ROI = BaseImg(Rect(320, 0, 640, 480));
			//addWeighted(ROI, 0, frame, 1, 0, ROI);
			//使用下面代码替代上面两行
			cvui::image(BaseImg, 320, 0, frame);

			cv::imshow(WINDOW_NAME, BaseImg);
			cv::waitKey(30);

			if (!use_camera && use_img)
			{
				open_camera = false;
				//use_camera为false的时候关闭camera
				cap.release();
				img(use_img);
			}
		}
		break;
	}
	return 0;
}

