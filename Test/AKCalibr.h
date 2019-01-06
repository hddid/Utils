#ifndef ANKOBOT_CALIBRATION_H
#define ANKOBOT_CALIBRATION_H

#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

typedef struct AKConfig
{
    AKConfig()
    {
        boardSize = cv::Size(4, 11);
        squareSize = 50;//circle center distance
        imgCount = 9;
        aspectRatio = 1.0f;
        showGridPoints = true;
        showUndistorsed = true;
        waitTime = 0;
    }

    Size boardSize;
    float squareSize;
    float aspectRatio;
    int imgCount;
    int waitTime;
    bool showUndistorsed;
    bool showGridPoints;
}AKConfig;

class AKCalibr
{
public:
    AKCalibr();
    ~AKCalibr();

    bool Process(const std::vector<Mat>& imgList);
    inline Mat GetMatric(void) const { return mMatrix; }
    inline Mat GetDistCoeffs(void) const { return mDistCoeffs; }
    inline void SetConfig(const AKConfig& config) { mConfig = config; }

private:
    void CalcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners); 

    bool Calibration(const Size & imageSize, const vector<vector<Point2f>>& imagePoints, Mat & cameraMatrix, Mat & distCoeffs);
    bool Calibration(const Size& imageSize, const vector<vector<Point2f>> imagePoints, Mat& cameraMatrix
        , Mat& distCoeffs, vector<Mat>& rvecs, vector<Mat>& tvecs, vector<float>& reprojErrs);

    double ComputeReprojectionErrors(const vector<vector<Point3f>>& objectPoints, const vector<vector<Point2f>>& imagePoints
        , const vector<Mat>& rvecs, const vector<Mat>& tvecs, const Mat & cameraMatrix, const Mat & distCoeffs, vector<float>& perViewErrors);

private:
    int mImgCount;
    Mat mMatrix;
    Mat mDistCoeffs;
    Size mImageSize;
    vector<vector<Point2f>> mImagePoints;
    AKConfig mConfig;
};

#endif // ANKOBOT_CALIBRATION_H
