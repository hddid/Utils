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
int main()
{
	cv::Mat src, grey;
	src = imread("C:\\Users\\Robin\\Desktop\\map-00003.bmp");

	//if (RET_ERROR_OK == ConvertRGB2Gray(src, grey))
	//{
	//	imshow("grey", grey);
	//}

	const char *txtname = "C:\\Users\\Robin\\Desktop\\test.txt";
	imwrite("C:\\Users\\Robin\\Desktop\\map.jpg", src);
	Mat img = imread("C:\\Users\\Robin\\Desktop\\map.jpg");
	FILE *temp;
	if((temp = fopen(txtname,"wb"))==NULL)
	{
		cout << "read file fail" << endl;
		return 0;
	}
	for(int i = 0;i<img.rows;i++)
	{
		for(int j =0;j<img.cols;j++)
		{
			fprintf(temp, "%d ", img.at<Vec3b>(i, j)[0]);
			fprintf(temp, "%d ", img.at<Vec3b>(i, j)[1]);
			fprintf(temp, "%d   ", img.at<Vec3b>(i, j)[2]);
			
		}
		fprintf(temp, "\n");
	}
	fclose(temp);
	imwrite("C:\\Users\\Robin\\Desktop\\map.bmp", img);
	int ret = waitKey(0);

	return 0;

}

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

//int main()
//{
//	Mat img = imread("14.jpg");
//	//imshow("before", img);
//	double time = static_cast<double>(getTickCount());
//	if (RET_ERROR_OK == OilPaintFilter(img,4,8))
//	{
//		time = ((double)getTickCount() - time) / getTickFrequency();
//		cout << "time" << time << endl;
//		imshow("img", img);
//		imwrite("../ss.jpg", img);
//	}
//	waitKey(0);
//	return 0;
//
//}
#if 0
int main()
{
	Mat src = imread("./w.jpg");
	if(src.empty())
	{
		printf("cound not load image\n");
		return -1;
	}
	imshow("原图", src);

	Mat dst, gray, binary;

	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(src, dst, MORPH_GRADIENT, se);
	imshow("dst", dst);

	cvtColor(dst, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	se = getStructuringElement(MORPH_RECT, Size(1, 5), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_DILATE, se);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (size_t c = 0; c < contours.size(); c++) {
		Rect rect = boundingRect(contours[c]);
		double area = contourArea(contours[c]);
		if (area < 200)
			continue;
		int h = rect.height;
		int w = rect.width;
		if (h > (3 * w) || h < 20)
			continue;
		rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);
	}
	imshow("result", src);
	waitKey(0);
	return 0;
}

#endif

int main()
{
	KNN();
	return 0;
}