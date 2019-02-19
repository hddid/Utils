/***********************************
 *
 * file Utils.cpp
 * ingroup GroupName
 * TODO: long description
 * author Haoyu_Zeng
 * version 1.0
 * date  2018/08/31 20:20
 * E-mail: 1150566379@qq.com
 *
 ***********************************/
#include "Utils.h"

#include "UVersion.h"
#include "UManger.h"


UTILS_IMPL string GetCurrentVersion()
{
	return  OST_BRIEF_VERSION_STRING;
}


//http://www.cnblogs.com/Imageshop/p/3302850.html

UTILS_IMPL int ConvertRGB2Gray(const cv::Mat& imgRGB, cv::Mat& imgGray)
{
	return UManger::Instance()->ConvertRGB2Gray(imgRGB, imgGray);
}

UTILS_IMPL int FastColorReduce(Mat& image, int div = 64)
{
	return UManger::Instance()->FastColorReduce(image,div);
}

UTILS_IMPL int ContrastAndBright(Mat& src_image, Mat& dst_image, const double alpha, const double beta)
{
	return UManger::Instance()->ContrastAndBright(src_image, dst_image, alpha, beta);
}


//*****************************************检测相关*****************************************

UTILS_IMPL int RGBSkin(Mat& img)
{
	return UManger::Instance()->RGBSkin(img);
}

UTILS_IMPL int EllipseSkin(Mat& img)
{
	return UManger::Instance()->EllipseSkin(img);
}

UTILS_IMPL int YCrCbOtusSkin(Mat& img)
{
	return UManger::Instance()->YCrCbOtsuSkin(img);
}

UTILS_IMPL int YCrCbSkin(Mat& img)
{
	return UManger::Instance()->YCrCbSkin(img);
}

UTILS_IMPL int HSVSkin(Mat& img)
{
	return UManger::Instance()->HSVSkin(img);
}

//人脸特征点
#if 0
UTILS_IMPL int FacesPoints(Mat& img)
{
	return UManger::Instance()->FacesPoints(img);
}
#endif


//*****************************************饰品相关*****************************************

UTILS_IMPL int AddHat(Mat& img)
{
	return UManger::Instance()->AddHat(img);
}

UTILS_IMPL int AddGrasses(Mat& img)
{
	return UManger::Instance()->AddGrasses(img);
}


//*****************************************滤镜相关*****************************************

UTILS_IMPL int CartoonFilter(Mat& img)
{
	return UManger::Instance()->CartoonFilter(img);
}

UTILS_IMPL int NostalgicFilter(Mat& img)
{
	return UManger::Instance()->NostalgicFilter(img);
}

UTILS_IMPL int WaveFilter(Mat& img,const int& level)
{
	return UManger::Instance()->WaveFilter(img,level);
}

UTILS_IMPL int OilPaintFilter(Mat& img,const int& smoothness,const int& bucketSize)
{
	return UManger::Instance()->OilPaintFilter(img,smoothness,bucketSize);
}


//*****************************************图片相关*****************************************

UTILS_IMPL int PicAddPic(Mat& img1, Mat& img2, Mat& result)
{
	return UManger::Instance()->PicAddPic(img1, img2, result);
}

UTILS_IMPL int PicSubPic(Mat& img1, Mat& img2, Mat& result)
{
	return UManger::Instance()->PicSubPic(img1, img2, result);
}

UTILS_IMPL int PicMulPic(Mat& img1, Mat& img2, Mat& result)
{
	return UManger::Instance()->PicMulPic(img1, img2, result);
}

UTILS_IMPL int PicDivPic(Mat& img1, Mat& img2, Mat& result)
{
	return UManger::Instance()->PicDivPic(img1, img2, result);
}

UTILS_IMPL int WhiteBalance(Mat& img)
{
	return UManger::Instance()->WhiteBalance(img);
}


//*****************************************噪音相关*****************************************
UTILS_IMPL int AddGaussianNoise(Mat& img)
{
	return UManger::Instance()->AddGaussianNoise(img);
}

UTILS_IMPL int AddSaltPepperNoise(Mat& img)
{
	return UManger::Instance()->AddSaltPepperNoise(img);
}


//*****************************************工具相关*****************************************

UTILS_IMPL int RenamePic(string InPic, string OutPic)
{
	return UManger::Instance()->RenamePic(InPic, OutPic);
}

UTILS_IMPL int VideoToPic(string VideoPath, string PicPath, double totalFremeNumber)
{
	return UManger::Instance()->VideoToPic(VideoPath, PicPath, totalFremeNumber);
}

UTILS_IMPL int PicToVideo(string PicPath, string VideoPath, int height, int width)
{
	return UManger::Instance()->PicToVideo(PicPath, VideoPath, height, width);
}

//*****************************************UI相关*****************************************

UTILS_IMPL int UI_Img(bool& use_img)
{
	return UManger::Instance()->UI_Img(use_img);
}

UTILS_IMPL int UI_Camera(bool& use_camera)
{
	return UManger::Instance()->UI_Camera(use_camera);
}
