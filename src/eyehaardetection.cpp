#include "cvpupil.hpp"

using namespace std;

/**
 * EyeHaarDetection class
 */
cvp::EyeHaarDetection::EyeHaarDetection(const char* cascadePath, double minSizeRatio)
{
    _cascade.load(cascadePath);
    _minSizeRatio = minSizeRatio;
}

vector<cv::Rect> cvp::EyeHaarDetection::process(cv::Mat img)
{
// others
cv::Mat img_gray;
vector<cv::Rect> eyes;

    cv::cvtColor(img, img_gray, CV_RGB2GRAY);

    // detectMultiScale params
    double scaleFactor = 1.1;
    int minNeighbors = 2;
    int flags = CV_HAAR_SCALE_IMAGE;
    cv::Size minSize(cvRound(img.cols * _minSizeRatio), cvRound(img.rows * _minSizeRatio));

    _cascade.detectMultiScale(img_gray, eyes, scaleFactor, minNeighbors, flags, minSize);

    return eyes;
}