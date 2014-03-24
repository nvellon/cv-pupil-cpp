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
     *
     * @param const char* cascadePath Cascade classifier file path
     * @param cv::Mat     img         Image matrix
     *
     * @return std::vector<cv::Rect>
     */
    std::vector<cv::Rect> detectEyes(const char* cascadePath, cv::Mat img);

    /**
     * Pupil detection
     *
     * @param cv::Mat eye Eye image matrix
     *
     * @return cv::Rect
     */
    cv::Rect detectPupil(cv::Mat eye);
    
    /**
     * Pupil tracking
     *
     * @param cv::Mat eye Eye image matrix
     * @param cv::Mat tpl Template image matrix
     *
     * @return cv::Point
     */
    cv::Point trackPupil(cv::Mat eye, cv::Mat tpl);

    /**
     * Run detection on a file and show result
     *
     * @param const char* name Image file path to process
     *
     * @return void
     */
    void detectFile(const char* name);

    /**
     * Run camera detection and show result
     *
     * @return void
     */
    void detectCam();
}
