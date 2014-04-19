#include "../cvpupil.hpp"

using namespace std;

/**
 * Eye cvp class
 */
cvp::eye::Tracker::Tracker()
{
}

cvp::eye::Tracker::~Tracker()
{
}

void cvp::eye::Tracker::detect(cvp::Strategy* strategy, cv::Mat img)
{
    _srcImage = img;
    _eyes = strategy->process(img);
}

void cvp::eye::Tracker::track(cvp::Strategy* strategy, cv::Mat img)
{
    detect(strategy, img);
}

int cvp::eye::Tracker::getCount()
{
    return _eyes.size();
}

vector<cv::Rect> cvp::eye::Tracker::getRects()
{
    return _eyes;
}

vector<cv::Mat> cvp::eye::Tracker::getMats()
{
    vector<cv::Mat> mats;

    for (int i = 0; i < _eyes.size(); i++) {
        mats.push_back(_srcImage(_eyes[i]));
    }

    return mats;
}