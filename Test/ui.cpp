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

	while (use_img)
	{
		//img按键窗口
		cvui::window(BaseImg, 0, 0, 320, 480, "********************vision********************");
		cvui::checkbox(BaseImg, 50, 25, "img", &use_img);
		cvui::checkbox(BaseImg, 200, 25, "camera", &use_camera);
		cvui::printf(BaseImg, 0, 40, "*************************************************");
		cvui::printf(BaseImg, 0, 350, "*************************************************");
		cvui::printf(BaseImg, 0, 440, "*************************************************");

		cvui::checkbox(BaseImg, 0, 70, "Bright", &Bright);
		cvui::checkbox(BaseImg, 0, 110, "Contrast", &Contrast);
		cvui::checkbox(BaseImg, 0, 150, "Wave", &Wave);
		cvui::checkbox(BaseImg, 0, 190, "OilPaint", &OilPaint);

		cvui::checkbox(BaseImg, 0, 360, "whitebalance", &whitebalance);
		cvui::checkbox(BaseImg, 0, 380, "Cartoon", &Cartoon);
		cvui::checkbox(BaseImg, 0, 400, "Nostalgic", &Nostalgic);
		
		sprintf(img_name, "D://workspace//Utils//Test//img//%d.jpg", count);

		Mat img = imread(img_name);
		//equalizeHist(img, img);
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
		
		if (Cartoon == true)
			CartoonFilter(img);
		if (Nostalgic == true)
			NostalgicFilter(img);
		if (Wave == true)
		{
			cvui::trackbar(BaseImg, 70, 135, 250, &g_nlevel, 0, 100);
			WaveFilter(img, g_nlevel);
		}
		if (OilPaint == true)
		{	
			//速度太慢，去掉滑动条
			//cvui::trackbar(BaseImg, 70, 175, 250, &g_ntemplateSize, 0, 100);
			//cvui::trackbar(BaseImg, 70, 215, 250, &g_nbucketSize, 0, 100);
			OilPaintFilter(img, 4, 8);
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
				cvui::checkbox(BaseImg, 10, 150, "Wave", &Wave);
				cvui::checkbox(BaseImg, 10, 180, "OilPaint", &OilPaint);
				if (Cartoon == true)
					CartoonFilter(frame);
				if (Nostalgic == true)
					NostalgicFilter(frame);
				if (Wave == true)
				{
					cvui::trackbar(BaseImg, 70, 135, 250, &g_nlevel, 0, 100);
					WaveFilter(frame, g_nlevel);
				}
				if(OilPaint == true)
				{
					//速度太慢，去掉滑动条
					//cvui::trackbar(BaseImg, 70, 200, 250, &g_ntemplateSize, 0, 100);
					//cvui::trackbar(BaseImg, 70, 250, 250, &g_nbucketSize, 0, 100);
					//整个算法都很慢，用做油画滤镜不现实
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

