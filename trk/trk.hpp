#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <iostream>
#include <stdio.h>

namespace trk 
{
    /**
     * Eyes detection
     */
    std::vector<cv::Rect> detectEyes(const char* cascadePath, cv::Mat img);

    /**
     * Pupil detection
     */
    cv::Rect detectPupil(cv::Mat eye);
    
    /**
     * Pupil tracking
     */
    cv::Point trackPupil(cv::Mat eye, cv::Mat tpl);

    /**
     * Run detection and show result
     */
    void detect(const char* name);
}
