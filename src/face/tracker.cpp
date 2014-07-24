#include "../cvpupil.hpp"

using namespace std;

/**
 * Face cvp class
 */
cvp::face::Tracker::Tracker()
{
}

cvp::face::Tracker::~Tracker()
{
}

void cvp::face::Tracker::detect(cvp::Strategy* strategy, cv::Mat img)
{
    _srcImage = img;
    _faces = strategy->process(img);
}

void cvp::face::Tracker::track(cvp::Strategy* strategy, cv::Mat img)
{
    detect(strategy, img);
}

int cvp::face::Tracker::getCount()
{
    return _faces.size();
}

vector<cv::Rect> cvp::face::Tracker::getRects()
{
    return _faces;
}

vector<cv::Mat> cvp::face::Tracker::getMats()
{
    vector<cv::Mat> mats;

    for (int i = 0; i < _faces.size(); i++) {
        mats.push_back(_srcImage(_faces[i]));
    }

    return mats;
}