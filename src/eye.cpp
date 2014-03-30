#include "cvpupil.hpp"

using namespace std;

/**
 * Eye cvp class
 */
cvp::Eye::Eye(const char* cascadePath, double minSizeRatio)
{
    _cascade.load(cascadePath);
    _minSizeRatio = minSizeRatio;
}

cvp::Eye::~Eye()
{

}

void cvp::Eye::detect(cv::Mat img)
{
// detectMultiScale params
double scaleFactor = 1.1;
int minNeighbors = 2;
int flags = CV_HAAR_SCALE_IMAGE;
cv::Size minSize(cvRound(img.cols * _minSizeRatio), cvRound(img.rows * _minSizeRatio));
cv::Mat img_gray;

    _srcImage = img.clone();

    cv::cvtColor(_srcImage, img_gray, CV_RGB2GRAY);

    _cascade.detectMultiScale(img_gray, _eyes, scaleFactor, minNeighbors, flags, minSize);
}

void cvp::Eye::track(cv::Mat img)
{
    detect(img);
}

int cvp::Eye::getCount()
{
    return _eyes.size();
}

vector<cv::Rect> cvp::Eye::getRects()
{
    return _eyes;
}

vector<cv::Mat> cvp::Eye::getMats()
{
    vector<cv::Mat> mats;

    for (int i = 0; i < _eyes.size(); i++) {
        mats.push_back(_srcImage(_eyes[i]));
    }

    return mats;
}