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
#include "Ui.h"

UManger::UManger()
{
} 

UManger::~UManger()
{
}

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

	for (int j = 0; j < nl; ++j) 
	{
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; ++i) 
		{
			*data++ = *data&mask + div / 2;
			*data++ = *data&mask + div / 2;
			*data++ = *data&mask + div / 2;
		}                 
	}
	return RET_ERROR_OK;
}

int UManger::ContrastAndBright(Mat& src_image, Mat& dst_image, const double alpha, const double beta)
{
	if (src_image.empty())
		return RET_ERROR_IMAGE;

	dst_image = Mat::zeros(src_image.size(), src_image.type());
	for (int i = 0; i < src_image.rows; ++i)
	{
		for (int j = 0; j < src_image.cols; ++j)
		{
			dst_image.at<Vec3b>(i, j)[0] =
				saturate_cast<uchar>(alpha*(src_image.at<Vec3b>(i, j)[0]) + beta);
			dst_image.at<Vec3b>(i, j)[1] =
				saturate_cast<uchar>(alpha*(src_image.at<Vec3b>(i, j)[1]) + beta);
			dst_image.at<Vec3b>(i, j)[2] =
				saturate_cast<uchar>(alpha*(src_image.at<Vec3b>(i, j)[2]) + beta);
		}
	}
	return RET_ERROR_OK;
}


//*****************************************检测相关*****************************************

int UManger::RGBSkin(Mat& img)
{
	Mat dst_img = Mat::zeros(img.size(), img.type());

	if (img.empty() || 3 != img.channels())
	{
		cout << "cant load pic" << endl;
		return 0;
	}
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			uchar *p_src = img.ptr<uchar>(i, j);
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
	img = dst_img.clone();
	return RET_ERROR_OK;
}

int UManger::EllipseSkin(Mat& img)
{
	Mat dst_img = img.clone();
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
	img = dst_img.clone();
	return RET_ERROR_OK;
}

int UManger::YCrCbOtsuSkin(Mat& img)
{
	Mat dst_img;
	Mat ycrcb_image;
	cvtColor(img, ycrcb_image, CV_BGR2YCrCb);
	Mat detect;
	vector<Mat> channels;
	split(ycrcb_image, channels);
	Mat output_mask = channels[1];
	threshold(output_mask, output_mask, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	img.copyTo(detect, output_mask);
	dst_img = detect.clone();
	img = dst_img.clone();
	return RET_ERROR_OK;
}

int UManger::YCrCbSkin(Mat& img)
{
	Mat ycrcb_image;
	int Cr = 1;
	int Cb = 2;
	cvtColor(img, ycrcb_image, CV_BGR2YCrCb);
	Mat output_mask = Mat::zeros(img.size(), CV_8UC1);

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
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
	img.copyTo(detect, output_mask);
	Mat dst_img = detect.clone();
	img = dst_img.clone();
	return RET_ERROR_OK;
}

int UManger::HSVSkin(Mat& img)
{
	Mat hsv_img;
	int h = 0;
	int s = 1;
	int v = 2;
	cvtColor(img, hsv_img, CV_BGR2HSV);

	Mat output_mask = Mat::zeros(img.size(), CV_8UC1);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; ++j)
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
	img.copyTo(detect, output_mask);
	Mat dst_img = detect.clone();

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(dst_img, dst_img, element);
	//erode(dst_img, dst_img, element);
	img = dst_img.clone();
	return RET_ERROR_OK;
}

//人脸特征点检测
#if 0
int UManger::FacesPoints(Mat& img)
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "cant open camera" << endl;
		return 0;
	}
	dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
	dlib::shape_predictor pose_model;
	dlib::deserialize("./shape_predictor_68_face_landmarks.dat");

	while (cv::waitKey(30)!=27)
	{
		cv::Mat frame;
		cap >> frame;
		int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
		int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
		cout << "width" << width << endl;
		cout << "height" << height << endl;

		dlib::cv_image<dlib::bgr_pixel> cimg(frame);
		std::vector<dlib::rectangle> faces = detector(cimg);
		std::vector<dlib::full_object_detection> shapes;

		for (unsigned long i = 0;i<faces.size();++i)
		{
			shapes.push_back(pose_model(cimg, faces[i]));
		}
		ofstream outfile;
		outfile.open("./facespoints.txt", ios::app);
		if (!outfile.is_open())
		{
			cout << "open file failure" << endl;
		}
		if (!shapes.empty())
		{
			for (int i = 0; i < 68; ++i)
			{
				circle(img, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 255, 0), -1);
				cv::putText(frame, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0));
				outfile << shapes[0].part(i).x() << " " << shapes[0].part(i).y() << "\t" << endl;

			}
			outfile.close();
		}
		
	}
	return RET_ERROR_OK;
}
#endif
 

//*****************************************饰品相关*****************************************

int UManger::AddHat(Mat& img)
{
	imshow("mask", img);
	
	CascadeClassifier faceDetector;
	faceDetector.load("D://workspace//Utils//haarcascade//haarcascade_frontalface_alt_tree.xml");
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
				cout << "faces.y" << faces[i].y << endl;
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
	bool use_detect = false;
	CascadeClassifier eyesDetect;
	eyesDetect.load("D://workspace//Utils//haarcascade//haarcascade_eye.xml");
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


//*****************************************滤镜相关*****************************************

int UManger::CartoonFilter(Mat& img)
{
	Mat dst;
	
	medianBlur(img, dst, 7);
	Mat imgCanny;
	Canny(dst, imgCanny, 50, 150);
	//设置核的种类及大小
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(imgCanny, imgCanny, kernel);
	imgCanny = imgCanny / 255;
	imgCanny = 1 - imgCanny;

	Mat imgf;
	imgCanny.convertTo(imgf, CV_32FC3);
	blur(imgf, imgf, Size(5, 5));
	
	Mat bilater;
	//双边滤波
	bilateralFilter(img, bilater, 9, 150.0, 150.0);

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

int UManger::NostalgicFilter(Mat& img)
{
	Mat src = Mat::zeros(img.size(),img.type());
	//imshow("src", src); 

	for (int i = 0;i<img.rows;i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			src.at<Vec3b>(i, j)[0] = max(0,(min(255,(static_cast<int>((img.at<Vec3b>(i, j)[2] * 131 + img.at<Vec3b>(i, j)[1] * 534 + img.at<Vec3b>(i, j)[0] * 272)/1000)))));
			src.at<Vec3b>(i, j)[1] = max(0,(min(255,(static_cast<int>((img.at<Vec3b>(i, j)[2] * 168 + img.at<Vec3b>(i, j)[1] * 686 + img.at<Vec3b>(i, j)[0] * 349)/1000)))));
			src.at<Vec3b>(i, j)[2] = max(0,(min(255,(static_cast<int>((img.at<Vec3b>(i, j)[2] * 189 + img.at<Vec3b>(i, j)[1] * 769 + img.at<Vec3b>(i, j)[0] * 393)/1000)))));		
		}
	}
	img = src.clone();
	return RET_ERROR_OK;

}

int UManger::WaveFilter(Mat& img,const int& level)
{
	Mat src = img.clone();

	int width = img.cols;
	int height = img.rows;
	//int N = 30;

	Point Center(width / 2, height / 2);

	float new_x, new_y;
	float p, q, x1, y1, x0, y0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			y0 = Center.y - y;
			x0 = x - Center.x;
			new_x = level*sin(2 * 3.14*y0 / 128.0) + x0;
			new_y = level*cos(2 * 3.14*x0 / 128.0) + y0;
			new_x = Center.x + new_x;
			new_y = Center.y - new_y;

			if (new_x < 0)         
				new_x = 0;
			if (new_x >= width - 1)  
				new_x = width - 2;
			if (new_y < 0)         
				new_y = 0;
			if (new_y >= height - 1)
				new_y = height - 2;

			x1 = (int)new_x;
			y1 = (int)new_y;

			p = new_x - x1;
			q = new_y - y1;

			src.at<Vec3b>(y, x)[0] = ((1 - p)*(1 - q)*img.at<Vec3b>(y1, x1)[0] + p*(1 - q)*img.at<Vec3b>(y1, x1 + 1)[0] + q*(1 - p)*img.at<Vec3b>(y1 + 1, x1)[0] + p*q*img.at<Vec3b>(y1 + 1, x1 + 1)[0]);
			src.at<Vec3b>(y, x)[1] = ((1 - p)*(1 - q)*img.at<Vec3b>(y1, x1)[1] + p*(1 - q)*img.at<Vec3b>(y1, x1 + 1)[1] + q*(1 - p)*img.at<Vec3b>(y1 + 1, x1)[1] + p*q*img.at<Vec3b>(y1 + 1, x1 + 1)[1]);
			src.at<Vec3b>(y, x)[2] = ((1 - p)*(1 - q)*img.at<Vec3b>(y1, x1)[2] + p*(1 - q)*img.at<Vec3b>(y1, x1 + 1)[2] + q*(1 - p)*img.at<Vec3b>(y1 + 1, x1)[2] + p*q*img.at<Vec3b>(y1 + 1, x1 + 1)[2]);
		}
	}
	img = src.clone();
	return RET_ERROR_OK;
}

int UManger::OilPaintFilter(Mat& img,const int& smoothness,const int& bucketSize)
{
	int width = img.cols;
	int height = img.rows;

	int lenArray = bucketSize + 1;
	int* CountIntensity = new int[lenArray];
	uint* RedAverage = new uint[lenArray];
	uint* GreenAverage = new uint[lenArray];
	uint* BlueAverage = new uint[lenArray];

	Mat gray;
	ConvertRGB2Gray(img, gray);

	/// 目标图像
	Mat dst = Mat::zeros(img.size(), img.type());

	for (int i = 0; i < height; i++)
	{
		// 油画渲染范围上下边界
		int top = i - smoothness;
		int bottom = i + smoothness + 1;

		if (top < 0) top = 0;
		if (bottom >= height) bottom = height - 1;

		for (int j = 0; j < width; j++)
		{
			// 油画渲染范围左右边界
			int left = j - smoothness;
			int right = j + smoothness + 1;

			if (left < 0) left = 0;
			if (right >= width) right = width - 1;

			//初始化数组
			for (int i = 0; i < lenArray; i++)
			{
				CountIntensity[i] = 0;
				RedAverage[i] = 0;
				GreenAverage[i] = 0;
				BlueAverage[i] = 0;
			}

			for (int j = top; j < bottom; j++)
			{
				for (int i = left; i < right; i++)
				{
					uchar intensity = static_cast<uchar>(bucketSize*gray.at<uchar>(j, i) / 255.0);
					CountIntensity[intensity]++;

					RedAverage[intensity] += img.at<Vec3b>(j, i)[2];
					GreenAverage[intensity] += img.at<Vec3b>(j, i)[1];
					BlueAverage[intensity] += img.at<Vec3b>(j, i)[0];
				}
			}

			// 求最大值，并记录下数组索引
			uchar chosenIntensity = 0;
			int maxInstance = CountIntensity[0];
			for (int i = 1; i < lenArray; i++)
			{
				if (CountIntensity[i] > maxInstance)
				{
					chosenIntensity = (uchar)i;
					maxInstance = CountIntensity[i];
				}
			}
			dst.at<Vec3b>(i, j)[2] = static_cast<uchar>(RedAverage[chosenIntensity] / static_cast<float>(maxInstance));
			dst.at<Vec3b>(i, j)[1] = static_cast<uchar>(GreenAverage[chosenIntensity] / static_cast<float>(maxInstance));
			dst.at<Vec3b>(i, j)[0] = static_cast<uchar>(BlueAverage[chosenIntensity] / static_cast<float>(maxInstance));
		}
	}
	//释放内存
	delete[] CountIntensity;
	delete[] RedAverage;
	delete[] GreenAverage;
	delete[] BlueAverage;

	img = dst.clone();
	return RET_ERROR_OK;
}


//*****************************************图片相关*****************************************

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

int UManger::WhiteBalance(Mat& img)
{
	vector<Mat> imgRGB;
	split(img, imgRGB);
	double B = mean(imgRGB[0])[0];
	double G = mean(imgRGB[1])[0];
	double R = mean(imgRGB[2])[0];

	double KB = (R + G + B) / (3 * B);
	double KG = (R + G + B) / (3 * G);
	double KR = (R + G + B) / (3 * R);

	imgRGB[0] = imgRGB[0] * KB;
	imgRGB[1] = imgRGB[1] * KG;
	imgRGB[2] = imgRGB[2] * KR;

	merge(imgRGB, img);
	return RET_ERROR_OK;

}


//*****************************************噪音相关*****************************************

int UManger::AddGaussianNoise(Mat& img)
{
	Mat noise = Mat::zeros(img.size(), img.type());
	randn(noise, (15, 15, 15), (30, 30, 30));
	Mat dst;
	add(img, noise, dst);
	img = dst.clone();
	return RET_ERROR_OK;
}

int UManger::AddSaltPepperNoise(Mat& img)
{
	int h = img.rows;
	int w = img.cols;
	
	for (int m = 0; m < 10000; m++)
	{
		int i = HY_RANDOM(1, w - 1);
		int j = HY_RANDOM(1, h - 1);
	
		if (i % 2 == 1)
		{
			img.at<Vec3b>(j, i) = Vec3b(255, 255, 255);
		}
		else
		{
			img.at<Vec3b>(j, i) = Vec3b(0, 0, 0);
		}
	}
	img = img.clone();
	return RET_ERROR_OK;
}


//*****************************************工具相关*****************************************

int UManger::RenamePic(string InPath, string OutPath)
{
	//定义一个vector存储图片
	vector<cv::String> filenames;
	//将InPath的所有文件名存进filenames;
	glob(InPath, filenames, false);

	size_t count = filenames.size();

	for (size_t i = 0; i < count; i++)
	{	
		stringstream str;
		str << i << ".jpg";
		imwrite(OutPath + str.str(), imread(filenames[i]));
	}
	return RET_ERROR_OK;
}

int UManger::VideoToPic(string VideoPath, string PicPath, double totalFrameNumber)
{
	VideoCapture cap(VideoPath);
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
			imwrite(PicPath + str.str(), frame);
		}
		if (currentFrame >= totalFrameNumber)
		{
			flags = false;
		}
		currentFrame++;
	}
	return RET_ERROR_OK;
}

int UManger::PicToVideo(string PicPath, string VideoPath, int height, int width)
{
	VideoWriter video(VideoPath, CV_FOURCC('X', 'V', 'I', 'D'), 27, Size(height, width), true);
	vector<String> images;
	glob(PicPath, images, false);

	int count = images.size();
	for (size_t i = 0; i <= count; ++i)
	{
		stringstream str;
		str << i << ".jpg";
		Mat pic = imread(PicPath + str.str());
		if (!pic.empty())
		{
			resize(pic, pic, Size(height, width));
			video << pic;
			cout << "正在处理第" << i << "帧" << endl;
		}
	}
	return RET_ERROR_OK;
}


//*****************************************DeepLearning相关*****************************************
int UManger::KmeansDataClassification(int& numCluster)
{
	Mat img(500, 500, CV_8UC3);
	RNG rng(12345);

	Scalar colorTab[] = {
		Scalar(0,0,255),
		Scalar(255, 0, 0),
	};

	int sampleCount = rng.uniform(5, 500);

	Mat points(sampleCount, 1, CV_32FC2);

	//生成随机数
	for (int k = 0;k<numCluster;k++)
	{
		Point center;
		center.x = rng.uniform(0, img.cols);
		center.y = rng.uniform(0, img.rows);
		Mat pointChunk = points.rowRange(k*sampleCount / numCluster,
			k == numCluster - 1 ? sampleCount : (k + 1)*sampleCount / numCluster);

		rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));

	}
	randShuffle(points, 1, &rng);

	Mat labels;
	Mat centers;
	kmeans(points, numCluster, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1), 3, KMEANS_PP_CENTERS,centers);

	img = Scalar::all(255);
	for (int i = 0;i<sampleCount;i++)
	{
		int index = labels.at<int>(i);
		Point p = points.at<Point2f>(i);
		circle(img, p, 2, colorTab[index], -1, 8);
	}
	for (int i = 0;i<centers.rows;i++)
	{
		int x = centers.at<float>(i, 0);
		int y = centers.at<float>(i, 1);
		cout << " c.x " << x << " c.y " << y << endl;
		circle(img, Point(x, y), 40, colorTab[i], 1, LINE_AA);
	}
	imshow("KMeans-Data-Demo", img);
	waitKey(0);
	return RET_ERROR_OK;
}


int UManger::KmeansImageDivision(string& PicPath)
{
	Mat img = imread(PicPath);
	if(img.empty())
	{
		cout << "cant load img" << endl;
		return -1;
	}
	imshow("input-img", img);

	Scalar colorTab[] = {
		Scalar(0,0,255),
		Scalar(0,255,0),
		Scalar(255,0,0),
		Scalar(0,255,255),
		Scalar(255,0,255),
	};

	int width = img.cols;
	int height = img.rows;
	int dims = img.channels();

	//初始化定义
	int sampleCount = width*height;
	int clusterCount = 3;
	Mat labels;
	Mat centers;

	//RGB 数据转样本数据
	Mat sample_data = img.reshape(3, sampleCount);
	Mat data;
	sample_data.convertTo(data, CV_32F);

	// 运行K-Means
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	// 显示图像分割结果
	int index = 0;
	Mat result = Mat::zeros(img.size(), img.type());
	for (int row = 0; row < height; row++) 
	{
		for (int col = 0; col < width; col++) 
		{
			index = row*width + col;
			int label = labels.at<int>(index, 0);
			result.at<Vec3b>(row, col)[0] = colorTab[label][0];
			result.at<Vec3b>(row, col)[1] = colorTab[label][1];
			result.at<Vec3b>(row, col)[2] = colorTab[label][2];
	
		}
	}

	imshow("KMeans-image-Division", result);
	waitKey(0);
	return RET_ERROR_OK;
}

int UManger::KmeansBackgroundSubstitution(string& PicPath)
{
	Mat img = imread(PicPath);
	if (img.empty())
	{
		cout << "cant load img" << endl;
		return -1;
	}
	imshow("input-img", img);


	int width = img.cols;
	int height = img.rows;
	int dims = img.channels();

	//初始化定义
	int sampleCount = width*height;
	int clusterCount = 3;
	Mat labels;
	Mat centers;

	//RGB 数据转样本数据
	Mat sample_data = img.reshape(3, sampleCount);
	Mat data;
	sample_data.convertTo(data, CV_32F);

	// 运行K-Means
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	Mat mask = Mat::zeros(img.size(), CV_8UC1);
	int index = labels.at<int>(0, 0);
	labels = labels.reshape(1, height);

	for(int row = 0;row<height;row++)
	{
		for(int col = 0;col<width;col++)
		{
			int c = labels.at<int>(row, col);
			if(c == index)
			{
				mask.at<uchar>(row, col) = 255;
			}
		}
	}

	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	dilate(mask, mask, se);
	GaussianBlur(mask, mask, Size(5, 5), 0);
	Mat result = Mat::zeros(img.size(), CV_8UC3);
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			float w1 = mask.at<uchar>(row, col) / 255.0;
			Vec3b bgr = img.at<Vec3b>(row, col);
			bgr[0] = w1 * 255.0 + bgr[0] * (1.0 - w1);
			bgr[1] = w1 * 0 + bgr[1] * (1.0 - w1);
			bgr[2] = w1 * 255.0 + bgr[2] * (1.0 - w1);
			result.at<Vec3b>(row, col) = bgr;
		}
	}
	imshow("KMeans-image-Demo", result);
	waitKey(0);
	return RET_ERROR_OK;
}

int UManger::KmeansColorExtraction(string& PicPath)
{
	Mat img = imread(PicPath);
	if (img.empty())
	{
		cout << "cant load img" << endl;
		return -1;
	}
	imshow("input-img", img);

	int width = img.cols;
	int height = img.rows;
	int dims = img.channels();

	//初始化定义
	int sampleCount = width*height;
	int clusterCount = 4;
	Mat labels;
	Mat centers;

	//RGB 数据转样本数据
	Mat sample_data = img.reshape(3, sampleCount);
	Mat data;
	sample_data.convertTo(data, CV_32F);

	// 运行K-Means
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	  
	kmeans(data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	Mat card = Mat::zeros(Size(width, 50), CV_8UC3);
	vector<float> clusters(clusterCount);
	for (int i = 0; i < labels.rows; i++) {
		clusters[labels.at<int>(i, 0)]++;
	}
	for (int i = 0; i < clusters.size(); i++) {
		clusters[i] = clusters[i] / sampleCount;
	}
	int x_offset = 0;
	for (int x = 0; x < clusterCount; x++) {
		Rect rect;
		rect.x = x_offset;
		rect.y = 0;
		rect.height = 50;
		rect.width = round(clusters[x] * width);
		x_offset += rect.width;
		int b = centers.at<float>(x, 0);
		int g = centers.at<float>(x, 1);
		int r = centers.at<float>(x, 2);
		rectangle(card, rect, Scalar(b, g, r), -1, 8, 0);
	}

	imshow("Image Color Card", card);
	waitKey(0);
	return RET_ERROR_OK;

}

int UManger::KNN(void)
{
	Mat img = imread("../Test/img/digits.png");
	if(img.empty())
	{
		cout << "cant read img" << endl;
		return -1;
	}
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//分割为5000个cells
	Mat images = Mat::zeros(5000, 400, CV_8UC1);
	Mat labels = Mat::zeros(5000, 1, CV_8UC1);

	Rect rect;

	rect.height = 20;
	rect.width = 20;
	int index = 0;

	Rect roi;
	roi.x = 0;
	roi.y = 0;

	roi.height = 1;
	roi.width = 400;

	for(int row = 0;row<50;row++)
	{
		int label = row / 5;
		for (int col=0;col<100;col++)
		{
			Mat digits = Mat::zeros(20, 20, CV_8UC1);
			index = row * 100 + col;

			rect.x = col * 20;
			rect.y = row * 20;
			gray(rect).copyTo(digits);
			Mat one_row = digits.reshape(1, 1);
			roi.y = index;
			one_row.copyTo(images(roi));
			labels.at<uchar>(index, 0) = label;
		}
	}
	cout << "load sample hand-writing data.." << endl;

	//装换为浮点数
	images.convertTo(images, CV_32FC1);
	labels.convertTo(labels, CV_32SC1);

	// 开始KNN训练
	printf("Start to knn train...\n");
	Ptr<ml::KNearest> knn = ml::KNearest::create();
	knn->setDefaultK(5);
	knn->setIsClassifier(true);
	Ptr<ml::TrainData> tdata = ml::TrainData::create(images, ml::ROW_SAMPLE, labels);
	knn->train(tdata);
	knn->save("./knn_knowledge.yml");
	printf("Finished KNN...\n");
	return true;
	

}

//*****************************************UI相关*****************************************

int UManger::UI_Img(bool& use_img)
{
	const int num = 500;
	char img_name[50];
	cvui::init(WINDOW_NAME);

	int count = 1;
	bool whitebalance = false;
	while (use_img)
	{
		//img按键窗口
		cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
		cvui::checkbox(BaseImg, 50, 25, "img", &use_img);
		cvui::checkbox(BaseImg, 200, 25, "camera", &use_camera);
		cvui::printf(BaseImg, 0, 40, "*************************************************");
		cvui::checkbox(BaseImg, 0, 70, "whitebalance", &whitebalance);

		sprintf(img_name, "D://workspace//Utils//Test//img//%d.jpg", count);

		Mat img = imread(img_name);
		if (whitebalance == true)
			WhiteBalance(img);
		resize(img, img, Size(640, 480));

		//Mat ROI = BaseImg(Rect(320, 0, 640, 480));
		//addWeighted(ROI, 0, img, 1, 0, ROI);
		//替代上面两行代码
		cvui::image(BaseImg, 320, 0, img);
		//下一张图片
		if (cvui::button(BaseImg, 255, 450, 60, 30, "latter"))
		{
			count++;
		}
		//上一张图片
		if (cvui::button(BaseImg, 5, 450, 60, 30, "previous"))
		{
			count--;
		}
		cvui::printf(BaseImg, 130, 460, 0.4, 0xff0000, "now is:%d", count);

		if (img.empty())
		{
			cerr << "no img in file now" << endl;
			destroyAllWindows();
			break;
		}

		cvui::update();
		cv::imshow(WINDOW_NAME, BaseImg);

		cv::waitKey(10);
		if (use_camera && !use_img)
		{
			img.release();
			UI_Camera(use_camera);
			break;
		}
	}
	waitKey(0);
	return 0;
}

int UManger::UI_Camera(bool& use_camera)
{
	//use_img = false;
	while (use_camera)
	{
		VideoCapture cap(0);
		bool open_camera = true;
		//bool cartoon = false;

		cvui::init(WINDOW_NAME);
		while (open_camera)
		{
			cvui::window(BaseImg, 0, 0, 320, 480, "********************camera********************");
			cvui::checkbox(BaseImg, 50, 25, "img", &use_img);
			cvui::checkbox(BaseImg, 200, 25, "camera", &use_camera);
			cvui::printf(BaseImg, 0, 40, "*************************************************");

			cvui::checkbox(BaseImg, 10, 60, "SkinDetector", &SkinDetector);
			cvui::checkbox(BaseImg, 140, 60, "CameraFilter", &CameraFilter);
			cvui::printf(BaseImg, 0, 80, "*************************************************");

			Mat frame;
			cap >> frame;
			resize(frame, frame, Size(640, 480));

			//bool puppet  = false;
			//puppet = (SkinDetector == true && CameraFilter == false);

			while (SkinDetector == true && CameraFilter == false)
			{
				cvui::checkbox(BaseImg, 20, 90, "RGBSkin", &rgbcolor);
				cvui::checkbox(BaseImg, 20, 110, "EleSkin", &ellipseskin);
				cvui::checkbox(BaseImg, 20, 130, "YOSkin", &ycrcbotusskin);
				cvui::checkbox(BaseImg, 100, 90, "YCrSkin", &ycrcbskin);
				cvui::checkbox(BaseImg, 100, 110, "HSVSkin", &hsvskin);

				if (rgbcolor == true)
					RGBSkin(frame);
				if (ellipseskin == true)
					EllipseSkin(frame);
				if (ycrcbotusskin == true)
					YCrCbOtusSkin(frame);
				if (ycrcbskin == true)
					YCrCbSkin(frame);
				if (hsvskin == true)
					HSVSkin(frame);
				break;
			}

			while (CameraFilter == true && SkinDetector == false)
			{
				cvui::checkbox(BaseImg, 10, 90, "Cartoon", &Cartoon);
				cvui::checkbox(BaseImg, 10, 120, "Nostalgic", &Nostalgic);
				if (Cartoon == true)
					CartoonFilter(frame);
				if (Nostalgic == true)
					NostalgicFilter(frame);
				break;
			}

			cvui::update();

			//添加摄像头遮挡
			/*Mat mask = Mat::zeros(Size(640, 480), CV_8UC3);
			frame = mask.clone();*/
			//Mat ROI = BaseImg(Rect(320, 0, 640, 480));
			//addWeighted(ROI, 0, frame, 1, 0, ROI);
			//使用下面代码替代上面两行
			cvui::image(BaseImg, 320, 0, frame);

			cv::imshow(WINDOW_NAME, BaseImg);
			cv::waitKey(30);

			if (!use_camera && use_img)
			{
				open_camera = false;
				//use_camera为false的时候关闭camera
				cap.release();
				UI_Img(use_img);

			}
		}
	}
	return 0;
}
