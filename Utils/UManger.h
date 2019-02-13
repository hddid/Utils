/***********************************
 *
 * class:   classname
 * file UManger.h
 * ingroup GroupName
 * brief 
 * TODO: long description
 * author Haoyu_Zeng
 * version 1.0
 * date 八月 2018
 * Contact: 1150566379@qq.com
 *
 ***********************************/
#ifndef ZHY_UTILS_UMANAGER_H
#define ZHY_UTILS_UMANAGER_H

#include <math.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>


#include "Singleton.h"

using namespace std;
using namespace cv;

class UManger : public Singleton<UManger>
{
	friend class Singleton<UManger>;

public:

	//RGB转灰度图，输入彩色图，输出灰度图
	int ConvertRGB2Gray(const Mat& src, Mat& gray);
	
	//遍历图像像素，利用 .ptr 和 * ++ 以及位运算 (continuous+channels)，速度最快
	int FastColorReduce(Mat& image,int div);

	//修改图片的亮度和对比度，采用公式g(i,j) = α*f(i,j)+β，需要输入alpha和beta值
	int ContrastAndBright(Mat& src_image, Mat& dst_image, const double alpha, const double beta);


	//*****************************************检测相关*****************************************
										//增加五种皮肤检测方法
	//第一种:基于RGB color space检测
	int RGBSkin(Mat& img);
	//第二种:基于椭圆皮肤模型的皮肤检测
	int EllipseSkin(Mat& img);
	//第三种：基于YCrCu颜色空间Cr分量+Otsu法阈值分割
	int YCrCbOtsuSkin(Mat& img);
	//第四种：基于YCrCb颜色空间Cr，Cb范围筛选法
	int YCrCbSkin(Mat& img);
	//第五种：基于HSV颜色空间H范围筛选法
	int HSVSkin(Mat& img);
										//face相关
	//int FacesPoints(Mat& img);

	//*****************************************饰品相关*****************************************
	int AddHat(Mat& img);

	int AddGrasses(Mat& img);

	//*****************************************滤镜相关*****************************************
	int CartoonFilter(Mat& img);

	int NostalgicFilter(Mat& img);

	int WaveFilter(Mat& img);

	//*****************************************图片相关*****************************************
	int PicAddPic(Mat& img1, Mat& img2, Mat& result);

	int PicSubPic(Mat& img1, Mat& img2, Mat& result);

	int PicMulPic(Mat& img1, Mat& img2, Mat& result);

	int PicDivPic(Mat& img1, Mat& img2, Mat& result);

	int WhiteBalance(Mat& img);

	//Tb means Trackbar
	//int Tb_ContrasAndBright(Mat& img);

	//*****************************************噪音相关*****************************************
	int AddGaussianNoise(Mat& img);

	int AddSaltPepperNoise(Mat& img);

	//*****************************************工具相关*****************************************
	int VideoToPic(string VideoPath, string PicPath, double totalFrameNumber);
	
	int PicToVideo(string PicPath, string VideoPath, int height, int width);

	int RenamePic(string InPath, string OutPath);

	//*****************************************UI相关*****************************************
	int UI_Img(bool& use_img);
	
	int UI_Camera(bool& use_camera);



protected:
	UManger();
	virtual ~UManger();
};

#endif // ZHY_UTILS_UMANAGER_H
