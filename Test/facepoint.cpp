#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace dlib;

int main()
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "cant open camera" << endl;
		return 0;
	}
	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor pose_model;
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

	while (cv::waitKey(30)!=27)
	{
		cv::Mat frame;
		cap >> frame;
		cv_image<bgr_pixel> cimg(frame);

		std::vector<rectangle> faces = detector(cimg);

		std::vector<full_object_detection> shapes;
		for (unsigned long i = 0;i<faces.size();++i)
		{
			shapes.push_back(pose_model(cimg, faces[i]));
		}
		ofstream outfile;
		outfile.open("./zeng.txt", ios::app);
		if (!outfile.is_open())
		{
			cout << "open file failure" << endl;
		}
		if (!shapes.empty())
		{
			for (int i = 0;i<68;i++)
			{
				circle(frame, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 255, 0), -1);
				cv::putText(frame, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0));
				outfile << shapes[0].part(i).x() << " " << shapes[0].part(i).y() << "\t" << endl;
			}
			outfile.close();
		}
		//imshow("point", frame);
	}
	return 0;
}