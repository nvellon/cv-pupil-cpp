#include "cvpupil.hpp"

using namespace std;

/**
 * Pupil cvp class
 */
cvp::Pupil::Pupil()
{

}

cvp::Pupil::~Pupil()
{

}

void cvp::Pupil::detect(cvp::Strategy* strategy, cv::Mat img)
{
vector<cv::Rect> pupil;

    pupil = strategy->process(img);

    if (pupil.size() > 0) {
        _rect = pupil[0];
    }

    _srcImage = img;
}

void cvp::Pupil::track(cv::Mat img)
{
cv::Mat result;
int match_method = CV_TM_CCORR_NORMED;

    cv::matchTemplate(img, _srcImage(_rect), result, match_method);
    cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    double minVal; double maxVal;
    cv::Point minLoc, maxLoc, matchLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
        matchLoc = minLoc;
    else
        matchLoc = maxLoc;
}

cv::Rect cvp::Pupil::getRect()
{
    return _rect;
}