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

void cvp::Pupil::detect(cv::Mat img)
{
cv::Mat gray;
cv::Mat candidate;

    // Invert the source image and convert to grayscale
    cv::cvtColor(img, gray, CV_BGR2GRAY);

    // Other filters
    //cv:equalizeHist(gray, gray);
    //cv::blur(gray, gray, Size(30, 30), Point(-1,-1), BORDER_DEFAULT);

    for (int threshold = 0; threshold <= 255 && _rect.width < 1; threshold++) {
        // Convert to binary image by thresholding it
        cv::threshold(gray, candidate, threshold, 255, cv::THRESH_BINARY_INV);

        // Find all contours
        vector<vector<cv::Point> > contours;
        cv::findContours(candidate, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

        // Fill holes in each contour
        cv::drawContours(candidate, contours, -1, CV_RGB(255,255,255), -1);

        for (int i = 0; i < contours.size(); i++) {
            double area = cv::contourArea(contours[i]);
            cv::Rect rect = cv::boundingRect(contours[i]);
            int radius = rect.width / 2;

            double sizeRate = (double)rect.width / (double)img.cols;

            // If contour: has round shape and has a specific size relation
            // Then it is the pupil
            if (sizeRate >= 0.25 && sizeRate <= 0.41 &&
                abs(1 - ((double)rect.width / (double)rect.height)) <= 0.2 &&
                abs(1 - (area / (CV_PI * pow(radius, 2)))) <= 0.2)
            {
                _contour = contours[i];
                _rect = cv::boundingRect(contours[i]);
                _srcImage = img;
            }
        }
    }
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