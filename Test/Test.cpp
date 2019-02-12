/***********************************
 *
 * file Test.cpp
 * ingroup GroupName
 * TODO: long description
 * author Haoyu_Zeng
 * version 1.0
 * date  2018/09/05 15:41
 * E-mail: 1150566379@qq.com
 *
 ***********************************/
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <opencv2/opencv.hpp>

#include "Utils.h"

#include "Ui.h"

using namespace std;
using namespace cv;

#if 0
//int main()
//{
//	cv::Mat src, grey;
//	src = imread("1.jpg");
//	string ver = GetCurrentVersion();
//	cout << ver << endl;
//
//	if (RET_ERROR_OK == ConvertRGB2Gray(src, grey))
//	{
//		imshow("grey", grey);
//	}
//	imshow("src", src);
//	int ret = waitKey(0);
//
//	return 0;
//
//}

//int main()
//{
//	Mat src;
//	src = imread("1.jpg");
//	string ver = GetCurrentVersion();
//	cout << ver << endl;
//
//	if (RET_ERROR_OK == FastColorReduce(src, 64))
//	{
//		imshow("src", src);
//	}
//	int ret = waitKey(0);
//	return RET_ERROR_OK;
//}

//int main()
//{
//
//	Mat img, new_img;
//	double alpha;
//	int beta;
//	img = imread("1.jpg");
//	cout << "please input the alpha" << endl;
//	cin >> alpha;
//	cout << "please input the beta" << endl;
//	cin >> beta;
//
//	if (RET_ERROR_OK == ContrastAndBright(img, new_img, alpha, beta))
//	{
//		imshow("new_img", new_img);
//	}
//	int ret = waitKey(0);
//	return 0;
//}

//int main()
//{
//	string video, pic;
//	double totalnum = 0;
//
//	cout << "输入视频所在地址" << endl;
//	cin >> video;
//	cout << "输入图片存放地址" << endl;
//	cin >> pic;
//
//
//	if (RET_ERROR_OK == VideoToPic(video, pic, totalnum))
//	{
//		cout << "totalframenumber" << totalnum << endl; 
//	}
//	return 0;
//}

//int main()
//{
//	string pic, video;
//	int height, width;
//	cout << "input pic path" << endl;
//	cin >> pic;
//	cout << "input video path" << endl;
//	cin >> video;
//	cout << "input height" << endl;
//	cin >> height;
//	cout << "input width" << endl;
//	cin >> width;
//	if (RET_ERROR_OK == PicToVideo(pic, video, height, width))
//	{
//		cout << "生成完毕" << endl;
//	}
//	system("pause");
//}

//int main()
//{
//	Mat img1 = imread("8.jpg");
//	Mat img2 = imread("9.jpg");
//
//	Mat result = Mat::zeros(img1.size(), img1.type());
//	if (RET_ERROR_OK == PicDivPic(img1, img2, result))
//	{
//		imshow("result", result);
//	}
//	waitKey(0);
//	return 0;
//}

//int main()
//{
//	//Mat img = imread("3.jpg");
//	Mat dst;
//	Mat img;
//	VideoCapture cap(0);
//	while (1)
//	{
//		cap >> img;
//		if (RET_ERROR_OK == HSVSkin(img, dst))
//		{
//			HSVSkin(img, dst);
//			imshow("dst", dst);
//			waitKey(30);
//		}
//	}
//	return 0;
//}


//int main()
//{
//	Mat img = imread("1.jpg");
//	if (RET_ERROR_OK == AddSaltPepperNoise(img))
//	{
//		imshow("img", img);
//		waitKey(0);
//	}
//	return 0;
//}

//int main()
//{
//	VideoCapture cap(0);
//	while (1)
//	{
//		Mat frame;
//		cap >> frame;
//
//		if (RET_ERROR_OK == CartoonFilter(frame))
//		{
//			imshow("img", frame);
//		}
//		char c = waitKey(30);
//		if (c == 27)
//		{
//			break;
//		}
//	}
//	return 0;
//}


//
//int main()
//{
//	Mat img = imread("11.jpg");
//	
//	if (RET_ERROR_OK == WhiteBalance(img))
//	{
//		imshow("dst", img);
//	}
//	waitKey(0);
//	return 0;
//}

#endif

int main()
{
	UI_Img(use_img);
	return 0;

}