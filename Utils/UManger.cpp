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

int UManger::RGBSkin(Mat& src_img, Mat& dst_img)
{
	dst_img = Mat::zeros(src_img.size(), src_img.type());

	if (src_img.empty() || 3 != src_img.channels())
	{
		cout << "cant load pic" << endl;
		return 0;
	}
	for (int i = 0; i < src_img.rows; i++)
	{
		for (int j = 0; j < src_img.cols; j++)
		{
			uchar *p_src = src_img.ptr<uchar>(i, j);
			uchar *p_dst = dst_img.ptr<uchar>(i, j);
			if ((p_src[2] > 95 && p_src[1] > 40 && p_src[0] > 20 &&
				(MAX(p_src[0], MAX(p_src[1], p_src[2])) - MIN(p_src[0], MIN(p_src[1], p_src[2])) > 15) &&
				abs(p_src[2] - p_src[1]) > 15 && p_src[2] > p_src[1] && p_src[1] > p_src[0]) ||
				(p_src[2] > 200 && p_src[1] > 210 && p_src[0] > 170 && abs(p_src[2] - p_src[1]) <= 15 &&
					p_src[2] > p_src[0] && p_src[1] > p_src[0]))
			{
				p_dst[0] = p_src[0];
				p_dst[1] = p_src[1];
				p_dst[2] = p_src[2];
			}
		}
	}
	return RET_ERROR_OK;
}

int UManger::EllipseSkin(Mat& src_img, Mat& dst_img)
{
	dst_img = src_img.clone();
	Mat skinCrCbHist = Mat::zeros(Size(256, 256), CV_8UC1);
	ellipse(skinCrCbHist, Point(113, 155.6), Size(23.4, 15.2), 43.0, 0.0, 360.0, Scalar(255, 255, 255), -1);

	Mat ycrcb_image;
	Mat output_mask = Mat::zeros(dst_img.size(), CV_8UC1);
	cvtColor(dst_img, ycrcb_image, CV_BGR2YCrCb);
	
	for (int i = 0; i < dst_img.rows; i++)
	{
		for (int j = 0; j < dst_img.cols; j++)
		{
			Vec3b ycrcb = ycrcb_image.at<Vec3b>(i, j);
			if (skinCrCbHist.at<uchar>(ycrcb[1], ycrcb[2]) > 0)
				output_mask.at<uchar>(i, j) = 255;
		}
	}
	Mat detect;
	dst_img.copyTo(detect, output_mask);
	dst_img = detect.clone();
	return RET_ERROR_OK;
}

int UManger::YCrCbOtsuSkin(Mat& src_img, Mat& dst_img)
{
	Mat ycrcb_image;
	cvtColor(src_img, ycrcb_image, CV_BGR2YCrCb);
	Mat detect;
	vector<Mat> channels;
	split(ycrcb_image, channels);
	Mat output_mask = channels[1];
	threshold(output_mask, output_mask, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	src_img.copyTo(detect, output_mask);
	dst_img = detect.clone();
	return RET_ERROR_OK;
}

int UManger::YCrCbSkin(Mat& src_img, Mat& dst_img)
{
	Mat ycrcb_image;
	int Cr = 1;
	int Cb = 2;
	cvtColor(src_img, ycrcb_image, CV_BGR2YCrCb);
	Mat output_mask = Mat::zeros(src_img.size(), CV_8UC1);

	for (int i = 0; i < src_img.rows; i++)
	{
		for (int j = 0; j < src_img.cols; j++)
		{
			uchar *p_mask = output_mask.ptr<uchar>(i, j);
			uchar *p_src = ycrcb_image.ptr<uchar>(i, j);
			if (p_src[Cr] >= 133 && p_src[Cr] <= 172 && p_src[Cb] >= 77 && p_src[Cb] <= 127)
			{
				p_mask[0] = 255;
			}
		}
	}
	Mat detect;
	src_img.copyTo(detect, output_mask);
	dst_img = detect.clone();
	return RET_ERROR_OK;
}

int UManger::HSVSkin(Mat& src_img, Mat& dst_img)
{
	Mat hsv_img;
	int h = 0;
	int s = 1;
	int v = 2;
	cvtColor(src_img, hsv_img, CV_BGR2HSV);

	Mat output_mask = Mat::zeros(src_img.size(), CV_8UC1);
	for (int i = 0; i < src_img.rows; i++)
	{
		for (int j = 0; j < src_img.cols; ++j)
		{
			uchar *p_mask = output_mask.ptr<uchar>(i, j);
			uchar *p_src = hsv_img.ptr<uchar>(i, j);
			if (p_src[h] >= 0 && p_src[h] <= 20 && p_src[s] >= 48 && p_src[v] >= 50)
			{
				p_mask[0] = 255;
			}
		}
	}
	Mat detect;
	src_img.copyTo(detect, output_mask);
	dst_img = detect.clone();

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(dst_img, dst_img, element);
	//erode(dst_img, dst_img, element);
	return RET_ERROR_OK;
}
 
int UManger::AddHat(Mat& img)
{
	imshow("mask", img);
	CascadeClassifier faceDetector;
	faceDetector.load("D://workspace//Utils//face_feature//haarcascade_frontalface_alt_tree.xml");
	Mat frame;
	Mat gray;
	VideoCapture cap(0);
	while (1)
	{
		cap >> frame;
		if(frame.empty())
			continue;
		cvtColor(frame, gray, CV_RGB2GRAY);
		equalizeHist(gray, gray);
		vector<Rect> faces;
		faceDetector.detectMultiScale(gray, faces, 1.2, 1, 0, Size(100, 100),Size(400,400));
		if (faces.size() > 0)
		{
			for (size_t i = 0; i < faces.size(); i++)
			{
				Mat out;
				rectangle(frame, faces[i], Scalar(0, 0, 255), 2, 8, 0);
				
				resize(img, out, Size(faces[i].width / 2, faces[i].height / 2));
				imshow("img", out);
				Mat imgROI = frame(Rect((faces[i].x + (faces[i].width)/4), abs(faces[i].y-(faces[i].height/3)), out.cols, out.rows));
				Mat mask = out.clone();
				cvtColor(mask, mask, CV_RGB2GRAY);
				out.copyTo(imgROI, mask);
				/*	cout << "faces.x" << faces[i].x << endl;
					cout << "faces.y" << faces[i].y << endl;
					cout << "faces.width" << faces[i].width << endl;
					cout << "faces.height" << faces[i].height << endl;*/
				cout << "faces.y" << faces[i].y << endl;

				//frame.copyTo(frame);
			}
			char c = waitKey(10);
			if (c == 27)
			{
				break;
			}
			imshow("frame", frame);
		}
	}

	waitKey(0);
	return RET_ERROR_OK;
}

int UManger::AddGrasses(Mat& img)
{
	//imshow("mask", img);
	bool use_detect = false;
	CascadeClassifier eyesDetect;
	eyesDetect.load("D://workspace//Utils//face_feature//haarcascade_eye.xml");
	Mat frame, gray;
	VideoCapture cap(0);
	while (1)
	{
		cap >> frame;
		cvtColor(frame, gray, CV_RGB2GRAY);
		equalizeHist(gray, gray);
		vector<Rect> eyes;
		if (use_detect)
		{
			eyesDetect.detectMultiScale(gray, eyes, 1.2, 1, 0, Size(10, 10), Size(100, 100));
			for (size_t i = 0; i < eyes.size(); i++)
			{
				rectangle(frame, eyes[i], Scalar(0, 255, 255), 2, 8, 0);
			}
			imshow("img", frame);
		}
		else
			imshow("frame", frame);

		waitKey(30);
	}
	return 0;

}

int UManger::CartoonFilter(Mat& img)
{
	Mat dst;
	
	medianBlur(img, dst, 7);
	Mat imgCanny;
	Canny(dst, imgCanny, 50, 150);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(imgCanny, imgCanny, kernel);
	imgCanny = imgCanny / 255;
	imgCanny = 1 - imgCanny;

	Mat imgf;
	imgCanny.convertTo(imgf, CV_32FC3);
	blur(imgf, imgf, Size(5, 5));
	//imshow("imgf", imgf);
	Mat bilater;
	bilateralFilter(img, bilater, 9, 150.0, 150.0);
	//imshow("bilater", bilater);

	Mat result = bilater / 25;
	result = result * 25;
	Mat img3c;
	Mat channels[] = { imgf,imgf,imgf };
	merge(channels, 3, img3c);
	Mat resultf;
	result.convertTo(resultf, CV_32FC3);

	multiply(resultf, img3c, resultf);

	resultf.convertTo(result, CV_8UC3);
	
	img = result.clone();


	return RET_ERROR_OK;
}

int UManger::Nostalgic(Mat& img)
{
	Mat src = Mat::zeros(img.size(),img.type());
	imshow("src", src);

	for (int i = 0;i<img.rows;i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			src.at<Vec3b>(i, j)[0] = static_cast<int>((img.at<Vec3b>(i, j)[0] * 272 + img.at<Vec3b>(i, j)[1] * 534 + img.at<Vec3b>(i, j)[1] * 131)/1000);
			src.at<Vec3b>(i, j)[1] = static_cast<int>((img.at<Vec3b>(i, j)[0] * 349 + img.at<Vec3b>(i, j)[1] * 686 + img.at<Vec3b>(i, j)[1] * 168)/1000);
			src.at<Vec3b>(i, j)[2] = static_cast<int>((img.at<Vec3b>(i, j)[0] * 393 + img.at<Vec3b>(i, j)[1] * 769 + img.at<Vec3b>(i, j)[1] * 189)/1000);

			if (src.at<Vec3b>(i, j)[0] < 0)
				src.at<Vec3b>(i, j)[0] = 0;
			if (src.at<Vec3b>(i, j)[0] >= 255)
				src.at<Vec3b>(i, j)[0] = 255;

			if (src.at<Vec3b>(i, j)[1] < 0)
				src.at<Vec3b>(i, j)[1] = 0;
			if (src.at<Vec3b>(i, j)[1] >= 255)
				src.at<Vec3b>(i, j)[1] = 255;

			if (src.at<Vec3b>(i, j)[2] < 0)
				src.at<Vec3b>(i, j)[2] = 0;
			if (src.at<Vec3b>(i, j)[2] >= 255)
				src.at<Vec3b>(i, j)[2] = 255;

		}
	}
	
	img = src.clone();
	return RET_ERROR_OK;

}