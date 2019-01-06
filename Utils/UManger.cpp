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
// Method:    AutoControst
// FullName:  UManger::AutoControst
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: Mat matface
// Author:    Haoyu_Zeng
// Date:      2019/01/06 16:56
//************************************
int UManger::AutoControst(Mat matface)
{
	Mat dst = Mat::zeros(matface.size(), matface.type());
	imshow("before", matface);
	//进行自动对比度校正
	double HistRed[256] = { 0 };
	double HistGreen[256] = { 0 };
	double HistBlue[256] = { 0 };

	int bluemap[256] = { 0 };
	int redmap[256] = { 0 };
	int greenmap[256] = { 0 };

	double dlowcut = 0.1;
	double dhighcut = 0.1;
	for (int i = 0; i < matface.rows; i++)
	{
		for (int j = 0; j < matface.cols; j++)
		{
			int iblue = matface.at<Vec3b>(i, j)[0];
			int igreen = matface.at<Vec3b>(i, j)[1];
			int ired = matface.at<Vec3b>(i, j)[2];

			HistBlue[iblue]++;
			HistGreen[igreen]++;
			HistRed[ired]++;
		}
	}
	int PixelAmount = matface.rows*matface.cols;
	cout << "rows" << matface.rows << endl;
	int isum = 0;
	// blue
	int iminblue = 0; 
	int imaxblue = 0;
	for (int y = 0; y < 256; y++)
	{
		isum = isum + HistBlue[y];
		if (isum >= PixelAmount*dlowcut*0.01)
		{
			iminblue = y;
			break;
		}
	}
	isum = 0;
	for (int y = 255; y >= 0; y--)
	{
		isum = isum + HistBlue[y];
		if (isum >= PixelAmount*dhighcut*0.01)
		{
			imaxblue = y;
			break;
		}
	}
	//red
	isum = 0;
	int iminred = 0; int imaxred = 0;
	for (int y = 0; y < 256; y++)
	{
		isum = isum + HistRed[y];
		if (isum >= PixelAmount*dlowcut*0.01)
		{
			iminred = y;
			break;
		}
	}
	isum = 0;
	for (int y = 255; y >= 0; y--)
	{
		isum = isum + HistRed[y];
		if (isum >= PixelAmount*dhighcut*0.01)
		{
			imaxred = y;
			break;
		}
	}
	//green
	isum = 0;
	int imingreen = 0; int imaxgreen = 0;
	for (int y = 0; y < 256; y++)
	{
		isum = isum + HistGreen[y];
		if (isum >= PixelAmount*dlowcut*0.01)
		{
			imingreen = y;
			break;
		}
	}
	isum = 0;
	for (int y = 255; y >= 0; y--)
	{
		isum = isum + HistGreen[y];
		if (isum >= PixelAmount*dhighcut*0.01)
		{
			imaxgreen = y;
			break;
		}
	}
	/////////自动色阶
	//自动对比度
	int imin = 0;
	if (imingreen > iminblue)
		imin = iminblue;
	else
		imin = imingreen;
	if (imin > iminred)
		imin = iminred;
	
	iminblue = imin;
	imingreen = imin;
	iminred = imin;

	int imax = 0;
	if (imaxgreen < imaxblue)
		imax = imaxblue;
	else
		imax = imaxblue;
	if (imaxred > imax)
		imax = imaxred;
		
	imaxred = imax;
	imaxgreen = imax;
	imaxblue = imax;
	
	//blue
	for (int y = 0; y < 256; y++)
	{
		if (y <= iminblue)
		{
			bluemap[y] = 0;
		}
		else if (y > imaxblue)
			{
				bluemap[y] = 255;
			}
		else
			{
				//  BlueMap(Y) = (Y - MinBlue) / (MaxBlue - MinBlue) * 255      '线性隐射
				float ftmp = (float)(y - iminblue) / (imaxblue - iminblue);
				cout << "ftmp" << ftmp << endl;
				bluemap[y] = (int)(ftmp * 255);
				cout << "blue" << bluemap[y] << endl;
			}
		

	}
	//red
	for (int y = 0; y < 256; y++)
	{
		if (y <= iminred)
		{
			redmap[y] = 0;
		}
		else if  (y > imaxred)
			{
				redmap[y] = 255;
			}
		else
			{
				//  BlueMap(Y) = (Y - MinBlue) / (MaxBlue - MinBlue) * 255      '线性隐射
				float ftmp = (float)(y - iminred) / (imaxred - iminred);
				redmap[y] = (int)(ftmp * 255);
			}
		

	}
	//green
	for (int y = 0; y < 256; y++)
	{
		if (y <= imingreen)
		{
			greenmap[y] = 0;
		}
		else if (y > imaxgreen)
			{
				greenmap[y] = 255;
			}
		else
			{
				//  BlueMap(Y) = (Y - MinBlue) / (MaxBlue - MinBlue) * 255      '线性隐射
				float ftmp = (float)(y - imingreen) / (imaxgreen - imingreen);
				greenmap[y] = (int)(ftmp * 255);
			}
		
	}
	//查表
	for (int i = 0; i < matface.rows; i++)
	{
		for (int j = 0; j < matface.cols; j++)
		{
			dst.at<Vec3b>(i, j)[0] = bluemap[matface.at<Vec3b>(i, j)[0]];
			dst.at<Vec3b>(i, j)[1] = greenmap[matface.at<Vec3b>(i, j)[1]];
			dst.at<Vec3b>(i, j)[2] = redmap[matface.at<Vec3b>(i, j)[2]];

		}
	}
	imshow("after", dst);
	waitKey(0);
	return RET_ERROR_OK;
}