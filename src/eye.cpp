#include "cvpupil.hpp"

using namespace std;

/**
 * Eye cvp class
 */
cvp::Eye::Eye()
{
}

cvp::Eye::~Eye()
{
}

void cvp::Eye::detect(cvp::Strategy* strategy, cv::Mat img)
{
    _srcImage = img;
    _eyes = strategy->process(img);
}

void cvp::Eye::track(cv::Mat img)
{
    //detect(img);
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