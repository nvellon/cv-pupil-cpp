#include "../cvpupil.hpp"

using namespace std;

/**
 * FaceHaarDetection class
 */
cvp::face::HaarDetection::HaarDetection(const char* cascadePath, double minSizeRatio)
{
    _cascadePath = cascadePath;
    _minSizeRatio = minSizeRatio;
}

vector<cv::Rect> cvp::face::HaarDetection::process(cv::Mat img)
{
// others
cv::Mat img_gray;
vector<cv::Rect> faces;

// detectMultiScale params
double scaleFactor = 1.1;
int minNeighbors = 4;
int flags = CV_HAAR_SCALE_IMAGE;
//cv::Size minSize(cvRound(img.cols * _minSizeRatio), cvRound(img.rows * _minSizeRatio));

    cv::cvtColor(img, img_gray, CV_RGB2GRAY);

    cv::equalizeHist(img_gray, img_gray);

    _cascade.load(_cascadePath);

    _cascade.detectMultiScale(img_gray, faces, scaleFactor, minNeighbors, flags);

    return faces;
}