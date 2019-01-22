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

UTILS_IMPL int VideoToPic(string Video_Path, string Pic_Path, double totalFremeNumber)
{
	return UManger::Instance()->VideoToPic(Video_Path,Pic_Path,totalFremeNumber);
}

UTILS_IMPL int PicToVideo(string Pic_Path, string Video_Path,int height,int width)
{
	return UManger::Instance()->PicToVideo(Pic_Path, Video_Path, height, width);
}

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

UTILS_IMPL int RGBSkin(Mat& src_img,Mat& dst_img)
{
	return UManger::Instance()->RGBSkin(src_img,dst_img);
}

UTILS_IMPL int EllipseSkin(Mat& src_img, Mat& dst_img)
{
	return UManger::Instance()->EllipseSkin(src_img, dst_img);
}

UTILS_IMPL int YCrCbOtusSkin(Mat& src_img, Mat& dst_img)
{
	return UManger::Instance()->YCrCbOtsuSkin(src_img, dst_img);
}

UTILS_IMPL int YCrCbSkin(Mat& src_img, Mat& dst_img)
{
	return UManger::Instance()->YCrCbSkin(src_img, dst_img);
}

UTILS_IMPL int HSVSkin(Mat& src_img, Mat& dst_img)
{
	return UManger::Instance()->HSVSkin(src_img, dst_img);
}

UTILS_IMPL int AddHat(Mat& img)
{
	return UManger::Instance()->AddHat(img);
}

UTILS_IMPL int AddGrasses(Mat& img)
{
	return UManger::Instance()->AddGrasses(img);
}

UTILS_IMPL int CartoonFilter(Mat& img)
{
	return UManger::Instance()->CartoonFilter(img);
}

UTILS_IMPL int Nostalgic(Mat& img)
{
	return UManger::Instance()->Nostalgic(img);
}

//UTILS_IMPL int AddRandom(Mat& img)
//{
//	return UManger::Instance()->AddRandom(img);
//}

UTILS_IMPL int AddGaussianNoise(Mat& img)
{
	return UManger::Instance()->AddGaussianNoise(img);
}

UTILS_IMPL int AddSaltPepperNoise(Mat& img)
{
	return UManger::Instance()->AddSaltPepperNoise(img);
}