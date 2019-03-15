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

#include <stdio.h>
#include "cJSON.h"


int main()
{
	const char* version = cJSON_Version();
	printf("version:%s\n", version);
	FILE* file = fopen("C:\\Users\\Robin\\Desktop\\test.json", "r");
	if (NULL == file)
	{
		printf("load file fail!\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* tmpStr = (char*)malloc(size + 1);
	memset(tmpStr, 0, size + 1);
	size_t ret = fread(tmpStr, size, 1, file);
	tmpStr[size] = '\0';
	printf("ret = %d size = %ld str=%s\n", ret, size, tmpStr);

	cJSON* root = cJSON_Parse(tmpStr);
	cJSON* map_id = cJSON_GetObjectItem(root, "map_id");
	if (NULL != map_id)
		printf("mapid is %d\n", map_id->valueint);

	cJSON *rect = cJSON_GetObjectItem(root, "rect");
	if (NULL != rect)
	{
		if (cJSON_IsArray(rect))
		{
			int len = cJSON_GetArraySize(rect);
			for (int i = 0; i < len; i++)
			{
				cJSON* pos = cJSON_GetArrayItem(rect, i);
				printf("i=%d value = %d\n", i, pos->valueint);
			}
		}
		else
		{
			printf("the rect is not an array!\n");
		}
	}
	else
	{
		printf("rect is null\n");
	}

	cJSON *areas = cJSON_GetObjectItem(root, "areas");
	if (NULL != areas)
	{
		if (cJSON_IsArray(areas))
		{
			int num = cJSON_GetArraySize(areas);
			cJSON* area = areas->child;
			for (int i = 0; i < num; i++)
			{
				//cJSON_Print(cJSON_GetObjectItem(area,"id"));
				cJSON* id = cJSON_GetObjectItem(area, "id");
				printf("id = %d\n", id->valueint);
				cJSON* name = cJSON_GetObjectItem(area, "name");
				printf("name = %s\n", name->valuestring);
				cJSON* rect = cJSON_GetObjectItem(area, "rect");
				{
					if (cJSON_IsArray(rect))
					{
						int n = cJSON_GetArraySize(rect);
						for (int j = 0; j < n; j++)
						{
							cJSON* item = cJSON_GetArrayItem(rect, j);
							{
								printf("item = %d\n", item->valueint);
							}
						}
					}
					else
					{
						printf("not a array\n");

					}

				}
				area = area->next;
			}
		}
		else
		{
			{
				printf("the areas is not a array\n");
			}
		}

	}
	else
	{
		printf("areas is null\n");
	}

	
	fclose(file);
	free(tmpStr);
	system("pause");
	
	return 0;
}
