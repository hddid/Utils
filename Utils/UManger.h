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

//***********************************************************************
	//RGB图像转灰度图
	//************************************
	// Method:    ConvertRGB2Gray
	// FullName:  UManger::ConvertRGB2Gray
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: const Mat & src
	// Parameter: Mat & gray
	// Author:    Haoyu_Zeng
	// Date:      2018/08/31 15:55
	//************************************
	int ConvertRGB2Gray(const Mat& src, Mat& gray);
	

//***********************************************************************
	//最快的遍历图像方法
	//************************************
	// Method:    FastColorReduce
	// FullName:  UManger::FastColorReduce
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & image
	// Parameter: int div
	// Author:    Haoyu_Zeng
	// Date:      2018/09/04 20:43
	//************************************
	int FastColorReduce(Mat& image,int div);
//**********************************************************************
	//修改图片的亮度和对比度，需要输入alpha值和beta值
	//************************************
	// Method:    ContrastAndBright
	// FullName:  UManger::ContrastAndBright
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & image
	// Parameter: Mat & new_image
	// Parameter: const double alpha
	// Parameter: const double beta
	// Author:    Haoyu_Zeng
	// Date:      2018/09/05 21:04
	//************************************
	int ContrastAndBright(Mat& src_image, Mat& dst_image, const double alpha, const double beta);

//*****************************************************************
	//将视频裁成一帧一帧的图片
	//************************************
	// Method:    VideoToPic
	// FullName:  UManger::VideoToPic
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: string Video_Path
	// Parameter: string Pic_Path
	// Parameter: double totalFrameNumber
	// Author:    Haoyu_Zeng
	// Date:      2018/09/19 14:54
	//************************************
	int VideoToPic(string Video_Path, string Pic_Path, double totalFrameNumber);

//*****************************************************************
	//将文件路径的所有图片合成一个视频
	//************************************
	// Method:    PicToVideo
	// FullName:  UManger::PicToVideo
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: string Pic_Path
	// Parameter: string Video_Path
	// Parameter: int height
	// Parameter: int width
	// Author:    Haoyu_Zeng
	// Date:      2018/09/20 22:52
	//************************************
	int PicToVideo(string Pic_Path, string Video_Path,int height,int width);

//****************************************************************
	//两张图片像素相加
	//************************************
	// Method:    PicAddPic
	// FullName:  UManger::PicAddPic
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img1
	// Parameter: Mat & img2
	// Parameter: Mat & result
	// Author:    Haoyu_Zeng
	// Date:      2019/01/09 15:50
	//************************************
	int PicAddPic(Mat& img1, Mat& img2, Mat& result);

//******************************************************
	//两张图片像素相减，img1是被减数
	//************************************
	// Method:    PicSubPic
	// FullName:  UManger::PicSubPic
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img1
	// Parameter: Mat & img2
	// Parameter: Mat & result
	// Author:    Haoyu_Zeng
	// Date:      2019/01/09 15:52
	//************************************
	int PicSubPic(Mat& img1, Mat& img2, Mat& result);

//********************************************************
	//两张图片相乘
	//************************************
	// Method:    PicMulPic
	// FullName:  UManger::PicMulPic
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img1
	// Parameter: Mat & img2
	// Parameter: Mat & result
	// Author:    Haoyu_Zeng
	// Date:      2019/01/09 15:54
	//************************************
	int PicMulPic(Mat& img1, Mat& img2, Mat& result);

//***********************************************************
	//两张图片相除，img1是被除数
	//************************************
	// Method:    PicDivPic
	// FullName:  UManger::PicDivPic
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img1
	// Parameter: Mat & img2
	// Parameter: Mat & result
	// Author:    Haoyu_Zeng
	// Date:      2019/01/09 15:54
	//************************************
	int PicDivPic(Mat& img1, Mat& img2, Mat& result);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//增加五种皮肤检测方法
//*****************************************************************
	//第一种:基于RGB color space检测
	int RGBSkin(Mat& src_img,Mat& dst_img);
	//第二种:基于椭圆皮肤模型的皮肤检测
	int EllipseSkin(Mat& src_img, Mat& dst_img);
	//第三种：基于YCrCu颜色空间Cr分量+Otsu法阈值分割
	int YCrCbOtsuSkin(Mat& src_img, Mat& dst_img);
	//第四种：基于YCrCb颜色空间Cr，Cb范围筛选法
	int YCrCbSkin(Mat& src_img, Mat& dst_img);
	//第五种：基于HSV颜色空间H范围筛选法
	int HSVSkin(Mat& src_img, Mat& dst_img);

//*****************************************************************
	//相机功能
	//************************************
	// Method:    AddOrnament
	// FullName:  UManger::AddOrnament
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & src_img
	// Author:    Haoyu_Zeng
	// Date:      2019/01/11 17:47
	//************************************
	int AddHat(Mat& img);

	//************************************
	// Method:    AddGrasses
	// FullName:  UManger::AddGrasses
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img
	// Author:    Haoyu_Zeng
	// Date:      2019/01/18 20:22
	//************************************
	int AddGrasses(Mat& img);

	//卡通滤镜
	//************************************
	// Method:    CartoonFilter
	// FullName:  UManger::CartoonFilter
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img
	// Author:    Haoyu_Zeng
	// Date:      2019/01/18 20:22
	//************************************
	int CartoonFilter(Mat& img);

	//怀旧滤镜
	//************************************
	// Method:    Nostalgic
	// FullName:  UManger::Nostalgic
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img
	// Author:    Haoyu_Zeng
	// Date:      2019/01/18 20:22
	//************************************
	int Nostalgic(Mat& img);

	//************************************
	// Method:    AddRandom
	// FullName:  UManger::AddRandom
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img
	// Author:    Haoyu_Zeng
	// Date:      2019/01/18 20:22
	//************************************
	//int AddRandom(Mat& img);

	//白平衡
	//************************************
	// Method:    WhiteBalance
	// FullName:  UManger::WhiteBalance
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat & img
	// Author:    Haoyu_Zeng
	// Date:      2019/01/22 21:40
	//************************************
	int WhiteBalance(Mat& img);


///////////////////////////////////////////////
//噪音相关
//add gaussian noise
	int AddGaussianNoise(Mat& img);
//add salt_noise
	int AddSaltPepperNoise(Mat& img);


/////////////////////////////////////////////
//face相关



protected:
	UManger();
	virtual ~UManger();
};

#endif // ZHY_UTILS_UMANAGER_H
