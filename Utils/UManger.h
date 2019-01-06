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

//*****************************************************************
	//自动对比度调整
	//************************************
	// Method:    autocontrost
	// FullName:  UManger::autocontrost
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Mat matface
	// Author:    Haoyu_Zeng
	// Date:      2019/01/06 16:52
	//************************************
	int AutoControst(Mat matface);

protected:
	UManger();
	virtual ~UManger();
};

#endif // ZHY_UTILS_UMANAGER_H
