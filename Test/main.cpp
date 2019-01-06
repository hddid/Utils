#include <stdio.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "AKCalibr.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	AKCalibr calibr;

	int nc = 12;
	char filePath[32];
	vector<Mat> imgList;
	for (int i = 1; i < nc; ++i)
	{
		sprintf(filePath, "../Data/%d.jpg", i);
		Mat view = imread(filePath, 0);

		if (view.empty())
			continue;

		imgList.push_back(view);
	}
	calibr.Process(imgList);

	system("pause");
	return 1;
}
