#include "../cvpupil.hpp"

using namespace std;

/**
 * EyeHaarDetection class
 */
cvp::eye::HaarDetection::HaarDetection(const char* cascadePath, double minSizeRatio)
{
    _cascadePath = cascadePath;
    _minSizeRatio = minSizeRatio;
}

vector<cv::Rect> cvp::eye::HaarDetection::process(cv::Mat img)
{
// others
cv::Mat img_gray;
vector<cv::Rect> eyes;

// detectMultiScale params
double scaleFactor = 1.1;
int minNeighbors = 2;
int flags = CV_HAAR_SCALE_IMAGE;
cv::Size minSize(cvRound(img.cols * _minSizeRatio), cvRound(img.rows * _minSizeRatio));

    cv::cvtColor(img, img_gray, CV_RGB2GRAY);

    _cascade.load(_cascadePath);

    _cascade.detectMultiScale(img_gray, eyes, scaleFactor, minNeighbors, flags, minSize);

    return eyes;
}