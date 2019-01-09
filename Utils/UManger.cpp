/***********************************
 *
 * file UManger.cpp
 * ingroup GroupName
 * TODO: long description
 * author Haoyu_Zeng
 * version 1.0
 * date  2018/08/31 16:26
 * E-mail: 1150566379@qq.com
 *
 ***********************************/

#include "UManger.h"
#include "Common.h"


UManger::UManger()
{
} 

UManger::~UManger()
{
}

//************************************
// Method:    ConvertRGB2Gray
// FullName:  UManger::ConvertRGB2Gray
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: const Mat & src
// Parameter: Mat & gray
// Author:    Haoyu_Zeng
// Date:      2018/09/03 9:02
//************************************
int UManger::ConvertRGB2Gray(const Mat & src, Mat & gray)
{
	if (src.empty())
		return RET_ERROR_IMAGE;

	if (gray.empty() || src.rows != gray.rows || src.cols != gray.cols)
	{
		gray = cv::Mat(src.rows, src.cols, CV_8UC1, Scalar(0));
	}

	for (int y = 0; y < src.rows; ++y)
	{
		uchar *gp = gray.ptr<uchar>(y);
		const uchar *cp = src.ptr<uchar>(y);
		for (int x = 0, x3 = 0; x < src.cols; ++x)
		{
			*gp++ = (117 * cp[x3 + 0] + 601 * cp[x3 + 1] + 306 * cp[x3 + 2]) >> 10;
			x3 = x + x + x;
		}
	}

	return RET_ERROR_OK;
}



//************************************
// Method:    FastColorReduce
// FullName:  UManger::FastColorReduce
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: Mat & image
// Parameter: int div
// Author:    Haoyu_Zeng
// Date:      2018/09/04 20:23
//************************************
int UManger::FastColorReduce(Mat& image,int div = 64)
{

	int nl = image.rows; 
	int nc = image.cols; 

	if (image.isContinuous())
	{
		//无填充像素
		nc = nc*nl;
		// 为一维数组
		nl = 1;  
	}

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	//掩码值e.g. 比如div=16, mask= 0xF0
	uchar mask = 0xFF << n; 

	for (int j = 0; j < nl; ++j) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; ++i) 
		{

			//-------------开始处理每个像素-------------------

			*data++ = *data&mask + div / 2;
			*data++ = *data&mask + div / 2;
			*data++ = *data&mask + div / 2;

		}                 
	}
	return RET_ERROR_OK;
}


//************************************
// Method:    ContrastAndBright
// FullName:  UManger::ContrastAndBright
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: Mat & src_image
// Parameter: Mat & dst_image
// Parameter: const double alpha
// Parameter: const double beta
// Author:    Haoyu_Zeng
// Date:      2018/09/06 10:13
//************************************
int UManger::ContrastAndBright(Mat& src_image, Mat& dst_image, const double alpha, const double beta)
{
	if (src_image.empty())
		return RET_ERROR_IMAGE;

	dst_image = Mat::zeros(src_image.size(), src_image.type());
	for (int i = 0; i < src_image.rows; ++i)
	{
		for (int j = 0; j < src_image.cols; ++j)
		{
			for (int c = 0; c < 3; ++c)
			{
				dst_image.at<Vec3b>(i, j)[c] =
					saturate_cast<uchar>(alpha*(src_image.at<Vec3b>(i, j)[c]) + beta);
			}
		}
	}
	return RET_ERROR_OK;
}

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
// Date:      2018/09/19 14:56
//************************************
int UManger::VideoToPic(string Video_Path, string Pic_Path,double totalFrameNumber)
{
	VideoCapture cap(Video_Path);
	totalFrameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT);

	Mat frame;
	bool flags = true;
	long currentFrame = 0;

	while (flags)
	{
		cap.read(frame);
		stringstream str;
		str << currentFrame << ".jpg";
		cout << "正在处理第 " << currentFrame << " 帧" << endl;
		
		if (0 == currentFrame % 1)
		{
			imwrite(Pic_Path + str.str(), frame);
		}
		if (currentFrame >= totalFrameNumber)
		{
			flags = false;
		}
		currentFrame++;
	}
	return RET_ERROR_OK;
}

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
// Date:      2018/09/20 22:22
//************************************
int UManger::PicToVideo(string Pic_Path, string Video_Path, int height, int width)
{
	VideoWriter video(Video_Path, CV_FOURCC('X', 'V', 'I', 'D'), 27, Size(height, width), true);
	vector<String> images;
	glob(Pic_Path, images, false);

	int count = images.size();
	for (size_t i = 0; i <= count; ++i)
	{
		stringstream str;
		str << i << ".jpg";
		Mat pic = imread(Pic_Path + str.str());
		if (!pic.empty())
		{
			resize(pic, pic, Size(height, width));
			video << pic;
			cout << "正在处理第" << i << "帧" << endl;
		}
	}
	return RET_ERROR_OK;
}

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
// Date:      2019/01/09 16:59
//************************************
int UManger::PicAddPic(Mat& img1, Mat& img2, Mat& result)
{
	if (img1.empty() || img2.empty())
	{
		cout << "cant load pic" << endl;
	}
	int b1, g1, r1;
	int b2, g2, r2;

	for (int rows = 0; rows < img1.rows; rows++)
	{
		for (int cols = 0; cols < img1.cols; cols++)
		{
			b1 = img1.at<Vec3b>(rows, cols)[0];
			g1 = img1.at<Vec3b>(rows, cols)[1];
			r1 = img1.at<Vec3b>(rows, cols)[2];

			b2 = img2.at<Vec3b>(rows, cols)[0];
			g2 = img2.at<Vec3b>(rows, cols)[1];
			r2 = img2.at<Vec3b>(rows, cols)[2];

			result.at<Vec3b>(rows, cols)[0] = saturate_cast<uchar>(b1 + b2);
			result.at<Vec3b>(rows, cols)[1] = saturate_cast<uchar>(g1 + g2);
			result.at<Vec3b>(rows, cols)[2] = saturate_cast<uchar>(r1 + r2);

		}
	}
	return RET_ERROR_OK;
}

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
// Date:      2019/01/09 16:59
//************************************
int UManger::PicSubPic(Mat& img1, Mat& img2, Mat& result)
{
	if (img1.empty() || img2.empty())
	{
		cout << "cant load pic" << endl;
	}
	int b1, g1, r1;
	int b2, g2, r2;

	for (int rows = 0; rows < img1.rows; rows++)
	{
		for (int cols = 0; cols < img1.cols; cols++)
		{
			b1 = img1.at<Vec3b>(rows, cols)[0];
			g1 = img1.at<Vec3b>(rows, cols)[1];
			r1 = img1.at<Vec3b>(rows, cols)[2];

			b2 = img2.at<Vec3b>(rows, cols)[0];
			g2 = img2.at<Vec3b>(rows, cols)[1];
			r2 = img2.at<Vec3b>(rows, cols)[2];

			result.at<Vec3b>(rows, cols)[0] = saturate_cast<uchar>(b1 - b2);
			result.at<Vec3b>(rows, cols)[1] = saturate_cast<uchar>(g1 - g2);
			result.at<Vec3b>(rows, cols)[2] = saturate_cast<uchar>(r1 - r2);

		}
	}
	return RET_ERROR_OK;
}

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
// Date:      2019/01/09 16:59
//************************************
int UManger::PicMulPic(Mat& img1, Mat& img2, Mat& result)
{
	if (img1.empty() || img2.empty())
	{
		cout << "cant load pic" << endl;
	}
	int b1, g1, r1;
	int b2, g2, r2;

	for (int rows = 0; rows < img1.rows; rows++)
	{
		for (int cols = 0; cols < img1.cols; cols++)
		{
			b1 = img1.at<Vec3b>(rows, cols)[0];
			g1 = img1.at<Vec3b>(rows, cols)[1];
			r1 = img1.at<Vec3b>(rows, cols)[2];

			b2 = img2.at<Vec3b>(rows, cols)[0];
			g2 = img2.at<Vec3b>(rows, cols)[1];
			r2 = img2.at<Vec3b>(rows, cols)[2];

			result.at<Vec3b>(rows, cols)[0] = saturate_cast<uchar>(b1 * b2);
			result.at<Vec3b>(rows, cols)[1] = saturate_cast<uchar>(g1 * g2);
			result.at<Vec3b>(rows, cols)[2] = saturate_cast<uchar>(r1 * r2);

		}
	}
	return RET_ERROR_OK;
}

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
// Date:      2019/01/09 16:59
//************************************
int UManger::PicDivPic(Mat& img1, Mat& img2, Mat& result)
{
	if (img1.empty() || img2.empty())
	{
		cout << "cant load pic" << endl;
	}
	double b1, g1, r1;
	double b2, g2, r2;

	for (int rows = 0; rows < img1.rows; rows++)
	{
		for (int cols = 0; cols < img1.cols; cols++)
		{
			b1 = img1.at<Vec3b>(rows, cols)[0];
			g1 = img1.at<Vec3b>(rows, cols)[1];
			r1 = img1.at<Vec3b>(rows, cols)[2];

			b2 = img2.at<Vec3b>(rows, cols)[0];
			g2 = img2.at<Vec3b>(rows, cols)[1];
			r2 = img2.at<Vec3b>(rows, cols)[2];

			result.at<Vec3b>(rows, cols)[0] = saturate_cast<uchar>(b1 / b2);
			result.at<Vec3b>(rows, cols)[1] = saturate_cast<uchar>(g1 / g2);
			result.at<Vec3b>(rows, cols)[2] = saturate_cast<uchar>(r1 / r2);

		}
	}
	return RET_ERROR_OK;
}