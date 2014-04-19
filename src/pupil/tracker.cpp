#include "../cvpupil.hpp"

using namespace std;

/**
 * Pupil cvp class
 */
cvp::pupil::Tracker::Tracker()
{

}

cvp::pupil::Tracker::~Tracker()
{

}

void cvp::pupil::Tracker::detect(cvp::Strategy* strategy, cv::Mat img)
{
vector<cv::Rect> pupil;

    pupil = strategy->process(img);

    if (pupil.size() > 0) {
        _rect = pupil[0];
    }

    _srcImage = img;
}

void cvp::pupil::Tracker::track(cvp::Strategy* strategy, cv::Mat img)
{
    strategy->process(img);
}

cv::Rect cvp::pupil::Tracker::getRect()
{
    return _rect;
}