#include "Ui.h"
#include "ExtendWindow.h"
using namespace cv;
using namespace std;

int main()
{
	while (true)
	{
		if (!use_img && use_camera)
		{
			Camera(use_camera);
		}
		else
		{
			use_img = true;
			use_camera = false;
			Img(use_img);
		}
	}
	return 0;
}

int Img(bool &use_img)
{
	const int num = 500;
	char img_name[50];
	cvui::init(WINDOW_NAME);

	int count = 1;
	
	while (use_img)
	{
		if(!button_window && trackbar_window)
		{
			TrackbarWindow(trackbar_window);
		}
		else
		{
			trackbar_window = false;
			button_window = true;
			ButtonWindow(button_window);
		}
		
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

		//修改图片大小，否则会覆盖按键的位置
		resize(img, img, Size(640, 480));

		if (Contrast == true || Bright == true)
		{
			cvui::trackbar(BaseImg, 70, 50, 250, &g_nBrightValue, 0, 100);
			cvui::trackbar(BaseImg, 70, 95, 250, &g_nContrastValue, 0, 100);
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
		
		if (cartoon == true)
			CartoonFilter(img);
		if (nostalgic == true)
			NostalgicFilter(img);
		if (wave == true)
		{
			cvui::trackbar(BaseImg, 70, 135, 250, &g_nlevel, 0, 100);
			WaveFilter(img, g_nlevel);
		}
		if (oilpaint == true)
		{	
			//速度太慢，去掉滑动条
			//cvui::trackbar(BaseImg, 70, 175, 250, &g_ntemplateSize, 0, 100);
			//cvui::trackbar(BaseImg, 70, 215, 250, &g_nbucketSize, 0, 100);
			OilPaintFilter(img, 4, 8);
		}
		
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

		if(!use_img)
		{
			img.release();
			use_camera = true;
		}
	}
	return 0;
}

int Camera(bool &use_camera)
{
	while (use_camera)
	{
		VideoCapture cap(0);
		bool open_camera = true;

		cvui::init(WINDOW_NAME);
		while (open_camera)
		{
			cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
			//cvui::checkbox(BaseImg, 50, 25, "Img", &use_img);
			cvui::checkbox(BaseImg, 100, 25, "camera", &use_camera);
			cvui::printf(BaseImg, 0, 40, "*************************************************");

			cvui::checkbox(BaseImg, 5, 60, "SkinDetector", &skindetector);
			cvui::checkbox(BaseImg, 110, 60, "CameraFilter", &camerafilter);
			cvui::printf(BaseImg, 0, 80, "*************************************************");
			
			Mat frame;
			cap >> frame;
			
			//修改一下图片大小,否则会覆盖按键的位置
			resize(frame, frame, Size(640, 480));

			while (skindetector == true && camerafilter == false)
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

			while (camerafilter == true && skindetector == false)
			{
				cvui::checkbox(BaseImg, 10, 90, "Cartoon", &cartoon);
				cvui::checkbox(BaseImg, 10, 120, "Nostalgic", &nostalgic);
				cvui::checkbox(BaseImg, 10, 150, "Wave", &wave);
				cvui::checkbox(BaseImg, 10, 180, "OilPaint", &oilpaint);
				if (cartoon == true)
					CartoonFilter(frame);
				if (nostalgic == true)
					NostalgicFilter(frame);
				if (wave == true)
				{
					cvui::trackbar(BaseImg, 70, 135, 250, &g_nlevel, 0, 100);
					WaveFilter(frame, g_nlevel);
				}
				if(oilpaint == true)
				{
					//速度太慢，去掉滑动条
					//cvui::trackbar(BaseImg, 70, 200, 250, &g_ntemplateSize, 0, 100);
					//cvui::trackbar(BaseImg, 70, 250, 250, &g_nbucketSize, 0, 100);
					//速度慢，去掉
					OilPaintFilter(frame, 4, 8);
				}
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

			if(!use_camera)
			{
				open_camera = false;
				use_img = true;
				cap.release();
			}
		}
		break;
	}
	return 0;
}

int TrackbarWindow(bool &trackbar_window)
{
	cvui::window(BaseImg, 0, 0, 320, 480, "********************TrackbarWindow********************");

	cvui::checkbox(BaseImg, 100, 25, "Img", &use_img);
	//cvui::checkbox(BaseImg, 200, 25, "Camera", &use_camera);
	//cout << "TrackbarWindow use_camera  " << use_camera << endl;
	cvui::printf(BaseImg, 0, 40, "*************************************************");

	cvui::checkbox(BaseImg, 0, 70, "Bright", &Bright);
	cvui::checkbox(BaseImg, 0, 110, "Contrast", &Contrast);
	cvui::checkbox(BaseImg, 0, 150, "Wave", &wave);
	cvui::checkbox(BaseImg, 0, 190, "OilPaint", &oilpaint);

	cvui::checkbox(BaseImg, 0, 250, "Trackbar_Window", &trackbar_window);
	
	if (!trackbar_window)
	{
		button_window = true;
	}
	return 0;
}

int ButtonWindow(bool &button_window)
{
	cvui::window(BaseImg, 0, 0, 320, 480, "********************ButtonWindow********************");

	cvui::checkbox(BaseImg, 100, 25, "Img", &use_img);
	//cvui::checkbox(BaseImg, 200, 25, "Camera", &use_camera);
	//cout << "ButtonWindow use_camera  " << use_camera << endl;
	cvui::printf(BaseImg, 0, 40, "*************************************************");

	cvui::checkbox(BaseImg, 0, 70, "WhiteBalance", &whitebalance);
	cvui::checkbox(BaseImg, 0, 110, "Cartoon", &cartoon);
	cvui::checkbox(BaseImg, 0, 150, "Nostalgic", &nostalgic);

	cvui::checkbox(BaseImg, 200, 400, "Button_Window", &button_window);

	if (!button_window)
	{
		trackbar_window = true;
	}
	return 0;
	
}