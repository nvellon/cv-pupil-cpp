#include "../cvpupil.hpp"

using namespace std;

/**
 * TemplateTracking class
 */
cvp::pupil::TemplateTracking::TemplateTracking()
{
}

vector<cv::Rect> cvp::pupil::TemplateTracking::process(cv::Mat img)
{
vector<cv::Rect> result;
int match_method = CV_TM_CCORR_NORMED;

    cv::matchTemplate(img, _srcImage(_rect), result, match_method);
    cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    double minVal, maxVal;
    cv::Point minLoc, maxLoc, matchLoc;

    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );

    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
        matchLoc = minLoc;
    else
        matchLoc = maxLoc;

    return result;
}