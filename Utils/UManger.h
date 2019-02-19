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
	int FastColorReduce(Mat& image, int div);

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

	//*************face相关*************
	//人脸特征点，将68个特征点的坐标写入到txt中
	//int FacesPoints(Mat& img);

	//*****************************************饰品相关*****************************************
	//添加帽子,输入的图片是帽子的图片，代码待改进，帽子位置不准确
	int AddHat(Mat& img);

	//添加眼镜，输入的图片是眼镜的图片，代码待改进，眼镜位置还准确
	int AddGrasses(Mat& img);

	//*****************************************滤镜相关*****************************************
	//添加卡通滤镜
	int CartoonFilter(Mat& img);

	//添加怀旧滤镜
	int NostalgicFilter(Mat& img);

	//添加怀旧滤镜
	int WaveFilter(Mat& img, const int& level);

	//油画滤镜
	int OilPaintFilter(Mat& img, const int& smoothness, const int& bucketSize);

	//*****************************************图片相关*****************************************
	//两张图片相加，分别输入两张图片，输出一张合成的结果
	int PicAddPic(Mat& img1, Mat& img2, Mat& result);
	
	//两张图片相减，分别输入两张图片，输出一张合成的结果，img1是被减数
	int PicSubPic(Mat& img1, Mat& img2, Mat& result);
    
	//两张图片相加，分别输入两张图片，输出一张合成的结果
	int PicMulPic(Mat& img1, Mat& img2, Mat& result);
	
	//两张图片相加，分别输入两张图片，输出一张合成的结果，img1是被除数
	int PicDivPic(Mat& img1, Mat& img2, Mat& result);

	//自动白平衡，输入图片
	int WhiteBalance(Mat& img);

	//*************颜色空间转换*************


	//*****************************************噪音相关*****************************************
	//在输入的图片上增加高斯噪音
	int AddGaussianNoise(Mat& img);

	//在输入的图片上增加椒盐噪声
	int AddSaltPepperNoise(Mat& img);

	//*****************************************工具相关*****************************************
	
	//将文件路径中的视频转为图片，需要输入视频地址，图片地址
	int VideoToPic(string VideoPath, string PicPath, double totalFrameNumber);

	//将文件路径中的图片合成视频，需要输入图片地址，视频地址，高和宽，视频地址精确到后缀
	int PicToVideo(string PicPath, string VideoPath, int height, int width);

	//批量修改文件夹内的图片名，输入图片地址及输出图片地址
	int RenamePic(string InPath, string OutPath);

	//*****************************************UI相关*****************************************
	
	//UI图片相关
	int UI_Img(bool& use_img);

	//UI视频相关
	int UI_Camera(bool& use_camera);


protected:
	UManger();
	virtual ~UManger();
};

#endif // ZHY_UTILS_UMANAGER_H
