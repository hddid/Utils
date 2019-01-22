#ifndef ZHY_UTILS_UTILS_H
#define ZHY_UTILS_UTILS_H

#include "Common.h"

using namespace cv;
using namespace std;

//获取当前版本
UTILS_API(string) GetCurrentVersion();

//RGB转灰度图，输入彩色图，输出灰度图
UTILS_API(int) ConvertRGB2Gray(const cv::Mat& imgRGB, cv::Mat& imgGray);

//遍历图像像素，利用 .ptr 和 * ++ 以及位运算 (continuous+channels)，速度最快
UTILS_API(int) FastColorReduce(Mat& image,int div);

//修改图片的亮度和对比度，采用公式g(i,j) = α*f(i,j)+β，需要输入alpha和beta值
UTILS_API(int) ContrastAndBright(Mat& src_image, Mat& dst_image, const double alpha, const double beta);

//将文件路径中的视频转为图片，需要输入视频地址，图片地址
UTILS_API(int) VideoToPic(string Video_Path, string Pic_Path, double totalFremeNumber);

//将文件路径中的图片合成视频，需要输入图片地址，视频地址，高和宽，视频地址精确到后缀
UTILS_API(int) PicToVideo(string Pic_Path, string Video_Path,int height,int width);

//两张图片相加，分别输入两张图片，输出一张合成的结果
UTILS_API(int) PicAddPic(Mat& img1, Mat& img2, Mat& result);

//两张图片相加，分别输入两张图片，输出一张合成的结果，img1是被减数
UTILS_API(int) PicSubPic(Mat& img1, Mat& img2, Mat& result);

//两张图片相加，分别输入两张图片，输出一张合成的结果
UTILS_API(int) PicMulPic(Mat& img1, Mat& img2, Mat& result);

//两张图片相加，分别输入两张图片，输出一张合成的结果，img1是被除数
UTILS_API(int) PicDivPic(Mat& img1, Mat& img2, Mat& result);

/////////////////////////////////////////////////////////////////////
//增加五种肤色检测方法

//第一种：基于RGB color space
UTILS_API(int) RGBSkin(Mat& src_img,Mat& dst_img);

//第二种：基于椭圆模型的皮肤检测
UTILS_API(int) EllipseSkin(Mat& src_img, Mat& dst_img);

//第三种：基于YCrCb颜色空间Cr分量+Otus法阈值分割
UTILS_API(int) YCrCbOtusSkin(Mat& src_img, Mat& dst_img);

//第四种：基于YCrCb颜色空间Cr，Cb范围筛选
UTILS_API(int) YCrCbSkin(Mat& src_img, Mat& dst_img);

//第五种：基于HSV颜色空间H范围筛选法
UTILS_API(int) HSVSkin(Mat& src_img, Mat& dst_img);

/////////////////////////////////////////////////////////
//相机功能
//添加帽子
UTILS_API(int) AddHat(Mat& img);
//添加眼镜
UTILS_API(int) AddGrasses(Mat& img);
//添加卡通滤镜
UTILS_API(int) CartoonFilter(Mat& img);
//添加怀旧滤镜
UTILS_API(int) Nostalgic(Mat& img);
//测试
//UTILS_API(int) AddRandom(Mat& img);

UTILS_API(int) WhiteBalance(Mat& img);

////////////////////////////////////////
//噪声
UTILS_API(int) AddGaussianNoise(Mat& img);
UTILS_API(int) AddSaltPepperNoise(Mat& img);

#endif//ZHY_UTILS_UTILS_H
